//
// Created by Mihai Moldovan on 18.05.2024.
//

#ifndef P1_DOMAIN_PROCESOR_H
#define P1_DOMAIN_PROCESOR_H
#include <string>
using std::string;

class Procesor {
public:
    Procesor() = default;
    Procesor(string nume, int numar_threaduri, string socket, int pret):
            nume{nume}, numar_threaduri{numar_threaduri}, socket{socket}, pret{pret} {};

    string get_nume();
    int get_numar_threaduri();
    string get_socket() const;
    int get_pret();

    void set_nume(string nume);
    void set_numar_threaduri(int nr_threaduri);
    void set_socket(string socket);
    void set_pret(int pret);

private:
    int numar_threaduri, pret;
    string nume, socket;
};


#endif //P1_DOMAIN_PROCESOR_H
