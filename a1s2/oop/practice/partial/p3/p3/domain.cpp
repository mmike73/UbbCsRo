//
// Created by Mihai Moldovan on 21.05.2024.
//

#include "domain.h"

int Elev::get_nr_matricol() const{
    return nr_matricol;
}
string Elev::get_nume() const{
    return nume;
}
string Elev::get_scoala() const{
    return scoala;
}

void Elev::set_nr_matricol(int nr_nou) {
    nr_matricol = nr_nou;
}

void Elev::set_nume(string nume_nou) {
    nume = nume_nou;
}
void Elev::set_scoala(string scoala_noua) {
    scoala = scoala_noua;
}

string Elev::get_str() const {
    string s;
    s += nume + " " + scoala;
    return s;
}

string Elev::get_ateliere() const {
    string s;
    for(string i:activitati)
        s += i + " ";
    return s;
}

vector<string> Elev::get_lista_ateliere() const {
    return activitati;
}
