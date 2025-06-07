//
// Created by Mihai Moldovan on 21.05.2024.
//

#ifndef P3_FILE_REPO_H
#define P3_FILE_REPO_H
#include "domain.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

using std::getline;
using std::stringstream;
using std::vector;


class FileRepo {
public:
    FileRepo(string file_path): file_path{file_path} {
        read_from_file();
    }
    Elev cauta_elev(int nr_matricol);
    vector<Elev> get_all();

private:
    string file_path;
    vector<Elev> repo;
    void read_from_file();

};


#endif //P3_FILE_REPO_H
