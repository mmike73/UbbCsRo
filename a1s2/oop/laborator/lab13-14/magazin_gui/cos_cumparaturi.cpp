//
// Created by Mihai Moldovan on 13.04.2024.
//

#include "cos_cumparaturi.h"
#include <fstream>
#include <random>

void CosCumparaturi::adauga_produs_cos(const int pr_id) {
    cos.push_back(pr_id);
    //total += repo_produse.cauta_produs_dupa_id_repo(pr_id).get_pret();
    notify();
}

void CosCumparaturi::add_random() {
    std::vector<Produs> result_filter = repo_produse.getAll();
    std::mt19937 mt{std::random_device{}()};
    std::uniform_int_distribution<> dist(0, result_filter.size() - 1);
    int i = 0, p, n_elem = 10;
    while (++i <= n_elem) {
        p = dist(mt);
        adauga_produs_cos(result_filter[p].get_id());
    }
    notify();
}

int CosCumparaturi::get_total_cos() const {
    int tot = 0;
    std::vector<int> cos_c = get_all_cos();
    for(auto& i:cos_c) {
        tot += repo_produse.cauta_produs_dupa_id_repo(i).get_pret();
    }
    return tot;//rescrie functia ca sa recalculeze de fiecare data pretul
}

void CosCumparaturi::sterge_produs_cos(const int pr_id) {
    const int poz_de_sters = pozitia_elementului(pr_id);
    if(poz_de_sters != -1) {
        this->cos.erase(cos.begin() + poz_de_sters);
        total -= repo_produse.cauta_produs_dupa_id_repo(pr_id).get_pret();
    }
    notify();
}

const std::vector<int>& CosCumparaturi::get_all_cos() const {
    return cos;
}

void CosCumparaturi::exporta_cos_csv(std::string file_path) const {
    std::ofstream fout(file_path);
    fout << cos.size() << ":\n";
    fout<<"id"<<","<<"nume"<<","<<"tip"<<","<<"pret"<<","<<"producator"<<'\n';
    for( auto& i:cos) {
        Produs& prod = repo_produse.cauta_produs_dupa_id_repo(i);
        fout<<prod.get_id()<<","<<prod.get_nume()<<","<<prod.get_tip()<<","<<prod.get_pret()<<","<<prod.get_producator()<<'\n';
    }

    fout.close();
}

void CosCumparaturi::goleste_cos() {
    cos.clear();
    total = 0;
    notify();
}

