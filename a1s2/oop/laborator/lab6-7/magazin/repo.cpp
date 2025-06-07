//
// Created by Mihai Moldovan on 28.03.2024.
//

#include "repo.h"
#include "exception.h"

void ProduseRepo::adauga_produs_repo(const Produs& pr) {
    if(cauta_produs_dupa_id_repo(pr.get_id()).get_nume() != "@invalid") {
        Exception("Produsul deja exista!!!\n");
        return;
    }
    this->produse.push_back(pr);
}

void ProduseRepo::sterge_produs_dupa_id_repo(const int& id_produs) {
    const int poz_de_sters = pozitia_elementului(id_produs);
    const Produs de_sters = cauta_produs_dupa_id_repo(id_produs);
    if(poz_de_sters != -1) {
        this->produse.erase( poz_de_sters);
    }
}

void ProduseRepo::modifica_produs_repo( const int& id, const Produs& pr_modified) {
    const int poz_modificare = pozitia_elementului(id);
    this->produse[poz_modificare] = pr_modified;
}

Produs& ProduseRepo::cauta_produs_dupa_id_repo( const int& id) {
    for( auto& prod: this->produse) {
        if( prod.get_id() == id) return prod;
    }
    static Produs invalid{-1,"@invalid","@invalid",-1,"@invalid"};
    return invalid;
}

const Vector<Produs>& ProduseRepo::getAll() const noexcept {
    return produse;
}
