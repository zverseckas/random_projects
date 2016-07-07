//
// Created by zilvinas on 16.5.2.
//

#ifndef KNIGHTS_TOUR_TEST_H
#define KNIGHTS_TOUR_TEST_H

#include <iostream>
#include <fstream>
#include <vector>

class Test {
    std::ostream *stream;
public:
    Test(std::ostream *stream = &std::clog);
    bool run_test_cases(void);
    bool run_start_cell_tests(void);
    bool test_case_1(void);
    bool test_case_2(void);
    bool test_case_3(void);
    bool test_case_4(void);
    bool test_case_5(void);
    bool test_case_6(void);
    bool test_case_7(void);
    bool test_case_8(void);
    bool test_case_9(void);
    bool test_case_10(void);
    bool test_case_11(void);
    bool test_case_12(void);
};

#endif //KNIGHTS_TOUR_TEST_H
