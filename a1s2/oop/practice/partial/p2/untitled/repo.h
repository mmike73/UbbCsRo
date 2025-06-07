//
// Created by Mihai Moldovan on 20.05.2024.
//

#ifndef UNTITLED_REPO_H
#define UNTITLED_REPO_H
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "domain.h"

using std::stringstream;
using std::getline;
using std::endl;
using std::string;
using std::vector;

class Repo {
public:
    Repo(string nume_fisier): cale_fisier{nume_fisier} {
        read_from_file();
    }

    void read_from_file();
    void write_to_file();

    void add_item(Apartament& a);
    Apartament search_item(int id);
    void delete_item(int id);
    vector<Apartament> get_all();

private:
    string cale_fisier;
    vector<Apartament> repo;
};


#endif //UNTITLED_REPO_H
