/*#ifndef OOP_LAB2_4_REPOSITORY_H
#define OOP_LAB2_4_REPOSITORY_H
#endif //OOP_LAB2_4_REPOSITORY_H
*/

#pragma once
#include "medicament.h"

/*Creeaza o entitate*/
typedef void* Entitate;


typedef struct {
    Entitate* medicamente ;
    int dimensiune;
    int capacitate;

} List;

/* Adauga o entitate in lista */
void addEntitate(List*, Entitate);

/* Sterge o entitate cu id-ul dat din lista */
int deleteEntitate(List*, int);

/*Dubleaza capacitatea vectorului*/
void asiguraCapacitate(List*);

/* Creeaza o lista Noua */
List* createList();

/* Sterge lista */
void destroyList(List*);

/* Modifica un medicament */
int updateMedicament(List*, Medicament*);

/* Returneaza entitatea de pe o pozitie data */
Entitate get(List*, int);

/* Pune pe o pozitie data Entitatea data.*/
Entitate set(List*, int, Entitate);

/*Cauta un medicament cu un id dat*/
int cauta(List*, int);

/*Creeaza o copie la farmacia data*/
List* copyFarmacie(List*);