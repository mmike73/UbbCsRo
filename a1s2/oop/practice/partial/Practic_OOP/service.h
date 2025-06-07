//
// Created by Mihai Moldovan on 22.05.2024.
//

#ifndef PRACTIC_OOP_SERVICE_H
#define PRACTIC_OOP_SERVICE_H
#include "repo.h"
#include "validation.h"
#include "exception.h"

class Service {
public:
    Service(Repo& repo,Validation& v): repo{repo}, v{v} {}
    void add_log(Log& l);
    vector<Log> get_all();
private:
    Repo& repo;
    Validation& v;
};


#endif //PRACTIC_OOP_SERVICE_H
