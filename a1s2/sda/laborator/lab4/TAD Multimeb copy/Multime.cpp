#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

/*
 * Theta(n + m),  n este numarul de elemente din  multime
 *                m este capacitatea mulțimii
 */
void Multime::redimensionare(int cap_noua) {
    TElem* tmp;
    int* ts;
    int* td;
    tmp = new TElem [cap_noua];
    ts = new int [cap_noua];
    td = new int [cap_noua];

    for( int i = 0; i < cap_noua; ++i) {
        ts[i] = -1;
        td[i] = -1;
    }

    IteratorMultime i = iterator();
    int poz = 0;
    while(i.valid()) {
        tmp[poz] = e[i.curent];
        if( ls[i.curent] != -1)
            ts[poz] = poz - 1;
        if( ld[i.curent] != -1)
            td[poz++] = poz + 1;
        i.urmator();
    }

    if( e != nullptr) {
        delete [] e;
        delete [] ls;
        delete [] ld;
    }

    e = tmp;
    ls = ts;
    ld = td;
    prim_liber = dimensiune;
    start = 0;
    capacitate = cap_noua;

}

/*
 * Theta(1)
 */
Multime::Multime() {
    e = nullptr;
    capacitate = 5;
    dimensiune = 0;
    redimensionare(5);
    prim_liber = 0;
    start = 0;
}

/*
 * BC: Theta(1), cand elementul este primul in multime
 * WC: Theta(n), cand elementul nu exista
 * AC: Theta(i), cand i este pozitie elementului din multime
 * overall: O(n), n e numarul de elemente din multime
 */
bool Multime::adauga(TElem elem) {

    if(cauta(elem) == false) {
        if( dimensiune == capacitate) {
            redimensionare(capacitate * 2);
        }
        if(dimensiune == 0) {
            e[dimensiune] = elem;
            dimensiune++;
            prim_liber++;
            start = 0;
            return true;
        }
        else {
            IteratorMultime i = iterator();
            while (ld[i.curent] != -1) {
                i.urmator();
            }
            ld[i.curent] = prim_liber;
            ls[prim_liber] = i.curent;
            e[prim_liber] = elem;
            dimensiune++;
            prim_liber = start;
            while((ls[prim_liber] != -1 || ld[prim_liber] != -1) && prim_liber < capacitate)
                prim_liber ++;

            return true;
        }
    }
	return false;
}

/*
 * BC: Theta(1), cand elementul este primul in multime
 * WC: Theta(n), cand elementul nu exista
 * AC: Theta(i), cand i este pozitie elementului din multime
 * overall: O(n), n e numarul de elemente din multime
 */
bool Multime::sterge(TElem elem) {
    if(dimensiune == 0) return false;
    IteratorMultime i = iterator();
    while(i.element() != elem && i.valid()) {
        i.urmator();
    }
    if(i.element() == elem && i.valid()) {
        int pred = ls[i.curent], succ = ld[i.curent];
        if( i.curent == start) start = succ;
        if(pred != -1) ld[pred] = succ;
        if( succ != -1) ls[succ] = pred;
        ls[i.curent] = -1;
        ld[i.curent] = -1;

        if( i.curent < prim_liber && i.valid()) prim_liber = i.curent;
        dimensiune--;



        if( dimensiune == capacitate / 4 && capacitate > 5) {
            redimensionare(capacitate / 2);
        }

        return true;
    }
	return false;
}

/*
 * BC: Theta(1), cand elementul este primul in multime
 * WC: Theta(n), cand elementul nu exista
 * AC: Theta(i), cand i este pozitie elementului din multime
 * overall: O(n), n e numarul de elemente din multime
 */
bool Multime::cauta(TElem elem) const {
    IteratorMultime i = iterator();
    while( i.element() != elem && i.valid()) i.urmator();
    if( !i.valid()) return false;
	return true;
}

/*
 * Theta(1)
 */
int Multime::dim() const {
	return dimensiune;
}

/*
 * Theta(1)
 */
bool Multime::vida() const {
    if(dimensiune > 0) return false;
	return true;
}

/*
 * Theta(1)
 */
Multime::~Multime() {
    capacitate = 0;
    dimensiune = 0;
    delete [] e;
    delete [] ls;
    delete [] ld;
}

IteratorMultime Multime::iterator() {
	return IteratorMultime(*this);
}
