#include "Matrice.h"

#include <exception>
#include <iostream>

using namespace std;

/*
 * Theta(1)
 */
Matrice::Matrice(int m, int n) {
	nr_linii = m;
    nr_coloane = n;
    dim_td = 3;
    td = new Nod*[dim_td];
}

/*
 * Theta(1)
 */
int Matrice::nrLinii() const{
    return nr_linii;
}

/*
 * Theta(1)
 */
int Matrice::nrColoane() const{
	return nr_coloane;
}

/*
 * BC: Theta(1), cand nu exista coliziuni
 * WC: Theta(n), cand matricea are linia completa si elementul e ultimul
 * AC: Theta(i), cand elementul se afla pe o pozitie intermediara in matrice
 * overall Theta(1) in ipoteza dispersiei uniforme, fiind matrice rara
 */
TElem Matrice::element(int i, int j) const{
    if(i < nr_linii && j < nr_coloane && i >= 0 && j >= 0) {
        Nod *n = td[dispersie(i,j)];
        while (n != nullptr && (n->val.lin != i || n->val.col != j)) {
            n = n->next;
        }
        if (n != nullptr && n->val.lin == i && n->val.col == j) return n->val.val;
        else return NULL_TELEMENT;
    }
    //throw exception
    throw std::exception();
}

/*
 * BC: Theta(1), cand nu exista coliziuni
 * WC: Theta(n), cand matricea are linia completa si elementul e ultimul
 * AC: Theta(i), cand elementul se afla pe o pozitie intermediara in matrice
 * overall Theta(1) in ipoteza dispersiei uniforme, fiind o matrice rara
 */
TElem Matrice::modifica(int i, int j, TElem e) {
	if(i < nr_linii && j < nr_coloane && i >= 0 && j >= 0) {
        if(element(i,j) != 0) {
            Nod* n = td[dispersie(i,j)];
            Nod* m = n;
            while (n->val.col != j || n->val.lin != i) {
                n = n->next;
                m = n;
            }
            if(e == 0) {
                m->next == nullptr;
                delete n;
            }
            else {
                n->val.val = e;
            }
        } else {
            if(td[dispersie(i,j)] == nullptr) {
                td[dispersie(i,j)] = new Nod{i,j,e};
            } else {
                Nod* n = td[dispersie(i,j)];
                while (n->next != nullptr) {
                    n = n->next;
                }
                n->next = new Nod{i, j, e};
            }
        }
    }
	return -1;
}

//BC - Theeta(nr_linii) - element, prima linie
//WC - Theta(n) = ultimul element
//O(n) n - numarul de elemente
int Matrice::numberOfNonZeroElements(int col) {
    if(col > nr_coloane) {
        throw std::exception();
    }
    int cnt = 0;
    for(int line = 0; line < nr_linii; ++line) {
        if(td[dispersie(line,col)] == nullptr) continue;
        Nod* elem = td[dispersie(line,col)];
        while(elem) {
            if (elem->val.col == col && elem->val.lin == line) {
                cnt++;
                break;
            }
            elem = elem->next;
        }
    }
    return cnt;
}

/*
Functie numberOfNonZeroElements(Intreg: col)
|   daca col > matrice.nuamr_coloane atunci
|   |   @arunca_exceptie
|   sfDaca
|
|   cnt <- 0
|   pentru i <- 0, matrice.numar_linii
|   |   daca td[d(i,j)] != NIL atunci
|   |   |   Nod elem <- td[d(i,j)]
|   |   |   catTimp elem != NIL atunci
|   |   |   |   daca [elem].val.col == col si [elem].val.lin == lin atunci
|   |   |   |   |   cnt <- cnt + 1
|   |   |   |   |   @break
|   |   |   |   sfDaca
|   |   |   |   elem <- [elem].urmator
|   |   |   sfCatTimp
|   |   sfDaca
|   sfPentru
sfFunctie
 */
