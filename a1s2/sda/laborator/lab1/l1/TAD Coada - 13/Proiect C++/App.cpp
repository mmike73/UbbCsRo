#include <iostream>
#include "Coada.h"
#include "TestExtins.h"
#include "TestScurt.h"
using namespace std;


int main() {
	testAll();
	testAllExtins();
	cout << "It works.";
    Coada c;
    c.adauga(5);
    c.adauga(1);
    c.adauga(10);
	return 0;
}
