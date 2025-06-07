#include "Iterator.h"
#include "LO.h"

#include <iostream>
#include <exception>
using namespace std;


//Theta(1)
LO::LO(Relatie r) {
    relatie = r;
    prim = nullptr;
}

//Theta(n)
// returnare dimensiune
int LO::dim() const {
    if(vida()) return 0;
    int dimensiune = 1;
    PNod nod = prim;
    while(nod->succesor() != nullptr) {
        dimensiune++;
        nod = nod->succesor();
    }
    return dimensiune;
}

//Theta(1)
// verifica daca LO e vida
bool LO::vida() const {
    if(prim == nullptr) return true;
    return false;
}

//Theta(i), i - pozitia elementului in lista
// returnare element
//arunca exceptie daca i nu e valid
TElement LO::element(int i) const{
    if(vida()) {
        throw runtime_error("Lista este vida!!!");
    }
    PNod nod = prim;
    while(i > 0) {
        if(nod->succesor() == nullptr) {
            throw runtime_error("Nu exista element la indicele dat!!!");
        }
        nod = nod->succesor();
        i--;
    }
    return nod->element();
}

//Theta(i), i - pozitia elementului in lista
// sterge element de pe o pozitie i si returneaza elementul sters
//arunca exceptie daca i nu e valid
TElement LO::sterge(int i) {
    if(vida()) {
        throw runtime_error("Lista este vida!!!");
    }
    if( i == -1) {
        throw runtime_error("Nu exista element la indicele dat!!!");
    }

    PNod nod = prim;
    for( int ind = 0; ind < i; ++ind) {

        nod = nod->succesor();
        if( nod == nullptr)
            throw runtime_error("Nu exista element la indicele dat!!!");
    }

    TElement deleted = nod->element();

    if( nod->succesor() != nullptr && nod->predecesor() != nullptr) {
        nod->pred->succ = nod->succesor();
        nod->succ->pred = nod->predecesor();
        delete nod;
    }
    else if(nod->succesor() == nullptr && nod->predecesor() != nullptr) {
        nod->pred->succ = nullptr;
        delete nod;
    }
    else if(nod->succesor() != nullptr && nod->predecesor() == nullptr) {
        prim = nod->succesor();
        prim->pred = nullptr;
        delete nod;
    }
    else if(nod->succesor() == nullptr && nod->predecesor() == nullptr) {
        delete prim;
        prim = nullptr;
    }
    return deleted;
}

//O(n)
// cauta element si returneaza prima pozitie pe care apare (sau -1)
int LO::cauta(TElement e) const {
    if(vida()) return -1;
    int i = 0;
    PNod nod = prim;
    while(nod != nullptr) {
        if(!relatie(nod->element(), e)) return -1;
        if(nod->element() == e) return i;
        nod = nod->succesor();
        i++;
    }
    return -1;
}

//WC - atunci cand elementul de adaugat e cel mai mare din lista - Theta(n)
//BC - atunci cand elementul de adaugat e cel mai mic din lista - Theta(1)
//AC - Theta(k), k e pozitia la care se va insera, respectiv cate elemente sunt mai mici decat e
//O(n)
// adaugare element in LO
void LO::adauga(TElement e) {
    if(vida()) {
        prim = new Nod(e, nullptr, nullptr);
        return;
    }
    PNod nod = prim;
    while(relatie(nod->element(), e) && nod->succesor() != nullptr)
        nod = nod->succesor();
    PNod nod_nou = new Nod(e, nullptr, nullptr);

    if( nod->succesor() != nullptr && nod->predecesor() != nullptr) {
        nod_nou->pred = nod->pred;
        nod_nou->succ = nod;
        nod_nou->pred->succ = nod_nou;
        nod->pred = nod_nou;
    }
    else if(nod->succesor() == nullptr && nod->predecesor() != nullptr && relatie(nod->element(), e)) {
        nod_nou->pred = nod;
        nod->succ = nod_nou;
    }
    else if(nod->succesor() == nullptr && nod->predecesor() != nullptr && !relatie(nod->element(), e)) {
        nod_nou->pred = nod->pred;
        nod_nou->succ = nod;
        nod_nou->pred->succ = nod_nou;
        nod->pred = nod_nou;
    }
    else if(nod->succesor() != nullptr && nod->predecesor() == nullptr) {
        nod_nou->succ = prim;
        prim->pred = nod_nou;
        prim = nod_nou;
    }
    else if(nod->succesor() == nullptr && nod->predecesor() == nullptr && relatie(nod->element(), e)) {
        nod_nou->pred = prim;
        prim->succ = nod_nou;
    }
    else if(nod->succesor() == nullptr && nod->predecesor() == nullptr && !relatie(nod->element(), e)) {
        nod_nou->succ = prim;
        prim->pred = nod_nou;
        prim = nod_nou;
    }
}

//Theta(1)
// returnare iterator
Iterator LO::iterator() {
    return Iterator(*this);
}

//Theta(n)
//destructor
LO::~LO() {
    while( prim != nullptr) {
        PNod p = prim;
        prim = prim->succ;
        delete p;
    }
}
