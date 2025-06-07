#include <stdio.h>
#include <stdlib.h>
#include "domain.h"
#include "service.h"
#include <unistd.h>
#include "tests.h"
#include "ui.h"
#include "repo.h"
#include "vector_dinamic.h"

void start() {
    VectorDinamic *r_c = creeaza_vector_dinamic();
    run(r_c);
}

int main() {
    run_all_tests();
    start();
}