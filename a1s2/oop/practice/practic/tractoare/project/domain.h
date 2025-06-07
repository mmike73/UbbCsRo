//
// Created by Mihai Moldovan on 14.06.2024.
//

#ifndef PROJECT_DOMAIN_H
#define PROJECT_DOMAIN_H
#include <string>
using std::string;

class Tractor {
private:
    int id, numar_roti;
    string denumire, tip;
public:
    Tractor(int id, string denumire, string tip, int numar_roti);

    //returneaza id-ul tractorului
    int get_id() const;

    //returneaza numarul de roti
    int get_nr_roti() const;

    //returneaza denumirea tractorului
    string get_denumire() const;

    //returneaza tipul treactorului
    string get_tip() const;

    void set_nr_roti(int nr_roti_nou);

    string str() const;
};


#endif //PROJECT_DOMAIN_H
