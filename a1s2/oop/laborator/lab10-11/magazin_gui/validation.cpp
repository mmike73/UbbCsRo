//
// Created by Mihai Moldovan on 29.03.2024.
//

#include "validation.h"
#include "exception.h"

bool Validation::valideaza_ID(const int& id) const {
    if(id <= 0) {
        throw Exception("ID trebuie sa fie pozitiv nenul!!!\n");
    }
    return true;
}

bool Validation::valideaza_nume(const std::string& nume) const {
    if( nume.size() > 31) {
        throw Exception("Numele trebuie sa fie de maxim 30 de caractere!!!\n");
    }
    return true;
}

bool Validation::valideaza_tip(const std::string& tip) const {
    if( tip.size() > 31) {
        throw Exception("Tipul trebuie sa fie de maxim 30 de caractere!!!\n");
    }
    return true;
}

bool Validation::valideaza_pret(const int& pret) const {
    if(pret <= 0) {
        throw Exception("Pretul trebuie sa fie intreg strict mai mare decat 0!\n");
        return false;
    }
    return true;
}

bool Validation::valideaza_producator(const std::string& producator) const {
    if( producator.size() > 31) {
        throw Exception("Producatorul trebuie sa fie de maxim 30 de caractere!!!\n");
        return false;
    }
    return true;
}

bool Validation::valideaza_produs(const Produs& produs) const {
    int erori = 0;
    if(valideaza_ID(produs.get_id()) == 0) erori++;
    if(valideaza_nume(produs.get_nume()) == 0) erori++;
    if(valideaza_producator(produs.get_producator()) == 0) erori++;
    if(valideaza_pret(produs.get_pret()) == 0) erori++;
    if(valideaza_tip(produs.get_tip()) == 0) erori++;
    if(erori != 0) return false;
    return true;
}