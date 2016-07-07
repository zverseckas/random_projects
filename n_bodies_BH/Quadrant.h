//
// Created by zilvinas on 16.3.20.
// Quadrant class
// The main part of Barnes-Hut algorithm
// Contains functions to crate, update and read the
// Quadrant tree. This way we reduce the update and traverse
// complexity from O(n^2) to O(n*log2(n))
//

#ifndef N_BODIES_BH_NODE_H
#define N_BODIES_BH_NODE_H

#include <vector>
#include "Body.h"

class Quadrant {
private:
    // Threshold for noce calculations
    const double NODE_THRESHOLD = 0.5;
public:
    // Max depth of a Quadrant
    unsigned MAX_DEPTH = 13;
    // Vector of bodies contained in a Quadrant
    std::vector<Body*> bodies;
    // Vector of children owned by a Quadrant
    std::vector<Quadrant*> children;
    bool has_children;

    // Properties of a Quadrant
    // (mid_x, mid_y) - geometric middle point
    double mid_x, mid_y;
    // Quadrant dimensions
    double width, height;
    // Total mass of bodies withing the Quadrant
    double total_mass;
    // (mass_center_x, mass_center_y)
    // - mass center of a Quadrant
    double mass_center_x;
    double mass_center_y;
    // Depth of a Quadrant
    unsigned depth;

    // Constructs a Quadrant with depth = 0
    // and no children
    Quadrant();

    // Constructs a Quadrant with depth = depth
    // and no children
    Quadrant(unsigned int depth);

    // Deletes children and the Quadrant itself
    ~Quadrant();

    // Generates the Barnes-Hut Quadrant Tree
    void generate_BHTree();

    // Calculates the force of a body with
    // respect to a Quadrant (Reducing iterations)
    void quad_node_force(Body *b);

    // Traverse the Quadrant tree and update forces
    void check_quad_node(Body *b);

    // Initialize a Quadrant
    void init(std::vector<Body *> bodies, double width, double height, double mid_x = 0, double mid_y = 0);

    // Delete children and bodies
    void reset();

    // Number of working threads
    void set_number_of_threads(int num);
};

#endif //N_BODIES_BH_NODE_H
