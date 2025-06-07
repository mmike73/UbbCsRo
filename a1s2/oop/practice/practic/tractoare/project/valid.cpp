//
// Created by Mihai Moldovan on 14.06.2024.
//

#include "valid.h"
#include "exception.h"

void Valid::valideaza_tractor(Tractor& t) {
    string erori;
    try {
        valideaza_id(t);
    } catch (Exception& e) {
        erori += e.what();
    }
    try {
        valideaza_denumire(t);
    } catch (Exception& e) {
        erori += e.what();
    }
    try {
        valideaza_tip(t);
    } catch (Exception& e) {
        erori += e.what();
    }
    try {
        valideaza_nr_roti(t);
    } catch (Exception& e) {
        erori += e.what();
    }
    if(erori.size() != 0) {
        throw Exception(erori);
    }
}

void Valid::valideaza_id(Tractor& t) {
    if(t.get_id() <= 0) throw Exception("ID trebuie sa fie intreg pozitiv!\n");
}

void Valid::valideaza_denumire(Tractor& t) {
    if(t.get_tip().size() == 0) {
        throw Exception("Denumirea trebuie sa fie un sir de caractere nenul!\n");
    }
}

void Valid::valideaza_tip(Tractor& t) {
    if(t.get_tip().size() == 0) {
        throw Exception("Tipul trebuie sa fie un sir de caractere nenul!\n");
    }
}

void Valid::valideaza_nr_roti(Tractor& t) {
    if(t.get_nr_roti() % 2 != 0 || t.get_nr_roti() < 2 || t.get_nr_roti() > 16)
        throw Exception("Numarul de roti trebuie sa fie intreg par intre 2 si 16!\n");
}