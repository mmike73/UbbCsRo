//
// Created by Mihai Moldovan on 21.06.2024.
//

#include "domain.h"

Joc::Joc()

int Joc::get_id() const {
    return id
}
int Joc::get_dim() const {
    return dim;
}
string Joc::get_tabla() const {
    return tabla;
}
string Joc::get_stare() const {
    return stare;
}
char Joc::get_jucator() const {
    return jucator;
}

void Joc::set_dim(int dim_noua) {
    dim = dim_noua
}
void Joc::set_tabla(string tabla_noua) {
    tabla = tabla_noua;
}
void Joc::set_jucatoe(char jucator_nou) {
    jucator = jucator_nou;
}
void Joc::set_stare(string stare_noua) {
    stare = stare_noua;
}

string Joc::get_save_format() {
    return std::to_string(id) + " " + std::to_string(dim) + " " + tabla + " " + jucator + " " + stare + '\n';
}
