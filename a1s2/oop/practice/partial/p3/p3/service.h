//
// Created by Mihai Moldovan on 21.05.2024.
//

#ifndef P3_SERVICE_H
#define P3_SERVICE_H
#include "file_repo.h"
#include <string>
using std::string;

class Service {
public:
    Service(FileRepo& repo): repo{repo} {}
    Elev cauta_dupa_nr(int nr_matricol);
    vector<Elev> filtreaza_dupa_activitate(string activitate);
    vector<Elev> get_all();

private:
    FileRepo& repo;
};


#endif //P3_SERVICE_H
