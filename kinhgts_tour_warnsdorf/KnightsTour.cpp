//
// Created by Žilvinas
// Knight's Tour problem solver using
// the non-recursive backtracking method.
// Algorithm analysis, 2016-04-28, VU MIF
//

#include <iostream>
#include <iomanip>
#include <vector>

#include "KnightsTour.h"

// Directions for a knight
#define LEFT_UP    1
#define UP_LEFT    2
#define UP_RIGHT   3
#define RIGHT_UP   4
#define RIGHT_DOWN 5
#define DOWN_RIGHT 6
#define DOWN_LEFT  7
#define LEFT_DOWN  8
#define ALL_DONE   9

KnightsTour::KnightsTour(int size) {
    n = size > 0 ? size : 5;
    board = new int*[n];
    // Initialize the board with zeroes
    for (int row = 0 ; row < n ; row++) {
        board[row] = new int[n];
        for (int col = 0; col < n; col++) {
            board[row][col] = 0;
        }
    }
}

KnightsTour::~KnightsTour() {
    for (int row = 0 ; row < n ; row++) {
        delete [] board[row];
    }
    delete [] board;
}

void KnightsTour::print_board(void) {
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            std::cout << std::setw(4) << board[col][row];
        }
        std::cout << std::endl;
    }
}

bool KnightsTour::solve(int row, int col) {
    std::vector<int> pq;
    std::vector<int> idx;

    int nx;
    int ny;

    int ex;
    int ey;

    int ctr;

    int min;
    int imin;

    int i, j, k, cy, cx;

    for(k = 0; k < n * n; k++) {
        board[col][row] = k + 1;
        pq.clear();
        idx.clear();
        for(i = 0; i < 8; i++) {
            nx = row + moves[i][0];
            ny = col + moves[i][1];
            if((nx >= 0 && nx < n) && (ny >=0 && ny < n)) {
                if(board[ny][nx] == 0) {
                    ctr = 0;
                    for(int j = 0; j < 8; j++) {
                        ex = nx + moves[j][0];
                        ey = ny + moves[j][1];
                        if((ex >= 0 && ex < n) && (ey >= 0 && ey < n)) {
                            if(board[ey][ex] == 0) {
                                ctr++;
                            }
                        }
                    }
                    pq.push_back(ctr);
                    idx.push_back(i);
                }
            }
        }
        if (!pq.empty()){
            for(int it = 0; it != pq.size(); it++) {
                if(it == 0) {
                    min = pq[it];
                    imin = it;
                    // log << pq[it] << " " << it << endl;
                } else {
                    if(pq[it] < min) {
                        min = pq[it];
                        imin = it;
                        // log << pq[it] << " " << it << endl;
                    }
                }
            }
            row += moves[idx[imin]][0];
            col += moves[idx[imin]][1];
        }
        else {
            break;
        }
    }
    return true;
}