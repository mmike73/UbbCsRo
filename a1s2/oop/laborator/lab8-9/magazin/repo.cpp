//
// Created by Mihai Moldovan on 28.03.2024.
//

#include "repo.h"
#include "exception.h"


void ProduseRepo::adauga_produs_repo(const Produs& pr) {
    if(cauta_produs_dupa_id_repo(pr.get_id()).get_nume() != "@invalid") {
        throw Exception("Produsul deja exista!!!\n");
    }
    this->produse.push_back(pr);
}

void ProduseRepo::sterge_produs_dupa_id_repo(const int& id_produs) {
    //rease remove
    //https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
    std::vector<Produs>::iterator ptr = produse.begin();
    while(ptr < produse.end() && ptr->get_id() != id_produs) ++ptr;
    if(ptr < produse.end() && ptr->get_id() == id_produs) {
        this->produse.erase(ptr);
    }
    else {
        throw Exception("Produsul nu exista!!!\n");
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

const std::vector<Produs>& ProduseRepo::getAll() const noexcept {
    return produse;
}


void ProduseRepoFile::adauga_produs_repo(const Produs& pr) {
    try {
        ProduseRepo::adauga_produs_repo(pr);
    } catch (Exception& e) {}
    save_to_file();
}

void ProduseRepoFile::sterge_produs_dupa_id_repo(const int& id_produs) {
    ProduseRepo::sterge_produs_dupa_id_repo(id_produs);
    save_to_file();
}

void ProduseRepoFile::modifica_produs_repo( const int& id, const Produs& pr_modified) {
    ProduseRepo::modifica_produs_repo(id, pr_modified);
    save_to_file();
}

std::vector<std::string> ProduseRepoFile::splt_line(std::string str, char separator) {
    std::vector<std::string> result;
    std::string current = "";
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == separator) {
            if (current != "") {
                result.push_back(current);
                current = "";
            }
            continue;
        }
        current += str[i];
    }
    if (current.empty() != 1)
        result.push_back(current);
    return result;
}
