//
// Created by Mihai Moldovan on 14.06.2024.
//

#include "repo.h"

Repo::Repo(string filename)
    : filename{filename} {
    read_from_file();
};

void Repo::read_from_file() {
    std::ifstream fin("../"+filename);
    if(!fin.is_open()) std::cout  << "Shit\n";

    string id, denumire, tip, nr_roti;
    int id_t, nr_rosti_t;

    string line;
    while(getline(fin,line)) {
        stringstream fields(line);

        getline(fields, id,',');
        getline(fields, denumire,',');
        getline(fields, tip,',');
        getline(fields, nr_roti,',');

        id_t = stoi(id);
        nr_rosti_t = stoi(nr_roti);

        Tractor t(id_t,denumire,tip,nr_rosti_t);

        add(t);
    }
    fin.close();
}

void Repo::write_to_file() {
    std::ofstream  fout("../" + filename);

    for(auto& i:repo) {
        fout << i.str();
    }

    fout.close();
}

void Repo::add(Tractor &t) {
    if(search(t.get_id()).get_id() == -1) {
        repo.push_back(t);
        write_to_file();
        if(occ.find(t.get_tip()) != occ.end()) occ.find(t.get_tip())->second++;
        else occ.insert({t.get_tip(),1});
    }
}

Tractor Repo::search(int id) {
    for(Tractor& i:repo) {
        if(i.get_id() == id) return i;
    }
    Tractor t(-1,"","",-1);
    return t;
}

vector<Tractor> Repo::get_all() {
    return repo;
}

void Repo::modifica_nr_roti(int id, int nr_roti_nou) {
    for(Tractor& i: repo) {
        if(i.get_id() == id) {
            i.set_nr_roti(nr_roti_nou);
            write_to_file();
            break;
        }
    }
}

map<string, int> Repo::get_occurences() {
    return occ;
}