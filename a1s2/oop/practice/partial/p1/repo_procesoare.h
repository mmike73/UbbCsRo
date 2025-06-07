//
// Created by Mihai Moldovan on 19.05.2024.
//

#ifndef P1_REPO_PROCESOARE_H
#define P1_REPO_PROCESOARE_H
#include "repo.h"
#include "domain_procesor.h"
#include <string>
#include <vector>

#include <iostream>
#include <fstream>
#include <sstream>

using std::stringstream;
using std::getline;
using std::endl;
using std::stod;

class FileRepoProcesoare: public Repo<Procesor> {
public:
    FileRepoProcesoare(string filename): filename{filename} {
        load_from_file();
    }

    void load_from_file() {
        std::ifstream fin(filename);
        //
        if (!fin.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }
        //

        string line;
        while (std::getline(fin, line)) {
            stringstream linestream(line);
            string nume, socket;
            int nr_threaduri, pret;

            // Using getline to parse CSV directly
            if (std::getline(linestream, nume, ',') &&
                linestream >> nr_threaduri &&
                linestream.ignore(1, ',') && // ignore the comma
                std::getline(linestream, socket, ',') &&
                linestream >> pret) {
                Procesor p{nume, nr_threaduri, socket, pret};
                try {
                    add_item(p);
                } catch (const Exception& e) {
                    std::cerr << e.what() << endl;
                }
            } else {
                std::cerr << "Invalid format in line: " << line << std::endl;
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
        for (auto& procesor : repo) {
            fout << procesor.get_nume() << ',' << procesor.get_socket() << ',' << procesor.get_pret() << "\n";
        }
        fout.close();
    }

private:
    string filename;
};


#endif //P1_REPO_PROCESOARE_H
