//
// Created by Mihai Moldovan on 21.06.2024.
//
#include <iostream>
using namespace std;

class A {
public:
    virtual void print() {
        cout << "printA" << endl;
    }
    ~A() {
        cout << "~A" << endl;
    }
};

class B: public A {
public:
    void print() {
        cout << "printB" << endl;
    }

    virtual ~B() {
        cout << "~B" << endl;
    }
};

int main() {
    A* o1 = new A;
    A* o2 = new B;
    o1->print();
    o2->print();
    delete o1;
    delete o2;
    return 0;
}