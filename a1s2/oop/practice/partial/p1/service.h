//
// Created by Mihai Moldovan on 18.05.2024.
//

#ifndef P1_SERVICE_H
#define P1_SERVICE_H
#include <vector>
#include <string>
#include <functional>
#include "repo.h"
#include "domain_placa.h"
#include "domain_procesor.h"
#include "validator.h"
using std::vector;
using std::string;

class Service {
public:
    Service(Repo<PlacaDeBaza>& repo_placi, Repo<Procesor>& repo_procesoare, Validator& validator):
        repo_placi{repo_placi}, repo_procesoare{repo_procesoare}, validator{validator} {};
    void add_placa(string& nume, string& socket, int pret) const;
    vector<PlacaDeBaza> filtreaza_placi(std::function <bool(const PlacaDeBaza& p)> filltru);
    Procesor cauta_procesor(string& nume);
    PlacaDeBaza cauta_placa(std::string &nume);
    vector<Procesor> get_procesoare() const;
    vector<PlacaDeBaza> get_placi() const;

private:
    Repo<PlacaDeBaza>& repo_placi;
    Repo<Procesor>& repo_procesoare;
    Validator& validator;
};


#endif //P1_SERVICE_H
