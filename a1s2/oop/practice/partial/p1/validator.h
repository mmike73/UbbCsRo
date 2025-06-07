//
// Created by Mihai Moldovan on 18.05.2024.
//

#ifndef P1_VALIDATOR_H
#define P1_VALIDATOR_H
#include <string>
#include "exception.h"
using std::string;

class Validator {
public:
    Validator() = default;
    void valid_nume(const string& nume) const {
        if(nume.empty())  throw Exception("Numele trbuie sa fie nevid!");
    }

    void valid_socket(const string& socket) const {
        if(socket.empty())  throw Exception("Numele trbuie sa fie nevid!");
    }

    void valid_pret(const int& pret) const {
        if(pret <= 0) throw Exception("Pretul trbuie sa fie nenul pozitiv!");
    }
};


#endif //P1_VALIDATOR_H
