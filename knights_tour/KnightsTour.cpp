//
// Created by Žilvinas
// Knight's Tour problem solver using
// the non-recursive backtracking method.
// Algorithm analysis, 2016-04-28, VU MIF
//

#include <iomanip>
#include <vector>
#include <sys/time.h>

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

#define ROW        0
#define COL        1

typedef unsigned long long timestamp_t;
static timestamp_t get_timestamp() {
    struct timeval now;
    gettimeofday(&now, NULL);
    return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

KnightsTour::KnightsTour(int size) {
    n = size > 0 ? size : 5;
    board = new int*[n];
    clean();
}

void KnightsTour::clean(void) {
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

KnightsTour::State::State(int row, int col, int dir) {
    this->row = row;
    this->col = col;
    this->dir = dir;
}

KnightsTour::State::State() {
    this->row = 0;
    this->col = 0;
    this->dir = 0;
}

void KnightsTour::print_board(std::ostream& stream) {
    int width = 1; int tmp = n * n;
    for(; tmp != 0; tmp /= 10, width++);
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            stream << std::setw(width) << board[row][col];
        }
        stream << std::endl;
    }
}

bool KnightsTour::solve_backtrack(int row, int col) {
    // No solution if the initial state is out of board bounds
    if (row < 0 || row >= n || col < 0 || col >= n) return false;
    clean();

    // Create a knight's tour tracker
    int tracker = 0;
    board[row][col] = ++tracker;

    // Set the initial direction
    State state(row, col, LEFT_UP);
    // Push the initial state on stack
    stack.push(state);

    timestamp_t t1 = get_timestamp();
    // While we have not visited all the cells on a single tour
    // and the tracking stack is not empty, do
    while (tracker < n * n && !stack.empty()) {
        timestamp_t t2 = get_timestamp();
        if ((t2 - t1) / 1000000.0L > 180) break;
        // Get the last state
        state = stack.top();
        // Set up the next-to-come state
        State new_state;

        // While we are not done and there are moves to make, move and increase the direction
        while(state.dir < ALL_DONE && !can_move(state.row, state.col, state.dir, &new_state)) {
            state.dir++;
        }

        // If there are no moves but we are not done yet
        if (state.dir != ALL_DONE) {
            // Pop the last state
            stack.pop();
            // Increase the direction
            state.dir++;
            // Save the updated state
            stack.push(state);
            // Mark the board cell as visited
            board[new_state.row][new_state.col] = ++tracker;
            // Update the old state with the new one
            state.row = new_state.row; state.col = new_state.col; state.dir = LEFT_UP;
            // Push the new state on stack
            stack.push(state);
        } else {
            // If there was no successful tour found
            // Pop the current state
            stack.pop();
            // Reset the board cell
            board[state.row][state.col] = 0;
            // Backtrack
            tracker--;
        }
    }
    // If all the paths have been tried and the
    // tracker indicated all the cells as visited
    // return true, else false (no solution)
    return tracker == n * n;
}

bool KnightsTour::solve_warnsdorff(int row, int col) {
    // Child move's priority queue by children number
    std::vector<int> queue;
    // Moves index queue
    std::vector<int> indexes;
    // No solution if the initial state is out of board bounds
    if (row < 0 || row >= n || col < 0 || col >= n) return false;
    clean();

    int k = 0;
    // While we have not visited all the cells on a single tour
    while(k < n * n) {
        // Mark a step on board
        board[row][col] = ++k;
        // Clean the priority queue
        queue.clear();
        // Clean the indexes queue
        indexes.clear();

        // At each step check the 8 possible moves
        for(int i = 0; i < 8; i++) {
            // The next-to-come state
            int new_row = row + moves[i][ROW];
            int new_col = col + moves[i][COL];

            // Go to next step if the move is out of bounds
            if (new_row < 0 || new_row >= n || new_col < 0 || new_col >= n) {
                continue;
            }

            // Go to the next step if the move has been visited before
            if (board[new_row][new_col] != 0) {
                continue;
            }

            // Look to the next-to-come state's 8 possible moves
            int counter = 0;
            for (int j = 0; j < 8; j++) {
                // The next-to-come state's next-to-come state
                int new_col_child = new_col + moves[j][ROW];
                int new_row_child = new_row + moves[j][COL];

                // Go to next step if the move is out of bounds
                if (new_row_child < 0 || new_row_child >= n || new_col_child < 0 || new_col_child >= n) {
                    continue;
                }

                // Count the number of availible moves
                if(board[new_row_child][new_col_child] == 0) {
                    counter++;
                }
            }

            queue.push_back(counter);
            indexes.push_back(i);
        }

        // No possible moves
        if (queue.empty()) {
            break;
        }

        // Find a move with minimum child moves
        int min = queue[0]; int index_min = 0;
        for (int i = 0; i != queue.size(); i++) {
            if(queue[i] < min) {
                min = queue[i];
                index_min = i;
            }
        }

        // Make a move with minimum child moves
        row += moves[indexes[index_min]][ROW];
        col += moves[indexes[index_min]][COL];
    }
    // If all the paths have been tried and the
    // tracker indicated all the cells as visited
    // return true, else false (no solution)
    return k == n * n;
}

bool KnightsTour::can_move(int row, int col, int dir, State *state) {
    switch (dir) {
        case LEFT_UP:
            if (row > 0 && col > 1 && board[row - 1][col - 2] == 0) {
                state->row = row - 1; state->col = col - 2; return true;
            }
            return false;
        case UP_LEFT:
            if (row > 1 && col > 0 && board[row - 2][col - 1] == 0) {
                state->row = row - 2; state->col = col - 1; return true;
            }
            return false;
        case UP_RIGHT:
            if (row > 1 && col < n - 1 && board[row - 2][col + 1] == 0) {
                state->row = row - 2; state->col = col + 1; return true;
            }
            return false;
        case RIGHT_UP:
            if (row > 0 && col < n - 2 && board[row - 1][col + 2] == 0) {
                state->row = row - 1; state->col = col + 2; return true;
            }
            return false;
        case RIGHT_DOWN:
            if (row < n - 1 && col < n - 2 && board[row + 1][col + 2] == 0) {
                state->row = row + 1; state->col = col + 2; return true;
            }
            return false;
        case DOWN_RIGHT:
            if (row < n - 2 && col < n - 1 && board[row + 2][col + 1] == 0) {
                state->row = row + 2; state->col = col + 1; return true;
            }
            return false;
        case DOWN_LEFT:
            if (row < n - 2 && col > 0 && board[row + 2][col - 1] == 0) {
                state->row = row + 2; state->col = col - 1; return true;
            }
            return false;
        case LEFT_DOWN:
            if (row < n - 1 && col > 1 && board[row + 1][col - 2] == 0) {
                state->row = row + 1; state->col = col - 2; return true;
            }
            return false;
        default:
            return false;
    }
}
