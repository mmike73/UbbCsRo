#pragma once

typedef int TElem;


#define NULL_TELEMENT 0

class Triplet {
public:
    int lin;
    int col;
    TElem val;
    Triplet(int i, int j, TElem e): lin{i}, col{j}, val{e} {}
};

class Nod {
public:
    Triplet val;
    Nod* next;
    Nod(int i, int j, TElem e): val{Triplet(i,j,e)}, next{nullptr} {}
};

class Matrice {
private:
    int nr_linii, nr_coloane;
    Nod** td;
    int dim_td;

public:
	//constructor
	//se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	Matrice(int nrLinii, int nrColoane);


	//destructor
	~Matrice(){
        //dealoca toate nodurile;
        delete [] td;
    };

    int dispersie(int i, int j) const {
        return (i + j) % 2;
    }

	//returnare element de pe o linie si o coloana
	//se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
	//indicii se considera incepand de la 0
	TElem element(int i, int j) const;

	// returnare numar linii
	int nrLinii() const;

	// returnare numar coloane
	int nrColoane() const;


	// modificare element de pe o linie si o coloana si returnarea vechii valori
	// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
	TElem modifica(int i, int j, TElem);

    //returneaza numarul de elemente nenule de pe coloana transmisa
    //arunca exceptie pentru o coloana invalida
    int numberOfNonZeroElements(int col);
};







