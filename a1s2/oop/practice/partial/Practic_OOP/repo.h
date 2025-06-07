//
// Created by Mihai Moldovan on 22.05.2024.
//

#ifndef PRACTIC_OOP_REPO_H
#define PRACTIC_OOP_REPO_H
#include "domain.h"
#include <fstream>
#include <sstream>
using std::stringstream;
using std::getline;

#include <iostream>
class Repo {
public:
    Repo(string cale_fisier): cale_fisier{cale_fisier} {
        read_from_file();
    }
    void add_item(Log& l);
    Log search_item(string id);
    vector<Log> get_all();

private:
    string cale_fisier;
    vector<Log> repo;

    void read_from_file();

};


#endif //PRACTIC_OOP_REPO_H
