#pragma once

#define NULL_TELEM -1
#include <iostream>
typedef int TElem;

class Pair {
public:
    Pair() {
        e = 0;
        freq = 0;
    }
    TElem e;
    int freq;
};

class IteratorColectie;

class Colectie
{
	friend class IteratorColectie;

private:
    Pair* e = nullptr;
    int* st;
    int* dr;

    int cap, size, prim_liber = 0;
    int cnt = 0;

    int root, height;

    void redimensionare(int cap_noua);
    void inc_prim_liber();
    int adauga_rec(int p, TElem elem);
    int cauta_rec(int p, TElem elem) const;
    int stergere_recursiva(int p, TElem elem);
    int minim(int p) const;
    int maxim(int p) const;

public:
		//constructorul implicit
		Colectie();

		//adauga un element in colectie
		void adauga(TElem e);

		//sterge o aparitie a unui element din colectie
		//returneaza adevarat daca s-a putut sterge
		bool sterge(TElem e);

		//verifica daca un element se afla in colectie
		bool cauta(TElem elem) const;

		//returneaza numar de aparitii ale unui element in colectie
		int nrAparitii(TElem elem) const;

		//intoarce numarul de elemente din colectie;
		int dim() const;

		//verifica daca colectia e vida;
		bool vida() const;

		//returneaza un iterator pe colectie
		IteratorColectie iterator() const;

        int diferentaMaxMin() const;

		// destructorul colectiei
		~Colectie();
};

