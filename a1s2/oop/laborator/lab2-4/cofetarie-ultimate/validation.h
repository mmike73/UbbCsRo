//
// Created by Mihai Moldovan on 09.03.2024.
//

#ifndef COFETARIE_VALIDATION_H
#define COFETARIE_VALIDATION_H
#include "domain.h"


int valideaza_materie_prima( char denumire_m_p[], char producator[], int cantitate);
int valideaza_denumire_materie_prima( char materie_prima[]);
int valideaza_producator( char producator[]);
int valideaza_cantitate( int cantitate);

#endif //COFETARIE_VALIDATION_H

//
