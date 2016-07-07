//
// Created by zilvinas on 16.3.20.
//

#include "Quadrant.h"
#include <memory>
#include <cmath>
#include <iostream>
#include <omp.h>

Quadrant::Quadrant(unsigned depth) {
    has_children = false;
    this->depth = depth;
    omp_set_num_threads(8);
}

Quadrant::Quadrant() {
    has_children = false;
    depth = 0;
}

void Quadrant::set_number_of_threads(int num) {
    omp_set_num_threads(8);
}


void Quadrant::quad_node_force(Body *b) {
    // Vector from the body to the center of mass
    double vec_x = mass_center_x - b->pos_x;
    double vec_y = mass_center_y - b->pos_y;

    // Proper Gravitational relation
    double dist_squared = vec_x * vec_x + vec_y * vec_y + Body::SOFTENER * Body::SOFTENER;
    double dist_sixth = dist_squared * dist_squared * dist_squared;
    double force = (total_mass * b->mass) / sqrt(dist_sixth) * Body::GRAVITY_CONST;

    // Update the Quadrant force
    b->force_x += vec_x * force;
    b->force_y += vec_y * force;
}

void Quadrant::check_quad_node(Body *b) {
    if (bodies.size()) {
        // Distance from the Quadrant to the Body
        double dx = mass_center_x - b->pos_x;
        double dy = mass_center_y - b->pos_y;
        double distance = sqrt(dx * dx + dy * dy);

        // If a Quadrant does not have children or we are in threshold
        if (width / distance < NODE_THRESHOLD || !has_children) {
            // Find body force to Quadrant
            quad_node_force(b);
        } else {
            // Else check other children too
            children[0]->check_quad_node(b);
            children[1]->check_quad_node(b);
            children[2]->check_quad_node(b);
            children[3]->check_quad_node(b);
        }
    }
}

void Quadrant::generate_BHTree() {
    // Declare found children for a Quadrant (divide into 4)
    std::vector<Body*> q1_bodies, q2_bodies, q3_bodies, q4_bodies;

    // Put bodies into appropriate child Quadrants
    #pragma omp parallel for
    for (int i = 0; i < bodies.size(); i++) {
        if (bodies[i]->pos_x < mid_x + width / 2) {
            if (bodies[i]->pos_y < mid_y + height / 2) {
                q1_bodies.push_back(bodies[i]);
            } else {
                q3_bodies.push_back(bodies[i]);
            }
        } else {
            if (bodies[i]->pos_y < mid_y + height / 2) {
                q2_bodies.push_back(bodies[i]);
            } else {
                q4_bodies.push_back(bodies[i]);
            }
        }
    }

    // Branch of the children
    Quadrant * q1 = new Quadrant(depth + 1);
    Quadrant * q2 = new Quadrant(depth + 1);
    Quadrant * q3 = new Quadrant(depth + 1);
    Quadrant * q4 = new Quadrant(depth + 1);

    // Initialize the children
    #pragma omp task untied
    q2->init(q2_bodies, width / 2, height / 2, mid_x + width / 2, mid_y);
    #pragma omp task untied
    q3->init(q3_bodies, width / 2, height / 2, mid_x, mid_y + height / 2);
    #pragma omp task untied
    q4->init(q4_bodies, width / 2, height / 2, mid_x + width / 2, mid_y + height / 2);
    #pragma omp task untied
    q1->init(q1_bodies, width / 2, height / 2, mid_x, mid_y);

    // Store them
    children.push_back(q1);
    children.push_back(q2);
    children.push_back(q3);
    children.push_back(q4);

    has_children = true;
}

void Quadrant::init(std::vector<Body *> bodies, double width, double height, double mid_x, double mid_y) {
    // Set the main properties
    this->bodies = bodies;
    this->mid_x = mid_x;
    this->mid_y = mid_y;
    this->width = width;
    this->height = height;

    double mass = 0;
    double center_x = 0;
    double center_y = 0;

    // Compute the total mass
    omp_set_num_threads(4);
    #pragma omp parallel for
    for (int i = 0; i < bodies.size(); i++) {
        mass += bodies[i]->mass;
        center_x += bodies[i]->pos_x;
        center_y += bodies[i]->pos_y;
    }
    total_mass = mass;

    // Compute the center of mass
    size_t size = bodies.size();
    mass_center_x = center_x / size;
    mass_center_y = center_y / size;

    // Build the Quadrant tree
    if (size > 1 && depth < MAX_DEPTH) {
        #pragma omp parallel
        {
            #pragma omp single
            generate_BHTree();
        }
    }
}

void Quadrant::reset() {
    bodies.clear();
    for (int i = 0; i < children.size(); i++) {
        children[i]->reset();
        delete children[i];
    }
    children.clear();
    has_children = false;
}

Quadrant::~Quadrant() {
    for (int i = 0; i < children.size(); i++) {
        delete children[i];
    }
    children.clear();
}
