#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>

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

/*
 * Theta(1) - complexitatea amortizata la redimensionare
 */
TElem IteratorMultime::elimina() {
    if(multime.dimensiune == 0 || !valid()) {
        throw std::exception();
    }
    TElem deleted = multime.e[curent];
    int pred = multime.ls[curent];
    int succ = multime.ld[curent];
    if(pred != -1 && succ != -1) {
        multime.ls[succ] = pred;
        multime.ld[pred] = succ;
    } else if(pred != -1 && succ == -1) {
        multime.ld[pred] = -1;
    } else if(pred == -1 && succ != -1) {
        multime.ls[succ] = -1;
    }
    multime.dimensiune --;
    if(multime.prim_liber > curent) {
        multime.prim_liber = curent;
    }
    if( multime.dimensiune == multime.capacitate / 4 && multime.capacitate > 5) {
        multime.redimensionare(multime.capacitate / 2);
    }
    multime.ls[curent] = -1;
    multime.ld[curent] = -1;
    curent = succ;
    return deleted;
}
/*
 * Pseudocod:
 * Functie elimina()
 *  daca multime.dimensiune = 0 sau iteator.valid() = false atunci
    |    @arunca_exceptie
    sfDaca

    TElem eliminat <- multime.e[iteator.curent]
    int pred <- multime.ls[iteator.curent];
    int succ <- multime.ld[iteator.curent];

    daca pred != -1 si succ != -1 atunci
    |    multime.ls[succ] <- pred
    |    multime.ld[pred] <- succ
    |altfel
    |    daca pred != -1 si succ == -1 atunci
    |    |   multime.ld[pred] = -1;
    |    |altfel
    |    |    daca pred == -1 && succ != -1 atunci
    |    |    |  multime.ls[succ] = -1;
    |    |    sfDaca
    |    sfDaca
    sfDaca

    multime.dimensiune --;

    daca multime.prim_liber > iteator.curent atunci
    |    multime.prim_liber <- iteator.curent;
    sfDaca

    daca multime.dimensiune = multime.capacitate / 4 si multime.capacitate > 5 atunci
    |    @redimensionare(multime.capacitate / 2);
    sfDaca

    multime.ls[iteator.curent] <- -1;
    multime.ld[iteator.curent] <- -1;
    iteator.curent <- succ;
    returneaza deleted;
 */