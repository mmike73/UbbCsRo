//
// Created by Mihai Moldovan on 18.05.2024.
//

#include "domain_placa.h"

string PlacaDeBaza::get_nume() {
    return nume;
}

string PlacaDeBaza::get_socket() const {
    return socket;
}
int PlacaDeBaza::get_pret() {
    return pret;
}

void PlacaDeBaza::set_nume(string nume) {
    this->nume = nume;
}

void PlacaDeBaza::set_socket(string socket) {
    this->socket = socket;
}
void PlacaDeBaza::set_pret(int pret) {
    this->pret = pret;
}