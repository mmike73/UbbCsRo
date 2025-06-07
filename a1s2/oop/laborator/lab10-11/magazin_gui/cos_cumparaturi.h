//
// Created by Mihai Moldovan on 13.04.2024.
//

#ifndef LAB6_7_COS_CUMPARATURI_H
#define LAB6_7_COS_CUMPARATURI_H
#include <vector>
#include "domain.h"
#include "repo.h"

class CosCumparaturi {
private:
    std::vector<int> cos;
    ProduseRepo& repo_produse;
    int total;

    const int pozitia_elementului(const int id) const{
        for( int i = 0; i < cos.size(); ++i) {
            if( cos[i] == id) return i;
        }
        return -1;
    }
public:
    CosCumparaturi(ProduseRepo& repo_produse):
        repo_produse{repo_produse} {
        total = 0;
    }
    void adauga_produs_cos(const int pr_id);
    void sterge_produs_cos(const int pr_id);
    const std::vector<int>& get_all_cos() const;
    void goleste_cos();
    int get_total_cos() const;
    void exporta_cos_csv(std::string file_path) const;

};


#endif //LAB6_7_COS_CUMPARATURI_H
