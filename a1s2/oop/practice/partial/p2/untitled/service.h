//
// Created by Mihai Moldovan on 20.05.2024.
//

#ifndef UNTITLED_SERVICE_H
#define UNTITLED_SERVICE_H
#include "repo.h"
#include <functional>

class Service {
public:
    Service(Repo& repo): repo{repo} {}

    vector<Apartament> filtreaza(std::function<bool(Apartament& a)> filtru);
    void sterge_apartament(int id);
    vector<Apartament> get_all() const;

private:
    Repo& repo;
};


#endif //UNTITLED_SERVICE_H
