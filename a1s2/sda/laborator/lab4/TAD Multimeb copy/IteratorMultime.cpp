#include "IteratorMultime.h"
#include "Multime.h"

/*
 * Theta(1)
 */
IteratorMultime::IteratorMultime(Multime& m) : multime(m){
	curent = multime.start;
}

/*
 * Theta(1)
 */
void IteratorMultime::prim() {
	curent = multime.start;
}

/*
 * Theta(1)
 */
void IteratorMultime::urmator() {
	curent = multime.ld[curent];
}

/*
 * Theta(1)
 */
TElem IteratorMultime::element() const {
    if(valid()) return multime.e[curent];
	return -1;
}

/*
 * Theta(1)
 */
bool IteratorMultime::valid() const {
    if( multime.dimensiune == 0) return false;
    if( curent == -1) return false;
    if(multime.ls[curent] == -1 && multime.ld[curent] == -1 && multime.dimensiune == 1 && curent == multime.start)
        return true;
    if(multime.ls[curent] == -1 && multime.ld[curent] == -1)
        return false;
	return true;
}


TElem IteratorMultime::elimina() {
    TElem deleted;



    return deleted;
}