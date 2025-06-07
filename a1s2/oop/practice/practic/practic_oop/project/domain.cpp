//
// Created by Mihai Moldovan on 22.06.2024.
//

#include "domain.h"

int Utilaj::get_id() const {
    return id;
}
int Utilaj::get_cilindri() const {
    return cil;
}
string Utilaj::get_denumire() const {
    return denumire;
}
string Utilaj::get_tip() const {
    return tip;
}

void Utilaj::set_denumire(string denumire_noua) {
    denumire = denumire_noua;
}
void Utilaj::set_tip(string tip_nou) {
    tip = tip_nou;
}
void Utilaj::set_cilindri(int nr_cil) {
    cil = nr_cil;
}

string Utilaj::to_string() {
    return std::to_string(id) + ',' + denumire + ',' + tip + ',' + std::to_string(cil) + '\n';
}

Utilaj::Utilaj(int id, string denumire, string tip, int cil):
    id{id}, denumire{denumire}, tip{tip}, cil{cil} {
}

