//
// Created by Mihai Moldovan on 21.05.2024.
//

#ifndef P3_DOMAIN_H
#define P3_DOMAIN_H
#include <string>
#include <vector>
using std::string;
using std::vector;

class Elev {
public:
    Elev(int nr_matricol, string nume, string scoala, vector<string> activitati): nr_matricol{nr_matricol}, nume{nume}, scoala{scoala} {
        for(auto& i:activitati) {
            this->activitati.push_back(i);
        }
    }

    int get_nr_matricol() const;
    string get_nume() const;
    string get_scoala() const;

    void set_nr_matricol(int nr_nou);
    void set_nume(string nume_nou);
    void set_scoala(string scoala_noua);

    string get_str() const;
    string get_ateliere() const;
    vector<string> get_lista_ateliere() const;


        private:
    int nr_matricol;
    string nume, scoala;
    vector<string> activitati;

};


#endif //P3_DOMAIN_H
