//
// Created by Mihai Moldovan on 14.06.2024.
//

#ifndef PROJECT_SERVICE_H
#define PROJECT_SERVICE_H
#include "repo.h"
#include "valid.h"
#include "observer.h"

class Service: public Subject {
private:
    Repo& repo;
    Valid& valid;

public:
    Service(Repo& repo, Valid& valid);

    void add_tractor(Tractor& t);
    void modifica_nr_roti(int id, int nr_roti_nou);
    Tractor cauta_tractor_dupa_id(int id);
    vector<Tractor> get_all_tractoare();
    map<string,int> get_all_types();
};


#endif //PROJECT_SERVICE_H
