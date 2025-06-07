//
// Created by Mihai Moldovan on 21.05.2024.
//

#include "service.h"
#include "exception.h"

Elev Service::cauta_dupa_nr(int nr_matricol) {
    Elev e = repo.cauta_elev(nr_matricol);
    if(e.get_nr_matricol() == -1) {
        throw Exception("Elevul nu exista");
    }
    return e;
}

vector<Elev> Service::get_all() {
    return repo.get_all();
}

vector<Elev> Service::filtreaza_dupa_activitate(string activitate) {
    vector<Elev> all = repo.get_all();
    vector<Elev> rez;
    for(const auto& i:all) {
        vector<string> a = i.get_lista_ateliere();
        for(auto& j:a) {
            if(j == activitate) rez.push_back(i);
        }
    }
    return rez;
}
