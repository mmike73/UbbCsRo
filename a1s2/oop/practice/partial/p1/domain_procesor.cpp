//
// Created by Mihai Moldovan on 18.05.2024.
//

#include "domain_procesor.h"

string Procesor::get_nume() {
    return nume;
}

int Procesor::get_numar_threaduri() {
    return numar_threaduri;
}

string Procesor::get_socket() const {
    return socket;
}
int Procesor::get_pret() {
    return pret;
}

void Procesor::set_nume(string nume) {
    this->nume = nume;
}

void Procesor::set_numar_threaduri(int nr_threaduri) {
    numar_threaduri = nr_threaduri;
}

void Procesor::set_socket(string socket) {
    this->socket = socket;
}
void Procesor::set_pret(int pret) {
    this->pret = pret;
}