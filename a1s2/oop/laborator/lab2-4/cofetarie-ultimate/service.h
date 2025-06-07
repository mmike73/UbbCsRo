//
// Created by Mihai Moldovan on 08.03.2024.
//

#ifndef COFETARIE_SERVICE_H
#define COFETARIE_SERVICE_H
#include "repo.h"
#include "domain.h"

int adauga_materie_prima( VectorDinamic *repo_cofetarie, char denumire_m_p[], char producator[], int cantitate);
void modifica_materie_prima( VectorDinamic *repo_cofetarie, char denumire_m_p[], char producator[], int cantitate);
int sterge_materie_prima( VectorDinamic*repo_cofetarie, char denumire_m_p[]);
int vizualizeaza_toate( VectorDinamic *repo_cofetarie, Element *toate_materiile_prime);
int vizualizeaza_materii_care_incep_cu_litera(VectorDinamic *repo_cofetarie, Element *toate_materiile_prime, char litera);
int vizualizeaza_materii_care_are_cantitatea_mai_mica_decat( VectorDinamic *repo_cofetarie, Element *toate_materiile_prime, int cantitate);
void ordoneaza_dupa(VectorDinamic *repo_cofetarie, Element *toate_materiile_prime, char cmp, char directie);

int get_lungime( VectorDinamic *repo_cofetarie);


#endif //COFETARIE_SERVICE_H
