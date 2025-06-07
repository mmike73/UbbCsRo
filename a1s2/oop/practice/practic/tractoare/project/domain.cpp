//
// Created by Mihai Moldovan on 14.06.2024.
//

#include "domain.h"

Tractor::Tractor(int id, string denumire, string tip, int numar_roti)
    :id{id},denumire{denumire},tip{tip},numar_roti{numar_roti} {};

int Tractor::get_id() const {
    return id;
}

int Tractor::get_nr_roti() const {
    return numar_roti;
}
string Tractor::get_denumire() const {
    return denumire;
}
string Tractor::get_tip() const {
    return tip;
}

void Tractor::set_nr_roti(int nr_roti_nou) {
    numar_roti = nr_roti_nou;
}

string Tractor::str() const {
    return std::to_string(id) +','+ denumire+','+ tip +','+ std::to_string(numar_roti) +'\n';
}