#pragma once
using namespace std;

typedef int TElem;

class Coada
{
	private:
        int capacitate, dimensiune, inceput;
        TElem *vector;
	public:
        //elimina si returneaza elementul minim din coada - elemente numere intregi
        //arunca exceptie in cazul in care coada e goala
        TElem stergeMinim();

		//constructorul implicit
		Coada();

		//adauga un element in coada
		void adauga(TElem e);

		//acceseaza elementul cel mai devreme introdus in coada 
		//arunca exceptie daca coada e vida
		TElem element() const;

		//sterge elementul cel mai devreme introdus in coada si returneaza elementul sters (principiul FIFO)
		//arunca exceptie daca coada e vida
		TElem sterge();

		//verifica daca coada e vida;
		bool vida() const;


		// destructorul cozii
		~Coada();
};
