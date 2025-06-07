#include <iostream>
#include <chrono>
#include "../Teste/TestExtins.h"
#include "../Teste/TestScurt.h"
#include "Colectie.h"
#include <assert.h>
using namespace std;
using namespace std::chrono;


int main() {
    auto start = high_resolution_clock::now();
	testAll();
    testAllExtins();

	cout<<"End\n";
    auto finish = high_resolution_clock::now();
    cout << "Took " << duration_cast<seconds>(finish-start).count()  << " seconds.\n";
    //Took 40 seconds.

    Colectie c;
    assert(c.diferentaMaxMin() == -1);
    c.adauga(1);
    assert(c.diferentaMaxMin() ==0);
    c.adauga(2);
    assert(c.diferentaMaxMin() == 1);
    c.adauga(7);
    assert(c.diferentaMaxMin() == 6);
    c.adauga(9);
    assert(c.diferentaMaxMin() == 8);
    c.adauga(-100);
    assert(c.diferentaMaxMin() == 109);

    return 0;
}
