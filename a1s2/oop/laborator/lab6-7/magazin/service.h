//
// Created by Mihai Moldovan on 28.03.2024.
//

#ifndef LAB6_7_SERVICE_H
#define LAB6_7_SERVICE_H
#include "repo.h"
#include "domain.h"
#include "validation.h"
#include <vector>

class ServiceProduse {
private:
    ProduseRepo repo_produse;
    Validation validator_produse;
public:

    ServiceProduse( ProduseRepo& repo_produse, Validation& validator_produse)
        : repo_produse{repo_produse}, validator_produse{validator_produse} {
    }

    /**
     * creeaza obiectul de tip produs, il valideaza si il adauga in magazin
     * @param id
     * @param nume
     * @param tip
     * @param pret
     * @param producator
     */
    void adauga_produs_service(const int& id, const std::string& nume, const std::string& tip, const int& pret, const std::string& producator);

    /**
     * elimina elementul cu id-ul dat
     * @param id
     */
    void sterge_produs_service(const int& id);

    /**
     * modifica obiectul cu idul trensmis
     * @param id
     * @param camp
     * @param modificare_text
     * @param modificare_numerica
     */
    void modifica_produs_service(const int& id, const std::string& camp, const std::string& modificare_text, const int& modificare_numerica);

    /**
     *
     * @param id
     */
    Produs& cauta_produs_service(const int& id);

    /**
     *
     * @param filtru
     */
    Vector<Produs> filtreaza_produse( bool(*filtru)(const Produs&,const std::string& comparator_string, const int& comparator_int ), const std::string& valoare_str, const int& valoare_num )const;

    //comparatori:

    //
    /**
     *
     * @param cmp
     */
    Vector<Produs> sorteaza_produse( int(*cmp)(const Produs&, const Produs&) ) const;
};


#endif //LAB6_7_SERVICE_H
