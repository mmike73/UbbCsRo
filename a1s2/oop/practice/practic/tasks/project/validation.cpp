//
// Created by Mihai Moldovan on 19.06.2024.
//

#include "validation.h"

void Validation::valid_id(const Task& t) {
    if(t.get_id() < 1) throw Exception("ID trebuie sa fie intreg pozitiv\n");
}

void Validation::valid_descriere(const Task& t) {
    if(t.get_descriere().size() == 0) throw Exception("Introduceti o destriere\n");
}

void Validation::valid_programatori(const Task& t) {
    vector<string> ps = t.get_programatori();
    if(ps.size() > 4 || ps .size() == 0) throw Exception("Numarul maxim de programatori e 4\n");
    for(auto& p:ps) {
        if(p.size() == 0) throw Exception("Numele porgramatorului nu poate fi vid\n");
    }
}

void Validation::valid_stare(const Task& t) {
    string s = t.get_stare();
    if(s == "open") return;
    if(s == "inprogress") return;
    if(s == "closed") return;
    throw Exception("Starea poate fi doar open/inprogress/closed\n");
}

void Validation::valid_task(const Task& t) {
    string problems;
    try {
        valid_id(t);
    } catch (Exception& e) {
        problems += e.what();
    }
    try {
        valid_descriere(t);
    } catch (Exception& e) {
        problems += e.what();
    }
    try {
        valid_programatori(t);
    } catch (Exception& e) {
        problems += e.what();
    }
    try {
        valid_stare(t);
    } catch (Exception& e) {
        problems += e.what();
    }
    if(problems.size() != 0) {
        throw Exception(problems);
    }
}