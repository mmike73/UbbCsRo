//
// Created by Mihai Moldovan on 22.06.2024.
//

#include "repo.h"
#include <iostream>
#include "exception.h"

Repo::Repo(string cale_fisier): cale_fisier{cale_fisier} {
    read_from_file();
}

void Repo::read_from_file() {

    std::ifstream fin(cale_fisier);

    string line;
    string id_s, cil_s, denumire, tip;

    while(getline(fin,line)) {
        stringstream lin(line);

        getline(lin,id_s,',');
        getline(lin,denumire,',');
        getline(lin,tip,',');
        getline(lin,cil_s,',');

        int id = stoi(id_s);
        int cil = stoi(cil_s);

        Utilaj u{id,denumire,tip,cil};
        add(u);
    }

    fin.close();
}
void Repo::write_to_file() {
    std::ofstream fout(cale_fisier);
    fout.clear();
    for(auto& i:repo) {
        fout << i.to_string();
        std::cout << i.to_string();
    }
    fout.close();
}

void Repo::add(const Utilaj& u) {
    try {
        search(u.get_id());
    } catch (Exception& e) {
        repo.push_back(u);
        occ[u.get_tip()] ++;
        cilindri[u.get_cilindri()] ++;
        write_to_file();
    }
}

void Repo::modifica(int id, Utilaj& u) {
    try {
        Utilaj de_mod = search(u.get_id());
        occ[de_mod.get_tip()]--;
        cilindri[u.get_cilindri()] ++;
        occ[u.get_tip()]++;
        cilindri[u.get_cilindri()] --;

        for(auto& i: repo) {
            if(i.get_id() == id) i = u;
        }
        write_to_file();
    } catch (Exception& e) {
        //throw Exception(e.what());
    }
}

Utilaj Repo::search(int id) {
    for(auto& i: repo) {
        if(i.get_id() == id) return i;
    }
    throw Exception("Nu exista!");
}

void Repo::del(int id) {
    try {
        Utilaj u = search(id);
        occ[u.get_tip()] --;
        repo.erase(remove_if(repo.begin(), repo.end(), [&](Utilaj& u) {
            return u.get_id() == id;
        }));
        repo.pop_back();
        write_to_file();
    } catch (Exception& e) {}
}


vector<Utilaj> Repo::getAll() const {
    return repo;
}

map<string,int> Repo::getTipuri() const {
    return occ;
}

map<int,int> Repo::getCilindri() const {
    return cilindri;
}


