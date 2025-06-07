//
// Created by Mihai Moldovan on 22.06.2024.
//

#ifndef PROJECT_TEST_H
#define PROJECT_TEST_H
#include <iostream>
#include <assert.h>

class Test {
public:
    void run_all();

private:
    void test_domain();
    void test_service();
    void test_repo();

};


#endif //PROJECT_TEST_H
