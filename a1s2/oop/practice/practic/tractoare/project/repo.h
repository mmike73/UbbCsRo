//
// Created by Mihai Moldovan on 14.06.2024.
//

#ifndef PROJECT_REPO_H
#define PROJECT_REPO_H
#include "domain.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
using std::stringstream;
using std::getline;
using std::map;
using std::vector;

class Repo {
private:
    vector<Tractor> repo;
    map<string,int> occ;
    string filename;

    void read_from_file();
    void write_to_file();

public:
    Repo(string filename);
    void add(Tractor& t);
    void modifica_nr_roti(int id, int nr_roti_nou);
    Tractor search(int id);
    vector<Tractor> get_all();
    map<string, int> get_occurences();
};


#endif //PROJECT_REPO_H
