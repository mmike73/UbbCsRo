//
// Created by Mihai Moldovan on 21.05.2024.
//

#include "file_repo.h"

void FileRepo::read_from_file() {
    std::ifstream fin(file_path);
    string line;
    string nr_m,nume,scoala,activitate;
    int nr_matricol;
    vector<string> activitati;

    while(getline(fin,line)) {
        stringstream orice(line); // ca si la ifstram
        getline(orice,nr_m,',');
        getline(orice,nume,',');
        getline(orice,scoala,',');
        activitati.clear();
        while (getline(orice,activitate,',')) {
            activitati.push_back(activitate);
        }
        nr_matricol = std::stoi(nr_m);
        Elev e(nr_matricol,nume,scoala,activitati);
        repo.push_back(e);
    }
}

Elev FileRepo::cauta_elev(int nr_matricol) {
    for(const auto& i: repo) {
        if(i.get_nr_matricol() == nr_matricol) return i;
    }
    vector<string> act_inv;
    Elev invalid(-1,"","", act_inv);
    return invalid;
}


vector<Elev> FileRepo::get_all() {
    return repo;
}

