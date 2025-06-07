#include "Iterator.h"
#include "LO.h"
#include <iostream>
#include <exception>
using namespace std;

//WC=BC=AC = Theta(1)
Iterator::Iterator(const LO& lo) : lista(lo){
    curent = lo.prim;
}

//WC=BC=AC = Theta(1)
void Iterator::prim() {
    curent = lista.prim;
}

//WC=BC=AC = Theta(1)
void Iterator::urmator(){
    if(curent == nullptr) {
        throw runtime_error("Nu exista alt element!!!");
    }
    curent = curent->succesor();
}

//WC=BC=AC = Theta(1)
bool Iterator::valid() const{
    if( curent != nullptr) return true;
    return false;
}

//WC=BC=AC = Theta(1)
TElement Iterator::element() const{
    if( valid()) return curent->element();
    throw runtime_error("Element invalid!!!");
}

//WC - atunci cand iteratorul e setat pr primul element si k e aceeasi cu dimensiunea listei - Theta(k)
//BC - atunci cand k este 1, 0 sau negativ sau iteratorul e invalid - Theta(1)
//AC - Theta(k)
//O(k)
void Iterator::avanseazaKPasi(int k) {
    if(!valid()) throw runtime_error("Iterator invalid!!");
    if( k <= 0) throw runtime_error("Nu poți avansa cu un numar nul sau negativ!!!");

    while( k > 0 && curent != nullptr) {
        curent = curent->succesor();
        k--;
    }
}




