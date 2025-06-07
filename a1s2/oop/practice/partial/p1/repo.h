//
// Created by Mihai Moldovan on 18.05.2024.
//

#ifndef P1_REPO_H
#define P1_REPO_H
#include "domain_placa.h"
#include "domain_procesor.h"
#include "exception.h"
#include <vector>
using std::string;
using std::vector;

template<typename T>
class Repo {
protected:
    std::vector<T> repo;

public:
    virtual void add_item(T item);
    virtual void del_item(string nume);
    T search_item(string name);
    std::vector<T> get_all();
};

template<typename T>
void Repo<T>::add_item(T item) {
    if(search_item(item.get_nume()).get_nume() != "@invalid") {
        throw Exception("Produsul deja exista!");
    }
    repo.push_back(item);
}

template<typename T>
void Repo<T>::del_item(string nume) {
    T searched = search_item(nume);
    if(searched.get_nume() == "@invalid") {
        throw Exception("Produsul NU exista!");
    }
    auto it = std::remove_if(repo.begin(),repo.end(),[nume](T p) {
        return p.get_nume() == nume;
    });
    repo.erase(it);
}

template<typename T>
T Repo<T>::search_item(string name) {
    for(auto& i: repo)
        if(i.get_nume() == name)
            return i;
    T inv;
    inv.set_nume("@invalid");
    return inv;
}

template<typename T>
std::vector<T> Repo<T>::get_all() {
    return repo;
}

#endif //P1_REPO_H
