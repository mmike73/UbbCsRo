#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
    stack<int> stiva;
    int nod_crt = col.root;

    while(nod_crt != -1 || !stiva.empty()) {
        while(nod_crt != -1) {
            stiva.push(nod_crt);
            nod_crt = col.st[nod_crt];
        }
        nod_crt = stiva.top();
        stiva.pop();
        for(int i = 0; i < col.e[nod_crt].freq;++i)
            elems.push_back(col.e[nod_crt].e);
        nod_crt = col.dr[nod_crt];
    }
    crt = 0;
}

void IteratorColectie::prim() {
	crt = 0;
}

void IteratorColectie::urmator() {
    if(!valid()) throw exception();
	crt++;
}

bool IteratorColectie::valid() const {
    return crt < col.cnt;
}

TElem IteratorColectie::element() const {
    if(!valid()) throw exception();
	return elems[crt];
}
