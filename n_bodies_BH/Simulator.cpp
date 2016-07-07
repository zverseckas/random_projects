#include "Simulator.h"
#include <iostream>
#include <omp.h>
#include <sys/time.h>

// Timestamp for testing speed
typedef unsigned long long timestamp_t;
static timestamp_t get_timestamp() {
    struct timeval now;
    gettimeofday(&now, NULL);
    return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

Simulator::Simulator(unsigned body_count, unsigned width, unsigned height, int thread_num, std::string title) {
    this->body_count  = body_count;
    // GUI properties
    this->width = width;
    this->height = height;
    this->title = title;
    omp_set_num_threads(thread_num);

    // Adjust the precision of calculations
    // The more bodies the less precision
    if (body_count <= 500) {
        root_node.MAX_DEPTH = 100;
    } else if (body_count <= 2000) {
        root_node.MAX_DEPTH = 20;
    }

    root_node.set_number_of_threads(thread_num);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 6;
    this->window = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Default, settings);
}

Simulator::~Simulator() {
    delete_bodies();
    delete this->window;
}

void Simulator::start() {
    // Populate the body disk
    create_vector_disk();
    // Adjust the GUI view
    adjust_view();
    while (window->isOpen()) {
        listen();
        if (!paused) {

            // HERE GOES THE MAIN PART
            update_bodies();
            root_node.reset();

            timestamp_t t0 = get_timestamp();
            root_node.init(bodies, sim_width, sim_height);
            set_body_attraction();
            timestamp_t t1 = get_timestamp();
            std::cout << (t1 - t0) / 1000000.0L << std::endl;

            // END OF MAIN PART

        } else {
            window->clear();
        }
        // Draw the bodies
        #pragma omp single
        //render();
        window->display();
    }
}

void Simulator::set_body_attraction() {
    #pragma omp parallel for
    for (int i = 0; i < body_count; i++) {
        // Traverse the whole Quadrant tree and update it
        root_node.check_quad_node(bodies[i]);
    }
}

void Simulator::create_vector_disk() {
    for (int i = 0; i < body_count; i++) {
        // Distance random coefficient
        double dist_coef = random();
        // Distance between center and outside times coefficient
        double distance = disk_min_radius + (disk_max_radius - disk_min_radius) * dist_coef * dist_coef;

        // Give a random angle for a body
        double angle = random() * 2 * M_PI;
        double pos_x = cos(angle) * distance + (sim_width / 2);
        double pos_y = sin(angle) * distance + (sim_height / 2);

        // Give and orbital velocity to a body
        double orb_vel = sqrt((central_mass * Body::GRAVITY_CONST) / distance);
        double vel_x = (sin(angle) * orb_vel);
        double vel_y = (-cos(angle) * orb_vel);

        // Random mass between max and min
        double mass = body_min_mass + (int) round(random()) % (int) (body_max_mass - body_min_mass);

        // Create the body
        bodies.push_back(new Body(pos_x, pos_y, mass, vel_x, vel_y));
    }
}

void Simulator::render() {
    window->clear();
    draw_guidelines(&root_node);
    sf::CircleShape body_shape;
    for (int i = 0; i < body_count; i++) {
        // Adjust the dot size with respect to zoom
        if (zoom > 1) {
            body_shape.setRadius((float) (bodies[i]->mass * zoom));
        }
        else {
            body_shape.setRadius((float) bodies[i]->mass);
        }

        // Force coefficient
        double force_coef = sqrt(bodies[i]->force_x * bodies[i]->force_x + bodies[i]->force_y * bodies[i]->force_y) * (150 * Body::GRAVITY_CONST);
        if (force_coef > 1) {
            force_coef = 1;
        }

        // Set the coloring
        double red, green, blue;
        red = 1 - force_coef;
        blue = force_coef < 0.2 ? force_coef * 5 : 1;
        green = force_coef < 0.5 ? force_coef * 2 : 1;
        body_shape.setFillColor(sf::Color((sf::Uint8) (255 * red), (sf::Uint8) (255 * green), (sf::Uint8) (255 * blue), 128));

        // Draw
        body_shape.setPosition((float) (bodies[i]->pos_x - bodies[i]->mass), (float) (bodies[i]->pos_y - bodies[i]->mass));
        window->draw(body_shape);
    }
}

void Simulator::update_bodies() {
    Body *center = new Body(sim_width / 2, sim_height / 2, central_mass);
    #pragma omp parallel for
    for (int i = 0; i < body_count; i++) {
        // Attract to center
        bodies[i]->force_to(center);

        // Check the contraints
        if ((bodies[i]->pos_x > sim_width && bodies[i]->vel_x > 0) || (bodies[i]->pos_x < 0 && bodies[i]->vel_x < 0)) bodies[i]->vel_x = -bodies[i]->vel_x;
        if ((bodies[i]->pos_y > sim_height && bodies[i]->vel_y > 0) || (bodies[i]->pos_y < 0 && bodies[i]->vel_y < 0)) bodies[i]->vel_y = -bodies[i]->vel_y;

        // Update velocity
        bodies[i]->vel_x += bodies[i]->force_x / bodies[i]->mass;
        bodies[i]->vel_y += bodies[i]->force_y / bodies[i]->mass;

        // Update positions
        bodies[i]->pos_x += bodies[i]->vel_x;
        bodies[i]->pos_y += bodies[i]->vel_y;

        // Update force
        bodies[i]->force_x = 0;
        bodies[i]->force_y = 0;
    }
}

// Utility functions

void Simulator::listen() {
    sf::Event event;
    window->setView(sim_view);
    while (window->pollEvent(event)) {
        // Close a windows
        if (event.type == sf::Event::Closed) window->close();
        if (event.type == sf::Event::KeyPressed) {
            // Pause a simulation
            if (event.key.code == sf::Keyboard::Space) paused = !paused;
        }
        // Zoom in/out the simulation
        if (event.type == sf::Event::MouseWheelScrolled) {
            zoom *= 1 - event.mouseWheelScroll.delta / 20;
            sim_view.zoom(1 + -event.mouseWheelScroll.delta / 20);
        }
    }
}

void Simulator::delete_bodies() {
    for(int i = 0; i < body_count; i++) {
        delete bodies[i];
    }
    bodies.clear();
}

double Simulator::random() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0, 1);
    return dis(gen);
}

void Simulator::adjust_view() {
    sim_view.reset(sf::FloatRect((float) sim_width / 2 - width / 2, (float) sim_height / 2 - height / 2, width, height));
    sim_view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    window->setView(sim_view);
}

void Simulator::draw_guidelines(Quadrant* quad) {
    sf::RectangleShape guide;
    guide.setFillColor(sf::Color(0, 0, 0, 0));
    guide.setOutlineThickness((float) zoom);
    guide.setOutlineColor(sf::Color(80, 25, 100, 50));
    guide.setPosition((float) quad->mid_x, (float) quad->mid_y);
    guide.setSize(sf::Vector2f( (float) quad->width, (float) quad->height));

    window->draw(guide);

    if (quad->has_children) {
        draw_guidelines(quad->children[0]);
        draw_guidelines(quad->children[1]);
        draw_guidelines(quad->children[2]);
        draw_guidelines(quad->children[3]);
    }
}
