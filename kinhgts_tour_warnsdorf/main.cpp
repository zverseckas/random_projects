//
// Created by Žilvinas
// Knight's Tour problem solver using
// the Wandorf's method.
// Algorithm analysis, 2016-04-28, VU MIF
//

#include "KnightsTour.h"
#include <iostream>

using namespace std;

int main(int arc, char** argv) {
    KnightsTour *board = new KnightsTour(5);
    if (board->solve(4,1)) {
        std::cout << "Solution:" << std::endl;
        board->print_board();
    } else {
        std::cout << "No solution" << std::endl;
    }
    delete board;
    return 0;
}