//
// Created by Mihai Moldovan on 31.03.2024.
//

#ifndef LAB6_7_COMPARATORI_H
#define LAB6_7_COMPARATORI_H

#include "domain.h"
/**
 * @param obiect
 * @param orice_str
 * @param orice_int
 * @return true
 */
bool filtru_vid(const Produs& obiect, const std::string& orice_str, const int& orice_int);

/**
 *
 * @param obiect
 * @param orice_str
 * @param pret pretul dupa care se filtreaza
 * @return
 */
bool filtru_pret(const Produs& obiect, const std::string& orice_str, const int& pret);

/**
 *
 * @param obiect
 * @param nume
 * @param orice_int
 * @return
 */
bool filtru_nume(const Produs& obiect, const std::string& nume, const int& orice_int);

/**
 *
 * @param obiect
 * @param nume
 * @param orice_int
 * @return
 */
bool filtru_tip(const Produs& obiect, const std::string& nume, const int& orice_int);

/**
 *
 * @param obiect
 * @param producator
 * @param orice_int
 * @return
 */
bool filtru_producator(const Produs& obiect, const std::string& producator, const int& orice_int);

/**
 *
 * @param obiect1
 * @param obiect2
 * @return
 */
int cmp_nume_c(const Produs& obiect1, const Produs& obiect2);

/**
 *
 * @param obiect1
 * @param obiect2
 * @return
 */
int cmp_pret_c(const Produs& obiect1, const Produs& obiect2);

/**
 *
 * @param obiect1
 * @param obiect2
 * @return
 */
int cmp_nume_pret_c(const Produs& obiect1, const Produs& obiect2);

/**
 *
 * @param obiect1
 * @param obiect2
 * @return
 */
int cmp_nume_d(const Produs& obiect1, const Produs& obiect2);

/**
 *
 * @param obiect1
 * @param obiect2
 * @return
 */
int cmp_pret_d(const Produs& obiect1, const Produs& obiect2);

/**
 *
 * @param obiect1
 * @param obiect2
 * @return
 */
int cmp_nume_pret_d(const Produs& obiect1, const Produs& obiect2);

#endif //LAB6_7_COMPARATORI_H
