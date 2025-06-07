//
// Created by Mihai Moldovan on 18.05.2024.
//

#include "service.h"

void Service::add_placa(string& nume, string& socket, int pret) const {
    PlacaDeBaza p = PlacaDeBaza(nume,socket,pret);
    try {
        validator.valid_nume(p.get_nume());
        validator.valid_socket(p.get_socket());
        validator.valid_pret(p.get_pret());
    } catch(Exception& e) {
        throw Exception(e.what());
    }
    try {
        repo_placi.add_item(p);
    } catch(Exception& e) {
        throw Exception(e.what());
    }
}

vector<PlacaDeBaza> Service::filtreaza_placi(std::function <bool(const PlacaDeBaza& p)> filltru) {
    std::vector<PlacaDeBaza> all_boards = repo_placi.get_all();
    std::vector<PlacaDeBaza> rez;
    for(const auto& i: all_boards)
        if(filltru(i)) rez.push_back(i);
    return rez;
}

Procesor Service::cauta_procesor(string& nume) {
    return repo_procesoare.search_item(nume);
}

PlacaDeBaza Service::cauta_placa(std::string &nume) {
    return repo_placi.search_item(nume);
}

vector<Procesor> Service::get_procesoare() const {
    return repo_procesoare.get_all();
}

vector<PlacaDeBaza> Service::get_placi() const {
    return repo_placi.get_all();
}