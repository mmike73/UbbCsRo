//
// Created by Mihai Moldovan on 19.06.2024.
//

#ifndef PROJECT_REPO_H
#define PROJECT_REPO_H
#include "domain.h"

#include <fstream>
#include <sstream>
using std::getline;
using std::stringstream;
using std::ifstream;
using std::ofstream;

class Repo {
public:
    Repo(string file_path);

    void add(Task& t);

    Task seaarch(int id) const;

    void modifica_stare_dupa_id(int id, string stare);

    vector<Task> get_all() const;

private:
    vector<Task> repo;
    string cale_fisier;

    void read_from_file();
    void write_to_file();

};


#endif //PROJECT_REPO_H
