//
// Created by Žilvinas
// Knight's Tour problem solver using
// the non-recursive backtracking method.
// Algorithm analysis, 2016-04-28, VU MIF
//

//home/zilvinas/ClionProjects/knights_tour/knight.log

#include "KnightsTour.h"
#include "Test.h"
#include <string>

int main(int argc, char** argv) {
    if (argc == 5) {
        int n = atoi(argv[2]);
        int p = atoi(argv[3]) - 1;
        int q = atoi(argv[4]) - 1;
        if (n == 0 || p == -1 || q == -1) {
			std::cout << "Bad input" << std::endl;
			return 1;
		}

        KnightsTour *kt = new KnightsTour(n);

        std::string bck = "bck";
        std::string wff = "wff";
        if (bck == argv[1]) {
            if (kt->solve_backtrack(p, q)) {
                kt->print_board();
            } else {
                std::cout << "No solution" << std::endl;
            }
        }
        if (wff == argv[1]) {
            if (kt->solve_warnsdorff(p, q)) {
                kt->print_board();
            } else {
                std::cout << "No solution" << std::endl;
            }
        }
        return 0;
    }
    if (argc == 6) {
        std::ofstream log;
        log.open(argv[5]);
        if (!log) {
			std::cout << "Bad log file" << std::endl;
			return 1;
		}
        // Run the tests
        Test tests = Test(&log);
        tests.run_start_cell_tests();
        return 0;
    }
    std::cout << "Bad input. Use: ./knights_tour bck|wff n p q [log]" << std::endl;
    return 1;
}
