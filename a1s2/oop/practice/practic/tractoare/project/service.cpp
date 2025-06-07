//
// Created by Mihai Moldovan on 14.06.2024.
//

#include "service.h"


Service::Service(Repo &repo, Valid &valid): repo{repo}, valid{valid} {};

void Service::add_tractor(Tractor& t) {
    valid.valideaza_tractor(t);
    repo.add(t);
    notify();
}

Tractor Service::cauta_tractor_dupa_id(int id) {
    return repo.search(id);
}

void Service::modifica_nr_roti(int id, int nr_roti_nou) {
    repo.modifica_nr_roti(id, nr_roti_nou);
}

vector<Tractor> Service::get_all_tractoare() {
    return repo.get_all();
}

map<string,int> Service::get_all_types() {
    return repo.get_occurences();
}