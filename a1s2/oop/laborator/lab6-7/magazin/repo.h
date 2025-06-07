//
// Created by Mihai Moldovan on 28.03.2024.
//

#ifndef LAB6_7_REPO_H
#define LAB6_7_REPO_H
#include "vector_template.h"
#include <iostream>
#include "domain.h"

class ProduseRepo {
private:
    Vector<Produs> produse;

    int pozitia_elementului(const int& id_produs) const {
        for (int i = 0; i < this->produse.size(); ++i)
            if (this->produse[i].get_id() == id_produs)
                return i;
        return -1;
    }

public:
    ProduseRepo() = default;

    /**
     * adauga produsul in repo
     * @param pr de tip Produs
     * arunca exceptie daca produsul deja exista
     */
    void adauga_produs_repo(const Produs& pr);

    /**
     * sterge produsul cu id-ul dat
     * @param id_produs de tip intreg
     */
    void sterge_produs_dupa_id_repo(const int& id_produs);

    /**
     * inlocuieste prdusul de la id-ul dat cu produsuul transmis
     * @param id
     * @param pr_modified
     */
    void modifica_produs_repo( const int& id, const Produs& pr_modified);

    /**
     * returneaza produsul cu id-ul transmis
     * @param id
     * arunca exceptie daca produsul nu exista
     * @return const Produs
     */
    Produs& cauta_produs_dupa_id_repo( const int& id);

    /**
     * returneaza toate produsele disponibile
     * @return const std::vector<Produs>
     */
    const Vector<Produs>& getAll() const noexcept;

};


#endif //LAB6_7_REPO_H
