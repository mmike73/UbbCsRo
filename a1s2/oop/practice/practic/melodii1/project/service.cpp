//
// Created by Mihai Moldovan on 18.06.2024.
//

#include "service.h"
#include "exception.h"


Service::Service(Repo& repo):repo{repo} {}


void Service::sterge_melodie(int id) {
    try {
        repo.sterge_melodie(id);
    } catch (Exception &e) {
        throw Exception(e.what());
    }
}

Melodie Service::cauta_melodie(int id) const {
    return repo.cauta_melodie(id);
}


void Service::modifica_melodie(int id, Melodie& m ) {
    repo.modifica_melodie(id,m);
//    try {
//        if(m.get_rank() > 10 || m.get_rank() < 0) {
//            throw Exception("Rank trebuie sa fie intre 0 si 10!\n");
//        }
//        m.set_rank(m.get_rank());
//        m.set_titlu(m.get_titlu());
//        repo.modifica_melodie(id, m);
//
//    } catch (Exception& e) {
//        std::cout << e.what();
//    }
}

vector<Melodie> Service::get_all_melodii() const {
    return repo.get_all_melodii();
}

map<int,int> Service::get_all_ranks() const {
    return repo.get_all_ranks();
}

map<string,int> Service::get_all_artists() const {
    return repo.get_all_artists();
}