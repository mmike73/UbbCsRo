#include <iostream>
using namespace std;

class A {
public:
    A() {
        cout << "A" << endl;
    }
    ~A() {
        cout << "~A" << endl;
    }
    void print() {
        cout << "print" << endl;
    }
};

void f() {
    A a[2]; //constructorul se apeleaza
    a[0].print();
}


int main() {
    f();
    return 0;
}
