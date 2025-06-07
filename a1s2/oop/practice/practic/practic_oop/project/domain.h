//
// Created by Mihai Moldovan on 22.06.2024.
//

#ifndef PROJECT_DOMAIN_H
#define PROJECT_DOMAIN_H
#include <string>
using std::string;

class Utilaj {
private:
    int id, cil;
    string denumire, tip;

public:
    Utilaj(int id, string denumire, string tip, int cil);

    int get_id() const;
    int get_cilindri() const;
    string get_denumire() const;
    string get_tip() const;

    void set_denumire(string denumire_noua);
    void set_tip(string tip_nou);
    void set_cilindri(int nr_cil);

    string to_string();

};


#endif //PROJECT_DOMAIN_H
