//
// Created by Mihai Moldovan on 21.06.2024.
//

#include "repo.h"
#include "exception.h"

void Repo::add(const Joc& j) {
    try {
        search(j.get_id());
    } catch(Exception& e) {
        repo.push_back(j);
    }
}

void Repo::mod(int id, Joc& j) {
    try {
        search(j.get_id());
        for(auto& i:repo) {
            if(i.get_id() == id)
                i = j;
        }
    } catch(Exception& e) {
        throw Exception(e.what());
    }
}

Joc Repo::search(int id) const {
    for(auto& i: repo) {
        if(i.get_id() == id) return i;
    }
    throw Exception("Nu exista!");
}

void Repo::remove(int id) {
    repo.erase(remove_if(repo.begin(),repo.end(),[&](Joc& crt) {
        return crt.get_id() == id;
    }));
}

vector<Joc> Repo::get_all() const {
    return repo;
}

void Repo::read_from_file() {
    std::ifstream fin(cale_fisier);

    string line;
    string id_s, dim_s, tabla, jucator_s, stare;
    while(getline(fin,line)) {
        stringstream lin(line,' ');
        getline(lin,id_s);
        getline(lin,dim_s);
        getline(lin,tabla);
        getline(lin,jucator_s);
        getline(lin,stare);
    }
    int id = std::stoi(id_s);
    int dim = std::stoi(dim_s);
    char jucator = jucator_s[0];

    Joc j(id,dim,tabla,jucator_s,stare);
}

void Repo::write_to_file() {

}

Repo::Repo(string cale_fisier): cale_fisier{cale_fisier} {}
