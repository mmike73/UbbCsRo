//
// Created by Mihai Moldovan on 28.03.2024.
//

#ifndef LAB6_7_UI_H
#define LAB6_7_UI_H
#include "service.h"

class UI {
private:
    ServiceProduse& service;
public:
    UI( ServiceProduse& service_produse)
        : service{service_produse} {

    }
    void adauga_produs(std::vector<std::string>& params);
    void vizualizeaza_produse(std::vector<std::string>& params);
    void sterge_produs(std::vector<std::string>& params);
    void modifica_produs(std::vector<std::string>& params);
    void sorteaza_produse(std::vector<std::string>& params);
    void adauga_produs_in_cos(std::vector<std::string>& params);
    void sterge_produs_in_cos(std::vector<std::string>& params);
    void vizualizeaza_produse_cos(std::vector<std::string>& params);
    void clear_cos(std::vector<std::string>& params);
    void random_cos(std::vector<std::string>& params);
    void export_cos(std::vector<std::string>& params);
    void print_catalog(std::vector<std::string>& params);
    void undo();

    void run();
};

#endif //LAB6_7_UI_H
