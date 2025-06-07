//
// Created by Mihai Moldovan on 21.06.2024.
//

#ifndef PROJECT_REPO_H
#define PROJECT_REPO_H
#include "domain.h"
#include <vector>
#include <fstream>
#include <sstream>
using std::vector;
using std::vector;
using std::stringstream;

class Repo {
private:
    vector<Joc> repo;
    string cale_fisier;

    void read_from_file();
    void write_to_file();

public:

    Repo(string cale_fisier);

    void add(const Joc& j);

    void mod(int id, Joc& j);

    Joc search(int id) const;

    void remove(int id);

    vector<Joc> get_all() const;
};


#endif //PROJECT_REPO_H
