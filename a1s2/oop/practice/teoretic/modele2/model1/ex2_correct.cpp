#include <vector>
#include <iostream>
#include <memory>

class A {
public:
    virtual void print() = 0;
    virtual ~A() = default; // Add a virtual destructor
};

class B : public A {
public:
    virtual void print() override {
        std::cout << "printB";
    }
};

class C : public B {
public:
    virtual void print() override {
        std::cout << "printC";
    }
};

int main() {
    std::vector<std::unique_ptr<A> > v; // Use a vector of unique_ptr to A
    v.push_back(std::make_unique<B>());
    v.push_back(std::make_unique<C>());

    for (auto& e : v) {
        e->print(); // Use -> to call the print function on the pointers
    }
    return 0;
}
