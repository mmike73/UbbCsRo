#include "Iterator.h"
#include "LO.h"
#include <iostream>
#include <exception>
using namespace std;

//Theta(1)
Iterator::Iterator(const LO& lo) : lista(lo){
    curent = lo.prim;
}

//Theta(1)
void Iterator::prim() {
    curent = lista.prim;
}

//Theta(1)
void Iterator::urmator(){
    if(curent == nullptr) {
        throw runtime_error("Nu exista alt element!!!");
    }
    curent = curent->succesor();
}

//Theta(1)
bool Iterator::valid() const{
    if( curent != nullptr) return true;
    return false;
}

//Theta(1)
TElement Iterator::element() const{
    if( valid()) return curent->element();
    throw runtime_error("Element invalid!!!");
}


