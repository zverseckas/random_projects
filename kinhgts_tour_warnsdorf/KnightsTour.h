//
// Created by zilvinas on 16.5.4.
//

#ifndef KINHGTS_TOUR_WARNSDORF_KNIGHTSTOUR_H
#define KINHGTS_TOUR_WARNSDORF_KNIGHTSTOUR_H

// Class represents the Knight's Tour problem solver.
// After constructing the board call the solve method
// providing the initial cell. If the solve method returns
// true, the tour was found, try to print it.
class KnightsTour {
private:

    int** board; // Dynamic size chess board
    int n;       // Size of a board
    int moves[8][2] = {{1,-2},{2,-1},{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2}};

public:

    // Initializes the board
    KnightsTour(int size = 5);

    // Destroys the board
    ~KnightsTour();

    // Prints the board with a tour on it
    void print_board(void);

    // Solves the problem starting at a cell (row, col)
    bool solve(int row, int col);
};

#endif //KINHGTS_TOUR_WARNSDORF_KNIGHTSTOUR_H
