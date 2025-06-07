//
// Created by Mihai Moldovan on 08.03.2024.
//
#include <stdio.h>
#include <string.h>
#include "validation.h"

/**
 * valideaza o materie prima
 * @param mp - o materie prima
 * @return 1 - daca e valida
 *         0 - daca nu e valida
 */

/**
 * valideaza o materie prima
 * @param denumire_m_p char - max 30 de caractere - denumirea unei materii prime
 * @param producator char - max 30 de caractere - denumirea producatorului materiei prrime
 * @param cantitate int - cantitatea de materie rpima in kg
 * @return 1 - daca e valida
 *         -1 - daca nu e valida
 */
int valideaza_materie_prima(char denumire_m_p[], char producator[], int cantitate) {
    int errors = 0;
    if(strlen(denumire_m_p) > 30) {
        fprintf(stderr, "Denumirea trebuie sa fie de maxim 30 de caractere!!!\n");
        errors++;
    }
    if(strlen(producator) > 30) {
        fprintf(stderr, "Producatorul trebuie sa fie de maxim 30 de caractere!!!\n");
        errors++;
    }
    if(cantitate < 1) {
        fprintf(stderr, "Cantitatea trebuie sa fie strict pozitiva!!!\n");
        errors++;
    }
    if(errors != 0) return -1;
    return 1;
}

/**
 * valideaza denumirea unei materi prie
 * @param materie_prima char - maxim 30 de caractere
 * @return 1 - valida
 *         -1 - nu e valida are mai mult de 30 de caractere
 */
int valideaza_denumire_materie_prima( char materie_prima[]) {
    int errors = 0;
    if(strlen(materie_prima) > 30) {
        fprintf(stderr, "Denumirea trebuie sa fie de maxim 30 de caractere!!!\n");
        errors++;
    }
    if(errors != 0) return -1;
    return 1;
}

/**
 * valideaza producatorul unei materii prime
 * @param producator char string - max 30 de caractere
 * @return 1 - valida
 *         -1 - nu e valida - are mai mult de 30 de caractere
 */
int valideaza_producator( char producator[]) {
    int errors = 0;
    if(strlen(producator) > 30) {
        fprintf(stderr, "Producatorul trebuie sa fie de maxim 30 de caractere!!!\n");
        errors++;
    }
    if( errors != 0) return -1;
    return 1;
}

/**
 * valideaza cantitatea u
 * @param cantitate
 * @return 1 - valida >= 0
 *         -1 - nu e valida cantitatea e negativa
 */
int valideaza_cantitate( int cantitate) {
    int errors = 0;
    if(cantitate < 1) {
        fprintf(stderr, "Cantitatea trebuie sa fie strict pozitiva!!!\n");
        errors++;
    }
    if( errors != 0) return -1;
    return 1;
}


