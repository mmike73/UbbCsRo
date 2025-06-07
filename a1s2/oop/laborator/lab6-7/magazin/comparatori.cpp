//
// Created by Mihai Moldovan on 31.03.2024.
//
#include "comparatori.h"

bool filtru_vid(const Produs& obiect, const std::string& orice_str, const int& orice_int) {
    return true;
}

bool filtru_pret(const Produs& obiect, const std::string& orice_str, const int& pret) {
    if( obiect.get_pret() == pret) return true;
    return false;
}

bool filtru_tip(const Produs& obiect, const std::string& orice_str, const int& pret) {
    if( obiect.get_tip() == orice_str) return true;
    return false;
}

bool filtru_nume(const Produs& obiect, const std::string& nume, const int& orice_int) {
    if(obiect.get_nume() == nume) {
        return true;
    }
    return false;
}

bool filtru_producator(const Produs& obiect, const std::string& producator, const int& orice_int) {
    if( obiect.get_producator() == producator) return true;
    return false;
}

int cmp_nume_c(const Produs& obiect1, const Produs& obiect2) {
    if( obiect1.get_nume() > obiect2.get_nume()) return -1;
    if( obiect1.get_nume() < obiect2.get_nume()) return 1;
    return 0;
}

int cmp_pret_c(const Produs& obiect1, const Produs& obiect2) {
    if( obiect1.get_pret() > obiect2.get_pret()) return -1;
    if( obiect1.get_pret() < obiect2.get_pret()) return 1;
    return 0;
}

int cmp_nume_pret_c(const Produs& obiect1, const Produs& obiect2) {
    if( obiect1.get_nume() > obiect2.get_nume()) return -1;
    if( obiect1.get_nume() < obiect2.get_nume()) return 1;
    if( obiect1.get_pret() > obiect2.get_pret()) return -1;
    if( obiect1.get_pret() < obiect2.get_pret()) return 1;
    return 0;
}

int cmp_nume_d(const Produs& obiect1, const Produs& obiect2) {
    if( obiect1.get_nume() < obiect2.get_nume()) return -1;
    if( obiect1.get_nume() > obiect2.get_nume()) return 1;
    return 0;
}

int cmp_pret_d(const Produs& obiect1, const Produs& obiect2) {
    if( obiect1.get_pret() < obiect2.get_pret()) return -1;
    if( obiect1.get_pret() > obiect2.get_pret()) return 1;
    return 0;
}

int cmp_nume_pret_d(const Produs& obiect1, const Produs& obiect2) {
    if( obiect1.get_nume() > obiect2.get_nume()) return 1;
    if( obiect1.get_nume() < obiect2.get_nume()) return -1;
    if( obiect1.get_pret() > obiect2.get_pret()) return 1;
    if( obiect1.get_pret() < obiect2.get_pret()) return -1;
    return 0;
}
