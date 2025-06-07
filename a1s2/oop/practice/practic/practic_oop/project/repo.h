//
// Created by Mihai Moldovan on 22.06.2024.
//

#ifndef PROJECT_REPO_H
#define PROJECT_REPO_H
#include "domain.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
using std::vector;
using std::map;
using std::getline;
using std::stringstream;


class Repo {
private:
    string cale_fisier;
    vector<Utilaj> repo;
    map<string,int> occ;
    map<int,int> cilindri;

    void read_from_file();
    void write_to_file();
public:
    Repo(string cale_fisier);

    void add(const Utilaj& u);
    Utilaj search(int id);
    void modifica(int id, Utilaj& u);
    void del(int id);
    vector<Utilaj> getAll() const;
    map<string,int> getTipuri() const;
    map<int,int> getCilindri() const;


    };


#endif //PROJECT_REPO_H
