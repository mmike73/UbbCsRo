//
// Created by Mihai Moldovan on 22.06.2024.
//

#ifndef PROJECT_SERVICE_H
#define PROJECT_SERVICE_H
#include "repo.h"
#include "observer.h"
#include "valid.h"
#include "exception.h"

class Service: public Subject {
public:

    Service(Repo& r);

    Utilaj cauta_utilaj(int id);
    Utilaj mdoifica_denumire_utilaj(int id, string denumire);
    Utilaj modifica_tip_utilaj(int id, string tip);
    Utilaj modifica_numar_cilindri_utilaj(int id, int nr_cil);
    void sterge_utilaj(int id);
    vector<Utilaj> get_all();
    map<string, int> get_tipuri();
    map<int, int> get_cilindri();

private:
    Repo& r;

};


#endif //PROJECT_SERVICE_H
