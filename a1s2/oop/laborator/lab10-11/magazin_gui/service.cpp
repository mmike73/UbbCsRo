//
// Created by Mihai Moldovan on 28.03.2024.
//

#include "service.h"
#include "exception.h"
#include <algorithm>

void ServiceProduse::adauga_produs_service(const int& id, const std::string& nume, const std::string& tip, const int& pret, const std::string& producator) {
    Produs produs{id,nume, tip, pret, producator};
    if(!validator_produse.valideaza_produs(produs)) return;
    repo_produse.adauga_produs_repo(produs);
    undoAction.push_back(std::make_unique<UndoAdauga>(repo_produse,id));
}

void ServiceProduse::sterge_produs_service(const int& id) {
    Produs& del = cauta_produs_service(id);
    if(del.get_id() == -1) {
        throw Exception("Produsul nu exista!!!");
    }
    undoAction.push_back(std::make_unique<UndoSterge>(repo_produse,del));
    repo_produse.sterge_produs_dupa_id_repo(id);
}

void ServiceProduse::modifica_produs_service(const int& id, const std::string& camp, const std::string& modificare_text, const int& modificare_numerica) {
    Produs de_modificat = this->cauta_produs_service(id);
    if( de_modificat.get_id() == -1) {
        throw Exception("Produsul cu idul dat nu exista!\n");
    }
    undoAction.push_back(std::make_unique<UndoModifica>(repo_produse,de_modificat));
    if( camp == "d") {
        de_modificat.set_nume(modificare_text);
    }
    if(camp == "t") {
        de_modificat.set_tip(modificare_text);
    }
    if(camp == "c") {
        de_modificat.set_pret(modificare_numerica);
    }
    if(camp == "p") {
        de_modificat.set_producator(modificare_text);
    }

    repo_produse.modifica_produs_repo(id, de_modificat);
}

Produs& ServiceProduse::cauta_produs_service(const int& id) {
    return repo_produse.cauta_produs_dupa_id_repo(id);
}

std::vector<Produs> ServiceProduse::filtreaza_produse( std::function<bool(const Produs&)> filtru)const {
    std::vector<Produs> brut = repo_produse.getAll();
    std::vector<Produs> rezultat;
    std::copy_if(brut.begin(),brut.end(),std::back_inserter(rezultat),filtru);
    return rezultat;
}

std::vector<Produs> ServiceProduse::sorteaza_produse( std::function<int(const Produs& p1, const Produs& p2)> cmp) const {
    std::vector<Produs> rezultat = repo_produse.getAll();
    std::sort(rezultat.begin(), rezultat.end(), cmp);
    return rezultat;
}

void ServiceProduse::adauga_inc_cos( const int id) {
    if( cauta_produs_service(id).get_id() != -1) {
        cos_cumparaturi.adauga_produs_cos(id);
    }
    else {
        throw Exception("Produsul nu exista!\n");
    }
}

void ServiceProduse::sterge_din_cos( const int id) {
    if( cauta_produs_service(id).get_id() != -1) {
        cos_cumparaturi.sterge_produs_cos(id);
    }
    else {
        throw Exception("Produsul nu exista!\n");
    }
}

const std::vector<int>& ServiceProduse::get_all_cos() const {
    return cos_cumparaturi.get_all_cos();
}

const int ServiceProduse::get_total_cos() {

    return cos_cumparaturi.get_total_cos();
}

void ServiceProduse::goleste_cos() {
    cos_cumparaturi.goleste_cos();
}

void ServiceProduse::exporta_cos_s(std::string file_path) {
    cos_cumparaturi.exporta_cos_csv(file_path);
}

std::multimap<std::string,int>& ServiceProduse::get_catalog() {
    return repo_produse.catalog;
}

void ServiceProduse::undo() {
    if( undoAction.empty())
        throw Exception("Nu mai exista modificari de anulat!!!\n");
    undoAction.back()->doUndo();
    undoAction.pop_back();
}