#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;

//Theta(cap_noua)
void Colectie::redimensionare(int cap_noua) {
    if(cap_noua < size) {
        throw exception();
    }
    Pair* te = new Pair [cap_noua];
    int* tst = new int [cap_noua];
    int* tdr = new int [cap_noua];


    for(int i = 0; i < size; ++i) {
        te[i] = e[i];
        tst[i] = st[i];
        tdr[i] = dr[i];
    }
    for(int i = size; i < cap_noua;++i) {
        te[i].freq = 0;
        tst[i] = -1;
        tdr[i] = -1;
    }

    if(e != nullptr) {
        delete [] e;
        delete [] st;
        delete [] dr;
    }
    e = te;
    st = tst;
    dr = tdr;
    cap = cap_noua;
}

// BC: Theta(1) - urmatorul spatiu e liber
// WC: Theta(n)- singurul elemeent liber e cel care e pe pozitia anterioara
// AC: Theta(i), i e pe o pozitie aleatoare in vector
// O(n)
void Colectie::inc_prim_liber() {
    while(e[prim_liber].freq != 0 && size < cap) {
        prim_liber++;
        if(prim_liber == cap) prim_liber %= cap;
    }
}

//BC: Theta(log n) - inaltimea arborelui echilibrat
//WC: Theta(n) - toate elementele se afla pe ramura stanga
//O(n)
int Colectie::minim(int p) const {
    while(st[p] != -1) {
        p = st[p];
    }
    return p;
}

//BC: Theta(log n) - inaltimea arborelui echilibrat
//WC: Theta(n) - toate elementele se afla pe ramura dreapta
//O(n)
int Colectie::maxim(int p) const {
    while(dr[p] != -1) {
        p = dr[p];
    }
    return p;
}

//O(n)
int Colectie::diferentaMaxMin() const {
    if(cnt == 0) {
        return -1;
    }
    int pmin = minim(root);
    int pmax = maxim(root);
    return e[pmax].e - e[pmin].e;
}

/*
 * Functie diferentaMaxima
 * Daca cnt == 0 atunci
 *  diferentaMaxima <- -1
 * SfDaca
 * pmin <- root
 * CatTimp st[pmin] != -1 executa
 *  pmin = st[pmin]
 * SfCatTimp
 * pmax <- root
 * CatTimp dr[pmin] != -1 executa
 *  pmax = dr[pmin]
 * SfCatTimp
 * diferentaMaxima <- e[pmax].e - e[pmin].e
 */

//Theta(1)
Colectie::Colectie() {
    prim_liber = 0;
    height = -1;
    root = -1;
    cnt = 0;
	size = 0;
    cap = 5;
    e = nullptr;
    st = nullptr;
    dr = nullptr;
    redimensionare(5);
}

//BC: Theta(log n) - inaltimea arborelui echilibrat
//WC: Theta(n) - toate elementele se afla pe una dintre ramuri
//O(n)
void Colectie::adauga(TElem elem) {
    root = adauga_rec(root, elem);
}

int Colectie::adauga_rec(int p, TElem elem) {
    if(p == -1) {
        e[prim_liber].e = elem;
        e[prim_liber].freq = 1;
        size++;
        cnt++;
        if(size == cap) redimensionare(2 * cap);
        p = prim_liber;
        inc_prim_liber();
    } else {
        if(elem < e[p].e) {
            st[p] = adauga_rec(st[p], elem);
        } else if(elem > e[p].e) {
            dr[p] = adauga_rec(dr[p], elem);
        } else if(elem == e[p].e){
            e[p].freq ++;
            cnt++;
        }
    }
    return p;
}

//BC: Theta(log n) - inaltimea arborelui echilibrat
//WC: Theta(n) - toate elementele se afla pe una dintre ramuri
//O(n)
bool Colectie::sterge(TElem elem) {
    int de_sters = cauta_rec(root,elem);
    if(de_sters != -1) {
        if(e[de_sters].freq > 1) {
            e[de_sters].freq--;
        } else {
            root = stergere_recursiva(root, elem);
            size -= 1;
        }
        cnt--;
        return true;
    }
    if(root == -1) cnt = 0;
    return false;
}

int Colectie::stergere_recursiva(int p, TElem elem) {
    if(p == -1) {
        return -1;
    } else {
        if(e[p].e > elem) {
            st[p] = stergere_recursiva(st[p],elem);
            return p;
        } else {
            if(e[p].e < elem) {
                dr[p] = stergere_recursiva(dr[p],elem);
                return p;
            } else {
                if (st[p] != -1 && dr[p] != -1) {
                    int tmp = minim(dr[p]);
                    e[p].e = e[tmp].e;
                    dr[p] = stergere_recursiva(dr[p], e[p].e);
                    return p;
                } else {
                    int tmp = p;
                    int repl;
                    if (st[p] == -1) {
                        repl = dr[p];
                    } else {
                        repl = st[p];
                    }
                    st[tmp] = -1;
                    dr[tmp] = -1;
                    e[tmp].e = 0;
                    e[tmp].freq = 0;
                    return repl;
                }
            }
        }
    }
}

//BC: Theta(log n) - inaltimea arborelui echilibrat
//WC: Theta(n) - toate elementele se afla pe una dintre ramuri
//O(n)
bool Colectie::Colectie::cauta(TElem elem) const {
    return cauta_rec(root,elem) != -1;
}

int Colectie::cauta_rec(int p, TElem elem) const {
    if(p == -1) {
        return -1;
    } else if(elem < e[p].e) {
        return cauta_rec(st[p], elem);
    } else if(elem > e[p].e) {
        return cauta_rec(dr[p], elem);
    }
    return p;
}

//BC: Theta(log n) - inaltimea arborelui echilibrat
//WC: Theta(n) - toate elementele se afla pe una dintre ramuri
//O(n)
int Colectie::nrAparitii(TElem elem) const {
    int poz = cauta_rec(root,elem);
    if(cauta_rec(root,elem) == -1) return 0;
    return e[poz].freq;
}

//Theta(1)
int Colectie::dim() const {
	return cnt;
}

//Theta(1)
bool Colectie::vida() const {
	return size == 0;
}

IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
	delete [] e;
	delete [] st;
	delete [] dr;
}
