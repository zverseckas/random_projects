//
// Created by zilvinas on 16.3.20.
// Body class
// Implement essential physical body features
// and functions.
//

#ifndef N_BODIES_BH_BODY_H
#define N_BODIES_BH_BODY_H

class Body {
public:
    // Softener for calculations
    static const double SOFTENER;
    static const double GRAVITY_CONST;
    // Body physical properties
    double pos_x, pos_y;
    double vel_x, vel_y;
    double force_x, force_y;
    double mass;

    // Body instance constructor
    // (pos_x pos_y) - body position in 2D
    // mass - body mass
    // (vel_x, vel_y) - body velocity vector
    Body(double pos_x, double pos_y, double mass, double vel_x = 0, double vel_y = 0);

    // Calculate a body force to another body
    void force_to(Body* b);
};

#endif //N_BODIES_BH_BODY_H
