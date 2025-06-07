#include <vector>
#include <iostream>

class A {
public:
    virtual void print() = 0;
};

class B: public A {
public:
    virtual void print() {
        std::cout << "printB";
    }
};

class C: public B {
public:
    virtual void print() {
        std::cout << "printC";
    }
};

int main() {
    std::vector<A> v;
    B b;
    C c;
    v.push_back(b);
    v.push_back(c);
    for(auto& e: v) {
        e.print();
    }
    return 0;
}
