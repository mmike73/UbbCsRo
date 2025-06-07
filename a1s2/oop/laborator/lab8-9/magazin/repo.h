//
// Created by Mihai Moldovan on 28.03.2024.
//

#ifndef LAB6_7_REPO_H
#define LAB6_7_REPO_H
#include <vector>
#include <iostream>
#include <fstream>
#include "domain.h"
#include <sstream>
#include "exception.h"


using std::stringstream;
using std::endl;
using std::getline;
using std::stod;

class RepoInterface {
protected:
    std::vector<Produs> produse;

    virtual int pozitia_elementului(const int& id_produs) const = 0;

public:

    /**
     * adauga produsul in repo
     * @param pr de tip Produs
     * arunca exceptie daca produsul deja exista
     */
    virtual void adauga_produs_repo(const Produs& pr) = 0;

    /**
     * sterge produsul cu id-ul dat
     * @param id_produs de tip intreg
     */
    virtual void sterge_produs_dupa_id_repo(const int& id_produs) = 0;

    /**
     * inlocuieste prdusul de la id-ul dat cu produsuul transmis
     * @param id
     * @param pr_modified
     */
    virtual void modifica_produs_repo( const int& id, const Produs& pr_modified) = 0;

    /**
     * returneaza produsul cu id-ul transmis
     * @param id
     * arunca exceptie daca produsul nu exista
     * @return const Produs
     */
    virtual Produs& cauta_produs_dupa_id_repo( const int& id) = 0;

    /**
     * returneaza toate produsele disponibile
     * @return const std::vector<Produs>
     */
    virtual const std::vector<Produs>& getAll() const noexcept = 0;
};

class ProduseRepo: public RepoInterface{
protected:

    int pozitia_elementului(const int& id_produs) const override {
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
    virtual void adauga_produs_repo(const Produs& pr) override;

    /**
     * sterge produsul cu id-ul dat
     * @param id_produs de tip intreg
     */
    virtual void sterge_produs_dupa_id_repo(const int& id_produs) override;

    /**
     * inlocuieste prdusul de la id-ul dat cu produsuul transmis
     * @param id
     * @param pr_modified
     */
    virtual void modifica_produs_repo( const int& id, const Produs& pr_modified) override;

    /**
     * returneaza produsul cu id-ul transmis
     * @param id
     * arunca exceptie daca produsul nu exista
     * @return const Produs
     */
    Produs& cauta_produs_dupa_id_repo( const int& id) override;

    /**
     * returneaza toate produsele disponibile
     * @return const std::vector<Produs>
     */
     const std::vector<Produs>& getAll() const noexcept override;

};

class ProduseRepoFile: public ProduseRepo {
private:
    std::string cale_fisier;

    std::vector<std::string> splt_line(std::string str, char separator);


    void load_from_file() {
        std::ifstream fin(cale_fisier);
        std::string line;

        stringstream linestream(line);
        std::string current;
        int ind = 0;

        while(getline(fin, line)) {
            std::string denumire, tip, producator;
            int id, pret;

            std::vector<std::string> elems = splt_line(line, ',');

            if(elems.size() == 5) {
                id = std::stoi(elems[0]);
                denumire = elems[1];
                tip = elems[2];
                pret = std::stoi(elems[3]);
                producator = elems[4];
            }
            Produs pr{id,denumire,tip,pret,producator};
            std::cout<<pr.get_id()<<","<<pr.get_nume()<<","<<pr.get_tip()<<","<<pr.get_pret()<<","<<pr.get_producator()<<'\n';
            try {
                ProduseRepo::adauga_produs_repo(pr);
            } catch (Exception& e) {
            }
        }

        fin.close();
    }

    void save_to_file() {
        std::ofstream fout(cale_fisier);
        if(!fout.is_open()) {
            throw Exception("Fisierul nu e deschis!!!\n");
        }
        for( auto& prod:produse) {
            /////////REZ
            fout<<prod.get_id()<<","<<prod.get_nume()<<","<<prod.get_tip()<<","<<prod.get_pret()<<","<<prod.get_producator()<<'\n';
        }
        fout.close();
    }

public:

    ProduseRepoFile(std::string cale_f): ProduseRepo(), cale_fisier(cale_f) {
        load_from_file();
    };

    void adauga_produs_repo(const Produs& pr) override;

    void sterge_produs_dupa_id_repo(const int& id_produs) override;

    void modifica_produs_repo( const int& id, const Produs& pr_modified) override;



};




#endif //LAB6_7_REPO_H
