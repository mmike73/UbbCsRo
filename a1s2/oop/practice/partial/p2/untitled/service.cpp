//
// Created by Mihai Moldovan on 20.05.2024.
//

#include "service.h"

vector<Apartament> Service::filtreaza(std::function<bool(Apartament& a)> filtru) {
    vector<Apartament> all = repo.get_all();
    vector<Apartament> rez;
    for(auto& i:all) {
        if(filtru(i))
            rez.push_back(i);
    }
    return rez;
}

void Service::sterge_apartament(int id) {
    repo.delete_item(id);
}

vector<Apartament> Service::get_all() const {
    return repo.get_all();
}
