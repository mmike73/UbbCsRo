//
// Created by Mihai Moldovan on 19.06.2024.
//

#ifndef PROJECT_TEST_H
#define PROJECT_TEST_H
#include "service.h"
#include "validation.h"

class Test {
public:
    void test_all();
private:
    void test_domain();
    void test_repo();
    void test_service();
    void test_valid();
};


#endif //PROJECT_TEST_H
