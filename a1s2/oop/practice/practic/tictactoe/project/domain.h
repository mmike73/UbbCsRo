//
// Created by Mihai Moldovan on 21.06.2024.
//

#ifndef PROJECT_DOMAIN_H
#define PROJECT_DOMAIN_H
#include <string>
using std::string;

class Joc {
private:
    int id, dim;
    string tabla, stare;
    char jucator;
public:
    Joc(int id, int dim, char tabla, o)
    int get_id() const;
    int get_dim() const;
    string get_tabla() const;
    string get_stare() const;
    char get_jucator() const;

    void set_dim(int dim);
    void set_tabla(string tabla_noua);
    void set_jucatoe(char jucator_nou);
    void set_stare(string stare_noua);

    string get_save_format();

};


#endif //PROJECT_DOMAIN_H
