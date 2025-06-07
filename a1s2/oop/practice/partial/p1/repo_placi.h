//
// Created by Mihai Moldovan on 19.05.2024.
//

#ifndef P1_REPO_PLACI_H
#define P1_REPO_PLACI_H
#include "repo.h"
#include "domain_placa.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using std::stringstream;
using std::getline;
using std::endl;
using std::stod;

class FileRepoPlaci: public Repo<PlacaDeBaza> {
public:
    FileRepoPlaci(string filename): filename{filename} {
        load_from_file();
    }

    void load_from_file() {
        std::ifstream fin(filename);
        if (!fin.is_open()) {
            std::cerr << "Error oppening file: " << filename << endl;
            return;
        }
        string line;
        while (getline(fin, line)) {
            stringstream linestream(line);
            string nume, socket;
            int pret;

            if (getline(linestream, nume, ',') &&
                //linestream.ignore(1, ',') &&
                getline(linestream, socket, ',') &&
                linestream >> pret) {

                PlacaDeBaza b{nume, socket, pret};
                //std::cout << b.get_nume() << ',' << b.get_socket() << ',' << b.get_pret() << "\n";

                try {
                    add_item(b);
                } catch (Exception &e) {
                    std::cerr << e.what() << endl;
                }
            } else {
                std::cerr << "Invalid format: " << line << endl;
            }
        }
        fin.close();
    }

    void write_to_file() {
        std::ofstream fout(filename);
        if (!fout.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }
        for (auto& placa : repo) {
            fout << placa.get_nume() << ',' << placa.get_socket() << ',' << placa.get_pret() << "\n";
        }
        fout.close();
    }

    void add_item(PlacaDeBaza p) override {
        Repo<PlacaDeBaza>::add_item(p);
        write_to_file();
    }

    void del_item(string nume) override {
        Repo<PlacaDeBaza>::del_item(nume);
        write_to_file();
    }

private:
    string filename;
};


#endif //P1_REPO_PLACI_H
