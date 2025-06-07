//
// Created by Mihai Moldovan on 19.06.2024.
//

#include "repo.h"


Repo::Repo(string file_path): cale_fisier{file_path} {
    read_from_file();
}

void Repo::add(Task& t) {
    if(seaarch(t.get_id()).get_id() == -1) {
        repo.push_back(t);
    }
}

Task Repo::seaarch(int id) const {
    for(auto& i:repo) {
        if( i.get_id() == id) return i;
    }
    Task t_invalid{-1,"",{""},""};
    return t_invalid;
}

vector<Task> Repo::get_all() const {
    return repo;
}

void Repo::read_from_file() {
    ifstream fin(cale_fisier);

    string line;
    string id_s, descriere, stare,programator;
    vector<string> programatori;

    while(getline(fin,line)) {
        stringstream linestream(line);

        programatori.clear();
        programator.clear();

        getline(linestream,id_s,',');
        getline(linestream,descriere,',');
        while(programator != "open" && programator != "inprogress" && programator != "closed") {
            if(programator != "") programatori.push_back(programator);
            getline(linestream,programator,',');
        }
        stare = programator;

        int id = std::stoi(id_s);
        Task t{id,descriere,programatori,stare};
        add(t);
        std::cout << t.get_string();
    }
    fin.close();
}
void Repo::write_to_file() {
    ofstream fout(cale_fisier);
    for(auto& i:repo) {
        fout << i.get_string();
    }
    fout.close();
}

void Repo::modifica_stare_dupa_id(int id, string stare) {
    for(auto& i:repo) {
        if(i.get_id() == id) {
            i.set_stare(stare);
            break;
        }
    }
}
