//#ifndef OOP_LAB2_4_MEDICAMENT_H
//#define OOP_LAB2_4_MEDICAMENT_H

#pragma once

typedef struct{
    int id;
    char *nume;
    float concentratie;
    int stoc;
}Medicament;

/*Primeste caracteristicile unui medicament, creeaza entitatea Medicament si returneaza un pointer la entitatea Medicament*/
Medicament* createMedicament(int, char*,float,int);

/*Primeste o entitate Medicament si il sterge din memorie.*/
void destroyMedicament(Medicament*);

/*Primeste o entitate Medicament si ii returneaza numele.*/
char* getNume(Medicament*);

/*Primeste o entitate Medicament si ii returneaza id-ul.*/
int getId(Medicament*);

/*Primeste o entitate Medicament si ii returneaza concentratia.*/
//float getConcentratie(Medicament*);

/*Primeste o entitate Medicament si ii returneaza stocul.*/
int getStoc(Medicament*);

/*Incrementeaza stocul unui medicament dat.*/
void setStoc(Medicament*,int);

/*Valideaza un medicament dat*/
int valideazaMedicament(Medicament*);

Medicament* copyMedicament(Medicament*);


//#endif //OOP_LAB2_4_MEDICAMENT_H