//
// Created by Mihai Moldovan on 18.06.2024.
//

#ifndef PROJECT_TEST_H
#define PROJECT_TEST_H
#include "domain.h"
#include "repo.h"
#include "service.h"
#include <assert.h>

class Test {
private:
    void test_domain();
    void test_repo();
    void test_service();
public:
    void test_all();
};


#endif //PROJECT_TEST_H
