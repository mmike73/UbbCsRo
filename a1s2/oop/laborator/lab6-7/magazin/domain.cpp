//
// Created by Mihai Moldovan on 28.03.2024.
//

#include "domain.h"
#include <iostream>

void Produs::set_nume( const std::string& nume_nou) {
    this->nume = nume_nou;
}

void Produs::set_tip( const std::string& tip_nou) {
    this->tip = tip_nou;
}

void Produs::set_pret( const int& pret_nou) {
    this->pret = pret_nou;
}

void Produs::set_producator( const std::string& producator_nou) {
    this->producator = producator_nou;
}