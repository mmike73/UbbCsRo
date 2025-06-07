//
// Created by Mihai Moldovan on 21.06.2024.
//
#include <vector>
#include <iostream>
using namespace std;
class A {
public:
    virtual void f() = 0;
};

class B: public A {
public:
    void f() override {
        cout << "f din B";
    }
};

class C: public B {
public:
    void f() override {
        cout << "f din C";
    }
};
///schimbat in pointeri si merge
int main() {
    vector<A> v;
    B b;
    v.push_back(b);
    C c;
    v.push_back(c);
    //for(auto e: v) {
     //   e->f();
    //}
    return 0;
}