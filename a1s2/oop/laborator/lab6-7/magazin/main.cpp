#include "repo.h"
#include "validation.h"
#include "service.h"
#include "ui.h"
#include "tests.h"

void start() {
    ProduseRepo repo;
    Validation validare;
    ServiceProduse service{repo, validare};
    UI ui{service};
    ui.run();
}

int main() {
    Tests t;
    t.run_all_tests();
    start();
}
