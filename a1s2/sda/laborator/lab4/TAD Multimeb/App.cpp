#include "Teste/TestExtins.h"
#include "Teste/TestScurt.h"
#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>
#include <assert.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main() {
    auto start = high_resolution_clock::now();
	testAll();
	testAllExtins();

    Multime m;
    m.adauga(1);
    m.adauga(2);
    m.adauga(3);
    m.adauga(4);
    m.adauga(5);
    m.adauga(6);

    assert(m.dim() == 6);
    IteratorMultime i = m.iterator();
    //elimina primul element
    assert(i.elimina() == 1);
    assert(m.dim() == 5);
    assert(i.element() == 2);
    assert(i.elimina() == 2);
    assert(m.dim() == 4);
    assert(i.element() == 3);
    i.urmator();
    //elimina element din interior
    assert(i.element() == 4);
    assert(i.elimina() == 4);
    assert(i.element() == 5);
    assert(m.dim() == 3);
    i.urmator();
    //elimina ultmul element
    assert(i.element() == 6);
    assert(i.elimina() == 6);
    assert(m.dim() == 2);
    //iterator invalid
    try {
        i.elimina();
    } catch( std::exception& e) {
        assert(true);
    }
    auto stop = high_resolution_clock::now();
    cout << "That's all!" << endl << "Took " << duration_cast<seconds>(stop - start).count() << " seconds." << endl;
    //Took 65 seconds.
}