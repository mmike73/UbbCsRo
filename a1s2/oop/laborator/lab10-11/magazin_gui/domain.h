//
// Created by Mihai Moldovan on 28.03.2024.
//

#ifndef LAB6_7_DOMAIN_H
#define LAB6_7_DOMAIN_H

#include <string>
#include <iostream>

class Produs {
private:
    int id;
    std::string nume;
    std::string tip;
    int pret;
    std::string producator;
public:

    Produs():
        id{0}, nume{""}, tip{""}, pret{0}, producator{""} {
    }

    Produs( const int& id, const std::string& nume, const std::string& tip, const int& pret, const std::string& producator)
        : id{id}, nume{nume}, tip{tip}, pret{pret}, producator{producator} {
        //
        //std::cout << "Creare\n";
        //
    }

    Produs( const Produs& other) {
        if (this != &other) {
            this->id = other.id;
            this->nume = other.nume;
            this->tip = other.tip;
            this->pret = other.pret;
            this->producator = other.producator;
        }
    }

    Produs& operator=(const Produs& other) {
        if (this != &other) {
            this->id = other.id;
            this->nume = other.nume;
            this->tip = other.tip;
            this->pret = other.pret;
            this->producator = other.producator;
        }
        return *this;
    }

    ~Produs() {
        //std::cout << "Distruge\n";
    }

    /**
     *
     * @return
     */
    int get_id() const {
        return id;
    }

    /**
     *
     * @return
     */
    std::string get_nume() const {
        return nume;
    }

    /**
     *
     * @return
     */
    std::string get_tip() const {
        return tip;
    }

    /**
     *
     * @return
     */
    int get_pret() const {
        return pret;
    }

    /**
     *
     * @return
     */
    std::string get_producator() const {
        return producator;
    }

    /**
     *
     * @param nume_nou
     */
    void set_nume( const std::string& nume_nou);

    /**
     *
     * @param tip_nou
     */
    void set_tip( const std::string& tip_nou);

    /**
     *
     * @param pret_nou
     */
    void set_pret( const int& pret_nou);

    /**
     *
     * @param producator_nou
     */
    void set_producator( const std::string& producator_nou);
};

#endif //LAB6_7_DOMAIN_H
