//
// Created by Mihai Moldovan on 20.05.2024.
//

#include "repo.h"

void Repo::read_from_file() {
    std::ifstream fin(cale_fisier);

    string line;
    while(getline(fin,line)) {
        stringstream linestream(line);
        string strada;
        int suprafata, pret, id;

        if(linestream >> id &&
            linestream.ignore(1,',') &&
            linestream >> suprafata &&
            linestream.ignore(1,',') &&
            getline(linestream,strada,',') &&
            linestream >> pret) {

            Apartament a{id,suprafata,strada,pret};
            add_item(a);
            //std::cout << a.text() << '\n';
        }
    }
    fin.close();
}

void Repo::write_to_file() {
    std::ofstream fout(cale_fisier);
    for(auto& i:repo)
        fout << i.get_id() << ',' <<i.get_suprafata() <<',' << i.get_strada() <<','<<i.get_pret() << '\n';
    fout.close();
}

void Repo::add_item(Apartament& a) {
    //if(search_item(a.get_id()).get_id() != -1) {
        //throw Exception()
    //    return;
    //}
    repo.push_back(a);
}
Apartament Repo::search_item(int id) {
    Apartament a{-1,-1,"",-1};
    for(const auto& apartament: repo) {
        if(apartament.get_id() == id) return apartament;
    }
    return a;
}

void Repo::delete_item(int id) {
    if(search_item(id).get_id() != -1) {
        auto it = std::remove_if(repo.begin(), repo.end(), [id](const Apartament &a) { return a.get_id() == id; });
        repo.erase(it);
        write_to_file();
    }
}

vector<Apartament> Repo::get_all() {
    return repo;
}