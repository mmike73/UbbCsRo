//
// Created by Mihai Moldovan on 22.05.2024.
//

#include "service.h"
#include "validation.h"

vector<Log> Service::get_all() {
    return repo.get_all();
}

void Service::add_log(Log& l) {
    try {
        v.valid(l);
    } catch (Exception& e) {
        throw Exception(e.what());
    }
    repo.add_item(l);
}