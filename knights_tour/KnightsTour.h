//
// Created by Žilvinas
// Knight's Tour problem solver using
// the non-recursive backtracking method.
// Algorithm analysis, 2016-04-28, VU MIF
//

#ifndef KNIGHTS_TOUR_KNIGHTSTOUR_H
#define KNIGHTS_TOUR_KNIGHTSTOUR_H

#include <stack>
#include <fstream>
#include <iostream>

// Class represents the Knight's Tour problem solver.
// After constructing the board call the solve method
// providing the initial cell. If the solve method returns
// true, the tour was found, try to print it.
class KnightsTour {
private:

    // Class represents the current state of a knight
    class State {
    public:
        // Current column, row and direction
        int col, row, dir;
        State(int col, int row, int dir);
        State();

    };

    // Moves array for the Warnsdorff's rule
    int moves[8][2] = {{1,-2},{2,-1},{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2}};

    // We use a non-recursive method so we track the
    // tour lookup process using the std::stack
    std::stack<State> stack;

    int** board; // Dynamic size chess board
    int n;       // Size of a board

    // Checks if the are moves possible at a cell (row, col).
    // If so, saves the new state in a state parameter
    bool can_move(int row, int col, int dir, State *state);

public:

    // Initializes the board
    KnightsTour(int size = 5);

    // Destroys the board
    ~KnightsTour();

    // Prints the board with a tour on it
    void print_board(std::ostream& stream = std::cout);

    // Solves the problem starting at a cell (row, col)
    // Backtracking method
    bool solve_backtrack(int row, int col);

    // Solves the problem starting at a cell (row, col)
    // Warnsdorff's rule
    bool solve_warnsdorff(int row, int col);

    void clean(void);
};

#endif //KNIGHTS_TOUR_KNIGHTSTOUR_H
