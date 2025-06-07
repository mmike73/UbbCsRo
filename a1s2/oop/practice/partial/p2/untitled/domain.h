//
// Created by Mihai Moldovan on 20.05.2024.
//

#ifndef UNTITLED_DOMAIN_H
#define UNTITLED_DOMAIN_H
#include <string>
using std::string;

class Apartament {
public:
    Apartament(int id, int suprafata, string strada, int pret): id{id}, suprafata{suprafata}, strada{strada}, pret{pret} {};

    int get_id() const;
    int get_suprafata() const;
    string get_strada() const;
    int get_pret() const;

    void set_suprafata(int suprafata);
    void set_pret(int pret);
    void set_strada(string strada);

    string text();

        private:
    int id, suprafata, pret;
    string strada;
};


#endif //UNTITLED_DOMAIN_H
