//
// Created by Mihai Moldovan on 08.03.2024.
//

#ifndef COFETARIE_REPO_H
#define COFETARIE_REPO_H
#include "domain.h"
#include <stdlib.h>
#include "vector_dinamic.h"

void distruge_repo_m_p( VectorDinamic *repo);
int exista_in_repo(VectorDinamic *repo_cofetarie, char *denumire);
void adaugare_m_p( VectorDinamic *repo_cofetarie, Element el);
int actualizare_materie_prima( VectorDinamic *repo_cofetarie, char denumire_m_p[], char producator[], int stoc);
int cautare_materie_prima_dupa_denumire( VectorDinamic *repo_cofetarie, char denumire[]);
int stergere_m_p( VectorDinamic *repo_cofetarie, int poz);




#endif //COFETARIE_REPO_H
