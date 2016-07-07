//
// Created by zilvinas on 16.3.20.
// Simulator class
// Draws the GUI and manages a Quadrant tree
//

#ifndef N_BODIES_BH_SIMULATOR_H
#define N_BODIES_BH_SIMULATOR_H

#include "SFML/Graphics.hpp"
#include "Body.h"
#include <vector>
#include <string>
#include "Quadrant.h"

class Simulator {
private:
    // Total bodies (can be very large)
    std::vector<Body*> bodies;
    // Number of bodies
    unsigned body_count = 1;

    // GUI PROPERTIES
    // Window dimensions
    unsigned width, height;
    // Window title
    std::string title;
    bool paused = false;
    sf::View sim_view;
    sf::RenderWindow* window;
    double zoom = 1;

    // Particle disk dimensions
    double const disk_max_radius = 200;
    double const disk_min_radius = 40;

    // Central mass
    double const central_mass = 50000;

    // Bodies mass range
    double const body_max_mass = 3;
    double const body_min_mass = 1;

    // Simulation size
    double const sim_width = 327680;
    double const sim_height = 327680;

    // The main Quadrant
    Quadrant root_node;

    // Utility functions
    // Sample of a random normal distribution
    double random();
    // Event listener
    void listen();
    // Adjusts the screen
    void adjust_view();

public:

    Simulator(unsigned body_count, unsigned width, unsigned height, int thread_num, std::string tile);
    ~Simulator();

    // Delete bodies in the simulation
    void delete_bodies();

    // Start the simulation
    void start();

    // Update the Quadrant tree
    // Called each iteration
    void set_body_attraction();

    // Create a normally randomly distributed
    // particle disk with orbital velocities
    void create_vector_disk();

    // Draws the current set of bodies on screen
    void render();

    // Draws guidelines to show the Quadrants
    void draw_guidelines(Quadrant* quad);

    // Updates the bodies
    void update_bodies();
};

#endif //N_BODIES_BH_SIMULATOR_H
