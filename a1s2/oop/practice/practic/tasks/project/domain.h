//
// Created by Mihai Moldovan on 19.06.2024.
//

#ifndef PROJECT_DOMAIN_H
#define PROJECT_DOMAIN_H
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

class Task {
private:
    int id;
    string descriere, stare;
    vector<string> programatori;
public:
    //constructor
    Task(int id, string descriere, vector<string> programatori, string stare);

    //returneaza id-ul taskului - intreg
    int get_id() const;

    //returneaza descrierea taskului - string
    string get_descriere() const;

    //returneaza programatorii taskului - vector<string>
    vector<string> get_programatori() const;

    //returneaza stringul in formatul de pus in fisier csv
    string get_string() const;

    //returneaza starea taskului - string
    string get_stare() const;

    //modifica starea taskului
    // stare_noua poate fi open, inprograss sau closed
    void set_stare(string stare_noua);

};


#endif //PROJECT_DOMAIN_H
