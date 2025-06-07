//
// Created by Mihai Moldovan on 22.05.2024.
//

#include "validation.h"
#include "exception.h"

bool Validation::valid_id(Log& l) {
    if(l.get_id().size() != 4) return false;
    return true;
}
bool Validation::valid_pid(Log& l) {
    if(l.get_PID() <= 0) return false;
    return true;
}
bool Validation::valid_level(Log& l) {
    if(l.get_level() == "info") return true;
    if(l.get_level() == "warnig") return true;
    if(l.get_level() == "error") return true;
    if(l.get_level() == "critical") return true;
    return false;
}
void Validation::valid(Log& l) {
    if(!valid_id(l)) {
        throw Exception("ID trebuie sa aiba 4 caractere!");
    }
    if(!valid_pid(l)) {
        throw Exception("PID trebuie sa fie >= 0!");
    }
    if(!valid_level(l)) {
        throw Exception("Level trebuie sa fie info, warning error sau critical!");
    }

}