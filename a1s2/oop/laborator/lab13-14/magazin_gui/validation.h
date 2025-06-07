//
// Created by Mihai Moldovan on 29.03.2024.
//

#ifndef LAB6_7_VALIDATION_H
#define LAB6_7_VALIDATION_H
#include <string>
#include <iostream>
#include "domain.h"

class Validation {
public:
    /**
     *
     * @param id
     * @return
     */
    bool valideaza_ID(const int& id) const;

    /**
     *
     * @param nume
     * @return
     */
    bool valideaza_nume(const std::string& nume) const;

    /**
     *
     * @param tip
     * @return
     */
    bool valideaza_tip(const std::string& tip) const;

    /**
     *
     * @param pret
     * @return
     */
    bool valideaza_pret(const int& pret) const;

    /**
     *
     * @param producator
     * @return
     */
    bool valideaza_producator(const std::string& producator) const;

    /**
     *
     * @param produs
     * @return
     */
    bool valideaza_produs(const Produs& produs) const;

};


#endif //LAB6_7_VALIDATION_H
