//
// Created by Mihai Moldovan on 28.03.2024.
//

#include "service.h"
#include "exception.h"

void ServiceProduse::adauga_produs_service(const int& id, const std::string& nume, const std::string& tip, const int& pret, const std::string& producator) {
    Produs produs{id,nume, tip, pret, producator};
    if(!validator_produse.valideaza_produs(produs)) return;
    repo_produse.adauga_produs_repo(produs);
}

void ServiceProduse::sterge_produs_service(const int& id) {
    repo_produse.sterge_produs_dupa_id_repo(id);
}

void ServiceProduse::modifica_produs_service(const int& id, const std::string& camp, const std::string& modificare_text, const int& modificare_numerica) {
    Produs de_modificat = this->cauta_produs_service(id);
    if( de_modificat.get_id() == -1) {
        Exception("Produsul cu idul dat nu exista!\n");
        return;
    }
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

Vector<Produs> ServiceProduse::filtreaza_produse( bool(*filtru)(const Produs&,const std::string& comparator_string, const int& comparator_int ), const std::string& valoare_str, const int& valoare_num )const {
    Vector<Produs> rezultat;
    for( const auto& produs: repo_produse.getAll()) {
        if( filtru(produs, valoare_str, valoare_num))
            rezultat.push_back(produs);
    }

    return rezultat;
}

Vector<Produs> ServiceProduse::sorteaza_produse( int(*cmp)(const Produs&, const Produs&) ) const {
    Vector<Produs> rezultat = repo_produse.getAll();
    int len = (int)rezultat.size();
    for( int i = 0; i < len - 1; ++i)
        for( int j = i + 1; j < len; ++j)
            if( cmp(rezultat[i], rezultat[j]) == -1)
                std::swap(rezultat[i], rezultat[j]);
    return rezultat;
}
