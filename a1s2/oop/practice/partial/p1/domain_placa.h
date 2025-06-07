//
// Created by Mihai Moldovan on 18.05.2024.
//

#ifndef P1_DOMAIN_PLACA_H
#define P1_DOMAIN_PLACA_H
#include <string>
using std::string;

class PlacaDeBaza {
public:
    PlacaDeBaza() = default;
    PlacaDeBaza(string nume, string socket, int pret):
        nume{nume}, socket{socket}, pret{pret} {};

    string get_nume();
    string get_socket() const;
    int get_pret();

    void set_nume(string nume);
    void set_socket(string socket);
    void set_pret(int pret);

private:
    int pret;
    string nume, socket;
};


#endif //P1_DOMAIN_PLACA_H
