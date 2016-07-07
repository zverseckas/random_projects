//
// Created by zilvinas on 16.5.2.
//
#include <sys/time.h>

#include "Test.h"
#include "KnightsTour.h"

// Timestamp for testing speed
typedef unsigned long long timestamp_t;
static timestamp_t get_timestamp() {
    struct timeval now;
    gettimeofday(&now, NULL);
    return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

Test::Test(std::ostream *stream) {
    this->stream = stream;
}
bool Test::run_start_cell_tests(void) {
  *stream << "Solving using the BACKTRACKING METHOD..." << std::endl;

  timestamp_t t1;
  bool status_back;
  timestamp_t t2;

  int size = 8;
  KnightsTour *board = new KnightsTour(size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      t1 = get_timestamp();
      *stream << "Solving for " << size <<"x" << size << " on " << "(" << i+1 << "," << j+1 << ")" << std::endl;
      status_back = board->solve_backtrack(i, j);
      t2 = get_timestamp();
      if (status_back) {
          *stream << "Solution:" << std::endl;
          board->print_board(*stream);
      } else {
          *stream << "No solution" << std::endl;
      }
      *stream << "Duration: " << (t2 - t1) / 1000000.0L << " s" << std::endl;
    }
  }
  return true;
}

bool Test::run_test_cases(void) {
    int result = 0;
    if (test_case_1()) result++;
    if (test_case_2()) result++;
    if (test_case_3()) result++;
    if (test_case_4()) result++;
    if (test_case_5()) result++;
    if (test_case_6()) result++;
    if (test_case_7()) result++;
    if (test_case_8()) result++;
    if (test_case_9()) result++;
    if (test_case_10()) result++;
    if (test_case_11()) result++;
    if (test_case_12()) result++;
    *stream << "Tests DONE. STATUS: " << (result == 12 ? "SUCCESS" : "FAILURE") << std::endl;
    *stream << "SUCCESSFUL RUNS " << result << "/" << 12 << std::endl;
    return result > 0;
}

bool Test::test_case_1(void) {
    *stream << "Test Case 1 STARTS. Board size 4. Start at (0, 0)." << std::endl;
    *stream << "Testing if the solution does not exist." << std::endl;

    KnightsTour *board = new KnightsTour(4);

    *stream << "Solving using the BACKTRACKING METHOD..." << std::endl;

    timestamp_t t1 = get_timestamp();
    bool status_back = board->solve_backtrack(0, 0);
    timestamp_t t2 = get_timestamp();

    if (status_back) {
        *stream << "Solution:" << std::endl;
        board->print_board(*stream);
    } else {
        *stream << "No solution" << std::endl;
    }

    *stream << "Duration: " << (t2 - t1) / 1000000.0L << " s" << std::endl;

    *stream << "Solving using the WARNSDORFF'S RULE..." << std::endl;

    timestamp_t t3 = get_timestamp();
    bool status_warn = board->solve_warnsdorff(0, 0);
    timestamp_t t4 = get_timestamp();

    if (status_warn) {
        *stream << "Solution:" << std::endl;
        board->print_board(*stream);
    } else {
        *stream << "No solution" << std::endl;
    }

    *stream << "Duration: " << (t4 - t3) / 1000000.0L << " s" << std::endl;

    delete board;

    *stream << "Test Case 1 ENDS with " << (status_back && status_warn ? "FAILURE" : "SUCCESS") << std::endl;
    *stream << "Duration: " << (t4 - t1) / 1000000.0L << " s" << std::endl << std::endl;

    return !(status_back && status_warn);
}

bool Test::test_case_2(void) {
    *stream << "Test Case 2 STARTS. Board size 5. Start at (4, 4)." << std::endl;
    *stream << "Testing if the solution exists." << std::endl;

    KnightsTour *board = new KnightsTour(5);

    *stream << "Solving using the BACKTRACKING METHOD..." << std::endl;
    timestamp_t t1 = get_timestamp();
    bool status_back = board->solve_backtrack(4, 4);
    timestamp_t t2 = get_timestamp();

    if (status_back) {
        *stream << "Solution:" << std::endl;
        board->print_board(*stream);
    } else {
        *stream << "No solution" << std::endl;
    }
    *stream << "Duration: " << (t2 - t1) / 1000000.0L << " s" << std::endl;

    *stream << "Solving using the WARNSDORFF'S RULE..." << std::endl;

    timestamp_t t3 = get_timestamp();
    bool status_warn = board->solve_warnsdorff(4, 4);
    timestamp_t t4 = get_timestamp();

    if (status_warn) {
        *stream << "Solution:" << std::endl;
        board->print_board(*stream);
    } else {
        *stream << "No solution" << std::endl;
    }
    *stream << "Duration: " << (t4 - t3) / 1000000.0L << " s" << std::endl;

    delete board;

    *stream << "Test Case 2 ENDS with " << (status_back && status_warn ? "SUCCESS" : "FAILURE") << std::endl;
    *stream << "Duration: " << (t4 - t1) / 1000000.0L << " s" << std::endl << std::endl;

    return status_back && status_warn;
}

bool Test::test_case_3(void) {
    *stream << "Test Case 3 STARTS. Board size 5. Start at (1, 1)." << std::endl;
    *stream << "Testing if the solution does not exist." << std::endl;

    KnightsTour *board = new KnightsTour(5);

    *stream << "Solving using the BACKTRACKING METHOD..." << std::endl;

    timestamp_t t1 = get_timestamp();
    bool status_back = board->solve_backtrack(0, 1);
    timestamp_t t2 = get_timestamp();

    if (status_back) {
        *stream << "Solution:" << std::endl;
        board->print_board(*stream);
    } else {
        *stream << "No solution" << std::endl;
    }

    *stream << "Duration: " << (t2 - t1) / 1000000.0L << " s" << std::endl;

    *stream << "Solving using the WARNSDORFF'S RULE..." << std::endl;

    timestamp_t t3 = get_timestamp();
    bool status_warn = board->solve_warnsdorff(0, 1);
    timestamp_t t4 = get_timestamp();

    if (status_warn) {
        *stream << "Solution:" << std::endl;
        board->print_board(*stream);
    } else {
        *stream << "No solution" << std::endl;
    }

    *stream << "Duration: " << (t4 - t3) / 1000000.0L << " s" << std::endl;

    delete board;

    *stream << "Test Case 3 ENDS with " << (status_back && status_warn ? "FAILURE" : "SUCCESS") << std::endl;
    *stream << "Duration: " << (t4 - t1) / 1000000.0L << " s" << std::endl << std::endl;

    return !(status_back && status_warn);
}

bool Test::test_case_4(void) {
    *stream << "Test Case 4 STARTS. Board size 6. Start at (5, 5)." << std::endl;
    *stream << "Testing if the solution exists." << std::endl;

    KnightsTour *board = new KnightsTour(6);

    *stream << "Solving using the BACKTRACKING METHOD..." << std::endl;
    timestamp_t t1 = get_timestamp();
    bool status_back = board->solve_backtrack(5, 5);
    timestamp_t t2 = get_timestamp();

    if (status_back) {
        *stream << "Solution:" << std::endl;
        board->print_board(*stream);
    } else {
        *stream << "No solution" << std::endl;
    }
    *stream << "Duration: " << (t2 - t1) / 1000000.0L << " s" << std::endl;

    *stream << "Solving using the WARNSDORFF'S RULE..." << std::endl;

    timestamp_t t3 = get_timestamp();
    bool status_warn = board->solve_warnsdorff(5, 5);
    timestamp_t t4 = get_timestamp();

    if (status_warn) {
        *stream << "Solution:" << std::endl;
        board->print_board(*stream);
    } else {
        *stream << "No solution" << std::endl;
    }
    *stream << "Duration: " << (t4 - t3) / 1000000.0L << " s" << std::endl;

    delete board;

    *stream << "Test Case 4 ENDS with " << (status_back && status_warn ? "SUCCESS" : "FAILURE") << std::endl;
    *stream << "Duration: " << (t4 - t1) / 1000000.0L << " s" << std::endl << std::endl;

    return status_back && status_warn;
}

bool Test::test_case_5(void) {
    *stream << "Test Case 5 STARTS. Board size 7. Start at (0, 0)." << std::endl;
    *stream << "Testing if the solution exists." << std::endl;
    KnightsTour *board = new KnightsTour(7);

    *stream << "Solving using the BACKTRACKING METHOD..." << std::endl;
    timestamp_t t1 = get_timestamp();
    bool status_back = board->solve_backtrack(0, 0);
    timestamp_t t2 = get_timestamp();

    if (status_back) {
        *stream << "Solution:" << std::endl;
        board->print_board(*stream);
    } else {
        *stream << "No solution" << std::endl;
    }
    *stream << "Duration: " << (t2 - t1) / 1000000.0L << " s" << std::endl;

    *stream << "Solving using the WARNSDORFF'S RULE..." << std::endl;

    timestamp_t t3 = get_timestamp();
    bool status_warn = board->solve_warnsdorff(0, 0);
    timestamp_t t4 = get_timestamp();

    if (status_warn) {
        *stream << "Solution:" << std::endl;
        board->print_board(*stream);
    } else {
        *stream << "No solution" << std::endl;
    }
    *stream << "Duration: " << (t4 - t3) / 1000000.0L << " s" << std::endl;

    delete board;

    *stream << "Test Case 5 ENDS with " << (status_back && status_warn ? "SUCCESS" : "FAILURE") << std::endl;
    *stream << "Duration: " << (t4 - t1) / 1000000.0L << " s" << std::endl << std::endl;

    return status_back && status_warn;
}

bool Test::test_case_6(void) {
    *stream << "Test Case 6 STARTS. Board size 7. Start at (6, 6)." << std::endl;
    *stream << "Testing if the solution exists." << std::endl;
    KnightsTour *board = new KnightsTour(7);

    *stream << "Solving using the BACKTRACKING METHOD..." << std::endl;
    timestamp_t t1 = get_timestamp();
    bool status_back = board->solve_backtrack(6, 6);
    timestamp_t t2 = get_timestamp();

    if (status_back) {
        *stream << "Solution:" << std::endl;
        board->print_board(*stream);
    } else {
        *stream << "No solution" << std::endl;
    }
    *stream << "Duration: " << (t2 - t1) / 1000000.0L << " s" << std::endl;

    *stream << "Solving using the WARNSDORFF'S RULE..." << std::endl;

    timestamp_t t3 = get_timestamp();
    bool status_warn = board->solve_warnsdorff(6, 6);
    timestamp_t t4 = get_timestamp();

    if (status_warn) {
        *stream << "Solution:" << std::endl;
        board->print_board(*stream);
    } else {
        *stream << "No solution" << std::endl;
    }
    *stream << "Duration: " << (t4 - t3) / 1000000.0L << " s" << std::endl;

    delete board;

    *stream << "Test Case 6 ENDS with " << (status_back && status_warn ? "SUCCESS" : "FAILURE") << std::endl;
    *stream << "Duration: " << (t4 - t1) / 1000000.0L << " s" << std::endl << std::endl;

    return status_back && status_warn;
}

bool Test::test_case_7(void) {
    *stream << "Test Case 7 STARTS. Board size 6. Start at (1, 1)." << std::endl;
    *stream << "Testing if the solution exists." << std::endl;
    KnightsTour *board = new KnightsTour(6);

    *stream << "Solving using the BACKTRACKING METHOD..." << std::endl;
    timestamp_t t1 = get_timestamp();
    bool status_back = board->solve_backtrack(1, 1);
    timestamp_t t2 = get_timestamp();

    if (status_back) {
        *stream << "Solution:" << std::endl;
        board->print_board(*stream);
    } else {
        *stream << "No solution" << std::endl;
    }
    *stream << "Duration: " << (t2 - t1) / 1000000.0L << " s" << std::endl;

    *stream << "Solving using the WARNSDORFF'S RULE..." << std::endl;

    timestamp_t t3 = get_timestamp();
    bool status_warn = board->solve_warnsdorff(1, 1);
    timestamp_t t4 = get_timestamp();

    if (status_warn) {
        *stream << "Solution:" << std::endl;
        board->print_board(*stream);
    } else {
        *stream << "No solution" << std::endl;
    }
    *stream << "Duration: " << (t4 - t3) / 1000000.0L << " s" << std::endl;

    delete board;

    *stream << "Test Case 7 ENDS with " << (status_back && status_warn ? "SUCCESS" : "FAILURE") << std::endl;
    *stream << "Duration: " << (t4 - t1) / 1000000.0L << " s" << std::endl << std::endl;

    return status_back && status_warn;
}

bool Test::test_case_8(void) {
    *stream << "Test Case 8 STARTS. Board size 6. Start at (2, 3)." << std::endl;
    *stream << "Testing if the solution exists." << std::endl;
    KnightsTour *board = new KnightsTour(6);

    *stream << "Solving using the BACKTRACKING METHOD..." << std::endl;
    timestamp_t t1 = get_timestamp();
    bool status_back = board->solve_backtrack(2, 3);
    timestamp_t t2 = get_timestamp();

    if (status_back) {
        *stream << "Solution:" << std::endl;
        board->print_board(*stream);
    } else {
        *stream << "No solution" << std::endl;
    }
    *stream << "Duration: " << (t2 - t1) / 1000000.0L << " s" << std::endl;

    *stream << "Solving using the WARNSDORFF'S RULE..." << std::endl;

    timestamp_t t3 = get_timestamp();
    bool status_warn = board->solve_warnsdorff(2, 3);
    timestamp_t t4 = get_timestamp();

    if (status_warn) {
        *stream << "Solution:" << std::endl;
        board->print_board(*stream);
    } else {
        *stream << "No solution" << std::endl;
    }
    *stream << "Duration: " << (t4 - t3) / 1000000.0L << " s" << std::endl;

    delete board;

    *stream << "Test Case 8 ENDS with " << (status_back && status_warn ? "SUCCESS" : "FAILURE") << std::endl;
    *stream << "Duration: " << (t4 - t1) / 1000000.0L << " s" << std::endl << std::endl;

    return status_back && status_warn;
}

bool Test::test_case_9(void) {
    *stream << "Test Case 9 STARTS. Board size 8. Start at (7, 7)." << std::endl;
    *stream << "Testing if the solution exists." << std::endl;
    KnightsTour *board = new KnightsTour(8);

    *stream << "Solving using the BACKTRACKING METHOD..." << std::endl;
    timestamp_t t1 = get_timestamp();
    bool status_back = board->solve_backtrack(7, 7);
    timestamp_t t2 = get_timestamp();

    if (status_back) {
        *stream << "Solution:" << std::endl;
        board->print_board(*stream);
    } else {
        *stream << "No solution" << std::endl;
    }
    *stream << "Duration: " << (t2 - t1) / 1000000.0L << " s" << std::endl;

    *stream << "Solving using the WARNSDORFF'S RULE..." << std::endl;

    timestamp_t t3 = get_timestamp();
    bool status_warn = board->solve_warnsdorff(7, 7);
    timestamp_t t4 = get_timestamp();

    if (status_warn) {
        *stream << "Solution:" << std::endl;
        board->print_board(*stream);
    } else {
        *stream << "No solution" << std::endl;
    }
    *stream << "Duration: " << (t4 - t3) / 1000000.0L << " s" << std::endl;

    delete board;

    *stream << "Test Case 9 ENDS with " << (status_back && status_warn ? "SUCCESS" : "FAILURE") << std::endl;
    *stream << "Duration: " << (t4 - t1) / 1000000.0L << " s" << std::endl << std::endl;

    return status_back && status_warn;
}

bool Test::test_case_10(void) {
    *stream << "Test Case 10 STARTS. Board size 16. Start at (7, 7)." << std::endl;
    *stream << "Testing if the solution exists." << std::endl;
    KnightsTour *board = new KnightsTour(16);

    *stream << "Solving using the WARNSDORFF'S RULE..." << std::endl;

    timestamp_t t1 = get_timestamp();
    bool status_warn = board->solve_warnsdorff(7, 7);
    timestamp_t t2 = get_timestamp();

    if (status_warn) {
        *stream << "Solution:" << std::endl;
        board->print_board(*stream);
    } else {
        *stream << "No solution" << std::endl;
    }
    *stream << "Duration: " << (t2 - t1) / 1000000.0L << " s" << std::endl;

    delete board;

    *stream << "Test Case 10 ENDS with " << (status_warn ? "SUCCESS" : "FAILURE") << std::endl;
    *stream << "Duration: " << (t2 - t1) / 1000000.0L << " s" << std::endl << std::endl;

    return status_warn;
}

bool Test::test_case_11(void) {
    *stream << "Test Case 10 STARTS. Board size 32. Start at (7, 7)." << std::endl;
    *stream << "Testing if the solution exists." << std::endl;
    KnightsTour *board = new KnightsTour(32);

    *stream << "Solving using the WARNSDORFF'S RULE..." << std::endl;

    timestamp_t t1 = get_timestamp();
    bool status_warn = board->solve_warnsdorff(7, 7);
    timestamp_t t2 = get_timestamp();

    if (status_warn) {
        *stream << "Solution:" << std::endl;
        board->print_board(*stream);
    } else {
        *stream << "No solution" << std::endl;
    }
    *stream << "Duration: " << (t2 - t1) / 1000000.0L << " s" << std::endl;

    delete board;

    *stream << "Test Case 11 ENDS with " << (status_warn ? "SUCCESS" : "FAILURE") << std::endl;
    *stream << "Duration: " << (t2 - t1) / 1000000.0L << " s" << std::endl << std::endl;

    return status_warn;
}

bool Test::test_case_12(void) {
    *stream << "Test Case 12 STARTS. Board size 128. Start at (0, 0)." << std::endl;
    *stream << "Testing if the solution exists." << std::endl;
    KnightsTour *board = new KnightsTour(128);

    *stream << "Solving using the WARNSDORFF'S RULE..." << std::endl;

    timestamp_t t1 = get_timestamp();
    bool status_warn = board->solve_warnsdorff(0, 0);
    timestamp_t t2 = get_timestamp();

    if (status_warn) {
        *stream << "Solution:" << std::endl;
        board->print_board(*stream);
    } else {
        *stream << "No solution" << std::endl;
    }
    *stream << "Duration: " << (t2 - t1) / 1000000.0L << " s" << std::endl;

    delete board;

    *stream << "Test Case 12 ENDS with " << (status_warn ? "SUCCESS" : "FAILURE") << std::endl;
    *stream << "Duration: " << (t2 - t1) / 1000000.0L << " s" << std::endl << std::endl;

    return status_warn;
}
