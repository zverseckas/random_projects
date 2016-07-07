//
// Created by zilvinas on 16.3.20.
// Stellar simulator (N-BODY problem)
// Barnes-Hut approach + OMP parallelization
//

#include "Simulator.h"

int main(int argc, char** argv) {

    int thread_num = 4;
    if (argc == 2) {
        int tmp = atoi(argv[1]);
        if (tmp > 0) thread_num = tmp;
    }

    Simulator sim(5000, 1366, 768, thread_num, "Particle Swarm");
    sim.start();
    return 0;
}