#include "repo.h"
#include "validation.h"
#include "service.h"
#include "ui.h"
#include "tests.h"
#include "cos_cumparaturi.h"

void start() {
    ProduseRepoFile repo{"/Volumes/D/Faculta/A1S2/OOP/labs/lab8-9/magazin/stoc"};
    Validation validare;
    CosCumparaturi cos_cumparaturi{repo};
    ServiceProduse service{repo, validare, cos_cumparaturi};
    UI ui(service);
    ui.run();
}

int main() {
    Tests t;
    t.run_all_tests();
    start();
}
