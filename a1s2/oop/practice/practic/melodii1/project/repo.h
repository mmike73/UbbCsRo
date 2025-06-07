//
// Created by Mihai Moldovan on 18.06.2024.
//

#ifndef PROJECT_REPO_H
#define PROJECT_REPO_H
#include "domain.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
using std::vector;
using std::map;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::getline;

class Repo {
private:
    string cale_fisier;
    vector<Melodie> repo;
    map<int,int> ranks;
    map<string,int> nr_piese;

    void read_from_file();
    void write_to_file();

public:
    //constriuctor
    //cale_fisier: string - calea fisierului in care sunt stocate melodii
    Repo(string cale_fisier);

    //adauga o melodie in repo
    //arunca exceptie daca melodia deja exista
    void adauga_melodie(Melodie& melodie);

    //cauta o melodie dupa id
    //intoarce o melodie invalida daca nu gaseste una
    Melodie cauta_melodie(int id) const;

    //inlocuieste melodia cu idul dat cu melodia data ca parametru
    void modifica_melodie(int id, Melodie& m);

    //sterge melodia cu id-ul dat
    void sterge_melodie(int id);

    //returneaza un vector cu toate melodiile
    vector<Melodie> get_all_melodii() const;

    //retuneaza un dictionar cu numarul fiecarui rank
    map<int,int> get_all_ranks() const;

    //returneaza un dicitonar cu artistii si numarul de piese al fiecaruia;
    map<string,int> get_all_artists() const;

};


#endif //PROJECT_REPO_H
