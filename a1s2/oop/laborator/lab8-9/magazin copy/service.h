//
// Created by Mihai Moldovan on 28.03.2024.
//

#ifndef LAB6_7_SERVICE_H
#define LAB6_7_SERVICE_H
#include "repo.h"
#include "domain.h"
#include "validation.h"
#include "actiune_undo.h"
#include <vector>
#include <map>
#include "cos_cumparaturi.h"
#include <functional>

class ServiceProduse {
private:
    RepoInterface& repo_produse;
    Validation& validator_produse;
    CosCumparaturi& cos_cumparaturi;
    std::multimap<std::string,int> catalog;

    std::vector<std::unique_ptr<ActiuneUndo>> undoAction;

public:

    ServiceProduse( ProduseRepoFile& repo_produse, Validation& validator_produse, CosCumparaturi& cos_cumparaturi)
        : repo_produse{repo_produse}, validator_produse{validator_produse}, cos_cumparaturi{cos_cumparaturi} {
    }

    ServiceProduse(const ServiceProduse& ot) = delete;

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
    std::vector<Produs> filtreaza_produse( std::function<bool(const Produs&)> filtru)const;

    //comparatori:

    //
    /**
     *
     * @param cmp
     */
    std::vector<Produs> sorteaza_produse( std::function<int(const Produs& p1, const Produs& p2)> cmp) const;

    /**
     *
     * @param id
     */
    void adauga_inc_cos( const int id);

    /**
     *
     * @param id
     */
    void sterge_din_cos( const int id);

    const std::vector<int>& get_all_cos() const;

    const int get_total_cos();

    void goleste_cos();

    void exporta_cos_s(std::string file_path);

    std::multimap<std::string,int>& get_catalog();

    void undo();



};


#endif //LAB6_7_SERVICE_H
