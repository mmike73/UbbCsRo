//
// Created by Mihai Moldovan on 18.06.2024.
//

#include "repo.h"
#include "exception.h"

Repo::Repo(string cale_fisier): cale_fisier{cale_fisier} {
    read_from_file();
}

void Repo::adauga_melodie(Melodie& melodie) {
    if(cauta_melodie(melodie.get_id()).get_id() == -1) {
        repo.push_back(melodie);
        if(ranks.find(melodie.get_rank()) != ranks.end()) {
            ranks.find(melodie.get_rank())->second++;
        } else {
            ranks.insert({melodie.get_rank(),1});
        }
        if(nr_piese.find(melodie.get_artist()) != nr_piese.end()) {
            nr_piese.find(melodie.get_artist())->second++;
        } else {
            nr_piese.insert({melodie.get_artist(),1});
        }
    } else {
        throw(Exception("Melodia deja exista!"));
    }
}


Melodie Repo::cauta_melodie(int id) const {
    for(auto& i: repo) {
        if(i.get_id() == id) return i;
    }
    Melodie invalida{-1,"","",-1};
    return invalida;
}

void Repo::sterge_melodie(int id) {
    Melodie melodie = cauta_melodie(id);
    if(nr_piese.find(melodie.get_artist())->second > 1) {
        auto de_sters = remove_if(repo.begin(), repo.end(), [&](const Melodie &m) {
            return m.get_id() == id;
        });
        repo.erase(de_sters);
        ranks.find(melodie.get_rank())->second--;
        nr_piese.find(melodie.get_artist())->second--;
    } else {
        throw Exception("Acesta este ultima piesa a artistului!\n");
    }
}

void Repo::modifica_melodie(int id, Melodie &m) {
    if(cauta_melodie(id).get_id() != -1) {
        auto it = repo.begin();
        while(it->get_id() != id) it++;
        ranks.find(it->get_rank())->second--;
        it->set_rank(m.get_rank());
        it->set_titlu(m.get_titlu());
        if(ranks.find(m.get_rank()) != ranks.end()) {
            ranks.find(m.get_rank())->second++;
        } else {
            ranks.insert({m.get_rank(),1});
        }
    }
    write_to_file();
}

vector<Melodie> Repo::get_all_melodii() const {
    return repo;
}

map<int,int> Repo::get_all_ranks() const {
    return ranks;
}

map<string,int> Repo::get_all_artists() const {
    return nr_piese;
}

void Repo::read_from_file() {
    ifstream fin (cale_fisier);

    string line, id_string, rank_string, artist, titlu;

    while(getline(fin,line)) {
        stringstream linestream(line);
        getline(linestream,id_string,',');
        getline(linestream,titlu,',');
        getline(linestream,artist,',');
        getline(linestream,rank_string,',');
        int id, rank;
        try {
            id = std::stoi(id_string);
        } catch(exception& e) {
            std::cout << e.what() << '\n';
        }
        try {
            rank = std::stoi(rank_string);
        } catch(exception& e) {
            std::cout << e.what() << '\n';
        }

        Melodie m{id,titlu,artist,rank};
        adauga_melodie(m);
        std::cout << m.to_string();
    }
    fin.close();
}

void Repo::write_to_file() {
    ofstream fout(cale_fisier);

    for(auto& i:repo) {
        fout << i.to_string();
    }

    fout.close();
}
