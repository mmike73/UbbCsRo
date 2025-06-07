//
// Created by Mihai Moldovan on 08.03.2024.
//
#include <stdio.h>
#include "domain.h"
#include <string.h>
#include <stdlib.h>

/**
 * creeaza o structura de date de tip MateriePrima
 * @param denumire char string - max 30 de caractere - denumirea materiei prime
 * @param producator char string - max 30 de caractere - denumirea producatorului
 * @param cantitate int - cantitatea de materie prima in kg
 * @return
 */
struct MateriePrima *creeaza_materie_prima( char denumire[], char producator[], int cantitate) {
    struct MateriePrima *m_p = (struct MateriePrima *)malloc(sizeof(struct MateriePrima));
    m_p->denumire = (char *)malloc((strlen(denumire) + 1) * sizeof(char));
    strcpy( m_p->denumire, denumire);
    m_p->producator = (char *)malloc((strlen(producator) + 1) * sizeof(char));
    strcpy( m_p->producator, producator);
    m_p->cantitate = cantitate;
    return m_p;
}

/**
 * distruget structura de date de tip MateriePrima
 * @param m_p MateriePrima - o materie prima
 */
void disctruge_materie_prima( struct MateriePrima* m_p) {
    free(m_p->denumire);
    free(m_p->producator);
    free(m_p);
}

/**
 * returneaza denumirea structurii de date de tip MateriePrima prin parametrul denumire
 * @param mp MateriePrima - o materie prima
 * @param denumire char* - un pointer catre locatia unde sa returneze denumirea materiei prime
 *                       - parametru de iesire
 */
void get_denumire(struct MateriePrima* mp, char *denumire) {
    strcpy(denumire, mp->denumire);
}

/**
 * returneaza producatorul structurii de date de tip MateriePrima prin parametrul producator
 * @param mp MateriePrima - o materie prima
 * @param producator char* - un pointer catre locatia unde sa returneze producatorul materiei prime
 *                       - parametru de iesire
 */
void get_producator(struct MateriePrima* mp, char *producator) {
    strcpy(producator, mp->producator);
}

/**
 * returneaza canitatea de materie prima di cadrul structurii de date de tip MateriePrima prin parametrul cantitate
 * @param mp MateriePrima - o materie prima
 * @param denumire int* - un pointer catre locatia unde sa returneze cantitatea materiei prime
 *                       - parametru de iesire
 */
void get_cantitate(struct MateriePrima* mp, int *cantitate) {
    *cantitate = mp->cantitate;
}

/**
 * seteaza valoarea campului producaroe a unri structuri de tip MateriePrima
 * @param mp MateriePrima
 * @param producator_nou char string max 30 de caractere - stringul cu care se modifica producatorul
 */
void set_producator( struct MateriePrima* mp, char* producator_nou) {
    free(mp->producator);
    mp->producator = NULL;
    mp->producator = (char *)malloc((strlen(producator_nou) + 1) * sizeof(char));
    strcpy(mp->producator, producator_nou);
}

/**
 * seteaza valoarea campului cantitate a unri structuri de tip MateriePrima
 * @param mp MateriePrima
 * @param cantitate_noua int - valoarea cu care se modifica cantitatea
 */
void set_cantitate( struct  MateriePrima* mp, int cantitate_noua) {
    mp->cantitate = cantitate_noua;
}
