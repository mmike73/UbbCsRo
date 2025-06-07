/*
#ifndef OOP_LAB2_4_UI_H
#define OOP_LAB2_4_UI_H

#endif //OOP_LAB2_4_UI_H
*/
#pragma once
#include "service.h"
#include "myList.h"
#include "medicament.h"

/*Citeste atributele unui medicament si il adauga in farmacie.*/
void readMed(Farmacie* list);

/*Afiseaza toata farmacia*/
void printFarmacie(Farmacie* list);

/*sterge un medicament*/
void deleteMed(Farmacie* list);

/*Modifica un medicament */
void updateMed(Farmacie* list);

/*Afiseaza medicamentele sortate alfabetic*/
void sortNumeCresc(Farmacie* list);

/*Afiseaza medicamentele sortate invers alfabetic*/
void sortNumeDesc(Farmacie* list);

/*Afiseaza medicamentele sortate crescator dupa stoc*/
void sortStocCresc(Farmacie* list);

/*Afiseaza medicamentele sortate descrescator dupa stoc*/
void sortStocDesc(Farmacie* list);



int criteriu_nume( void* medicament, void* filtru);

int criteriu_stoc( void* medicament, void* filtru);

List* filter_generic(Farmacie* list, int(*criteriu_filtrare)(void*, void*), void* filtru);




/*Afiseaza medicamentele dupa filtrare dupa stoc*/
void filtrareStoc(Farmacie* list);

/*Afiseaza medicamentele dupa filtrare dupa nume*/
void filtrareNume(Farmacie* list);

/**
 * restaureaza starea dinaintea modificarii listei
 * @param list
 * @param undo_list
 */
void  undo(Farmacie* list);


void run();