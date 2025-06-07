#include "Coada.h"
#include <exception>
#include <iostream>
#include <stdlib.h>

using namespace std;


class MyException : public exception {
private:
    string message;

public:
    // Constructor accepts a const char* that is used to set
    // the exception message
    MyException(const char* msg)
            : message(msg)
    {
    }

    // Override the what() method to return our message
    const char* what() const throw()
    {
        return message.c_str();
    }
};

/**
 * BC = WC = Theta(n)
 */
TElem Coada::stergeMinim() {
    if( this->vida())
        throw MyException("Coada este vida!!!");
    int poz_minim = 0;
    for( int i = 1; i < this->dimensiune; ++i) {
        if(this->vector[(i % this->capacitate)] < this->vector[(poz_minim % this->capacitate)])
            poz_minim = i;
    }
    int element_minim = this->vector[poz_minim];
    for( int i = poz_minim; i <= this->dimensiune; ++i)
        this->vector[(i % this->capacitate)] = this->vector[(i + 1) % this->capacitate];
    this->dimensiune--;
    return element_minim;
}

/**
 * Complexitate: Theta(1)
 */
Coada::Coada() {
    this->capacitate = 5;
    this->dimensiune = 0;
    this->inceput = 0;
    this->vector = (TElem *)malloc(sizeof(TElem) * capacitate);
}

/**
 * Complexitate amortizata: Theta(1)
 */
void Coada::adauga(TElem elem) {
	if( this->dimensiune < this->capacitate) {
        this->vector[(this->inceput + this->dimensiune) % this->capacitate] = elem;
        this->dimensiune++;
        //adaugam elementul la capatul vectorului sau la inceputul lui daca au fost eliberate elemente la inceput
    }
    else {
        //realocam spatiul de memorie dublandu-i capacitatea
        TElem *tmp = this->vector;
        this->vector = (TElem *)malloc(sizeof(TElem) * 2 * this->capacitate);
        //copiem elementele in noul spatiu alocat
        for( int i = 0; i < this->dimensiune; ++i)
            this->vector[i] = tmp[(this->inceput + i) % this->capacitate];
        this->inceput = 0;
        this->capacitate = 2 * this->capacitate;
        this->vector[this->dimensiune] = elem;
        this->dimensiune++;
        free(tmp);
    }
}

/**
 * Complexitate: Theta(1)
 */
TElem Coada::element() const {
	if( this->vida())
        throw MyException("Coada este vida!!!");
    return this->vector[this->inceput];
}

/**
 * Complexitate amortizata: Theta(1)
 */
TElem Coada::sterge() {
    if(this->dimensiune == 0) {
        throw exception();
    }
    int elem = this->vector[this->inceput];
    this->dimensiune--;
    this->inceput++;
    if( this->dimensiune <= this->capacitate / 2 && this->capacitate > 5) {
        TElem *tmp = (TElem *)this->vector;
        this->vector = (TElem *)malloc(sizeof(TElem) * this->dimensiune);
        //daca dimensiunea scade sub jumatate, vom realoca vectorul, injumatatindu-i dimensiunea
        for( int i = 0; i < this->dimensiune; ++i)
            this->vector[i] = tmp[(this->inceput + i) % this->capacitate];
        this->capacitate = this->dimensiune;
        this->inceput = 0;
        free(tmp);
    }
    return elem;
}

/**
 * Complexitate: Theta(1)
 */
bool Coada::vida() const {
	if( this->dimensiune == 0)
	    return true;
    return false;
}

/**
 * Complexitate O(1)
 */
Coada::~Coada() {
    this->capacitate = NULL;
    this->dimensiune = NULL;
    this->inceput = NULL;
}
