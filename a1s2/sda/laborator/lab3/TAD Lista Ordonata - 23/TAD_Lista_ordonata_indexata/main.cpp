#include <iostream>
#include <assert.h>
#include <exception>

#include "Proiect C++/LO.h"
#include "Proiect C++/Iterator.h"

#include "Teste/TestScurt.h"
#include "Teste/TestExtins.h"

bool crescator(TElement c1, TElement c2) {
    if (c1 <= c2) {
        return true;
    } else {
        return false;
    }
}

void test_functionalitate() {
    LO lista(crescator);
    lista.adauga(0);
    lista.adauga(1);
    lista.adauga(2);
    lista.adauga(3);
    lista.adauga(4);
    lista.adauga(5);

    Iterator it = lista.iterator();
    assert(it.element() == 0);
    it.urmator();
    assert(it.element() == 1);
    it.urmator();
    assert(it.element() == 2);
    it.urmator();
    assert(it.element() == 3);
    it.avanseazaKPasi(3);

    try {
        it.avanseazaKPasi(9);
        assert(false);
    } catch( std::exception&) {
        assert(true);
    }


    try {
        it.avanseazaKPasi(0);
        assert(false);
    } catch( std::exception&) {
        assert(true);
    }

    try {
        it.avanseazaKPasi(-3);
        assert(false);
    } catch( std::exception&) {
        assert(true);
    }
}

int main(){
    testAll();
    testAllExtins();
    test_functionalitate();
    std::cout<<"Finished LI Tests!"<<std::endl;
}
