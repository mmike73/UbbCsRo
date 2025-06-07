//
// Created by Mihai Moldovan on 20.05.2024.
//

#include "domain.h"

int Apartament::get_id() const {
    return id;
}
int Apartament::get_suprafata() const {
    return suprafata;
}

string Apartament::get_strada() const {
    return strada;
}

int Apartament::get_pret() const {
    return pret;
}

void Apartament::set_suprafata(int suprafata) {
    this->suprafata = suprafata;
}

void Apartament::set_pret(int pret) {
    this->pret = pret;
}

void Apartament::set_strada(string strada) {
    this->strada = strada;
}

string Apartament::text() {
    string list_item;
    list_item = std::to_string(id) + "  " + strada + " (" + std::to_string(suprafata) + " m^2)  " + std::to_string(pret) + " euro";
    return list_item;
}