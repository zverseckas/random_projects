#include "Body.h"
#include <cmath>

const double Body::SOFTENER = 10;
const double Body::GRAVITY_CONST = 0.1;

Body::Body(double pos_x, double pos_y, double mass, double vel_x, double vel_y) {
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->vel_x = vel_x;
    this->vel_y = vel_y;
    this->mass = mass;
    force_x = force_y = 0;
}

void Body::force_to(Body* b) {
    // Positions difference vector
    double vec_x = b->pos_x - pos_x;
    double vec_y = b->pos_y - pos_y;

    // Proper Gravitational relation
    double dist_squared = vec_x * vec_x + vec_y * vec_y + Body::SOFTENER * Body::SOFTENER;
    double dist_sixth = dist_squared * dist_squared * dist_squared;
    double force = (mass * b->mass) / sqrt(dist_sixth) * Body::GRAVITY_CONST;

    // Update the body force
    force_x += vec_x * force;
    force_y += vec_y * force;
}