#include <iostream>
#include <chrono>
#include "../Teste/TestExtins.h"
#include "../Teste/TestScurt.h"
using namespace std;
using namespace std::chrono;


int main() {
    auto start = high_resolution_clock::now();
	testAll();
    testAllExtins();
	cout<<"End";
    auto finish = high_resolution_clock::now();
    cout << "Took " << duration_cast<seconds>(finish-start).count()  << " seconds.\n";
}
