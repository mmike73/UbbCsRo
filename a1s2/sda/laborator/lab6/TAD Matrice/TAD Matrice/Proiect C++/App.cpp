#include <iostream>
#include <assert.h>
#include "Matrice.h"
#include "../Teste/TestExtins.h"
#include "../Teste/TestScurt.h"

using namespace std;


int main() {

	testAll();
	testAllExtins();

    Matrice m(10,10);
    m.modifica(1,4,1);
    m.modifica(1,5,1);
    m.modifica(1,8,1);
    m.modifica(2,1,1);
    m.modifica(2,7,1);
    m.modifica(3,1,1);
    m.modifica(4,1,1);
    m.modifica(7,9,1);
    m.modifica(9,9,1);

    assert(m.numberOfNonZeroElements(1) == 3);
    assert(m.numberOfNonZeroElements(2) == 0);
    assert(m.numberOfNonZeroElements(3) == 0);
    assert(m.numberOfNonZeroElements(4) == 1);
    assert(m.numberOfNonZeroElements(5) == 1);
    assert(m.numberOfNonZeroElements(6) == 0);
    assert(m.numberOfNonZeroElements(8) == 1);
    try {
        m.numberOfNonZeroElements(234);
    } catch (exception& e) {
        assert(true);
    }
    cout<<"End";
}
