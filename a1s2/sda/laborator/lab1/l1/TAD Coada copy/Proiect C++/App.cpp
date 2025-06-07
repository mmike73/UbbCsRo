#include <iostream>
#include "Coada.h"
#include "TestExtins.h"
#include "TestScurt.h"
#include <assert.h>
using namespace std;

bool test(Coada c) {
    c.adauga(5);
    c.adauga(2);
    c.adauga(56);
    c.adauga(2);
    c.adauga(8);
    c.adauga(99);
    c.adauga(100000);
    int minim = c.stergeMinim();
    assert(minim == 2);
    minim = c.stergeMinim();
    assert(minim == 2);
    minim = c.stergeMinim();
    assert(minim == 5);
    minim = c.stergeMinim();
    assert(minim == 8);
    minim = c.stergeMinim();
    assert(minim == 56);
    minim = c.stergeMinim();
    assert(minim == 99);
    minim = c.stergeMinim();
    assert(minim == 100000);
}

int main() {
	testAll();
	testAllExtins();
    Coada c;
    test(c);
    cout << "It works.";
	return 0;
}
