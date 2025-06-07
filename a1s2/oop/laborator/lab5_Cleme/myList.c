#include "myList.h"
#include <stdlib.h>
#include <stdio.h>

/*Adauga un produs nou in farmacie.*/
void addEntitate(List* f, Entitate e)
{
    if (f->dimensiune < f->capacitate)
    {
        f->medicamente[f->dimensiune] = e;
        f->dimensiune += 1;
    }
    else
    {
        asiguraCapacitate(f);
        addEntitate(f, e);
    }

}

/*Functie care mareste capacitatea farmaciei.*/
void asiguraCapacitate(List* f)
{

    Entitate* capacitateNoua = malloc(sizeof(Entitate)*(f->capacitate * 2));
    //copiaza elementele
    for (int i = 0; i < f->dimensiune; i++)
        capacitateNoua[i] = f->medicamente[i];

    //dealoca memoria
    free(f->medicamente);
    f->medicamente = capacitateNoua;
    f->capacitate *= 2;

}

/*Sterge o un produs din farmacie.*/
int deleteEntitate(List* f, int id)
{
    int i = 0;
    int ok = 1;
    while(i<f->dimensiune)
    {
        Medicament* p = get(f, i);
        if (p->id == id)
        {
                destroyMedicament(p);
                for (int j = i; j < f->dimensiune - 1; j++)
                    f->medicamente[j] = f->medicamente[j + 1];
                f->dimensiune -= 1;
                ok = 0;
        }

        i++;
    }

    return ok;
}


/*Functie care creeaza o entitate List noua si returneaza pointerul la entitatea respectiva.*/
List* createList()
{

    List* f = malloc(sizeof(List));
    f->dimensiune = 0;
    f->capacitate = 2;
    f->medicamente = malloc(sizeof(Entitate) * f->capacitate);

    return f;
}

/*Primeste un pointer la entitatea List si dealoca memoria ocupata de entitate.*/
void destroyList(List* f)
{
    for (int i = 0; i < f->dimensiune; i++)
        destroyMedicament(f->medicamente[i]);

    free(f->medicamente);
    free(f);

}
/*Functie care face update la un medicament.
 Primeste un pointer la medicamentul cu caracteristicile actualizate, distruge medicamentul
 vechi si il pune pe cel actualizat.
*/
int updateMedicament(List* f, Medicament* m)
{
    int ok = -1;
    for (int i=0; i < f->dimensiune; i++)
    {
        Medicament* p = get(f, i);
        if (p->id == m->id)
        {
            //distrug medicamentul returnat de set
            destroyMedicament(set(f,i,m));
            ok = 0;
        }
    }
    return ok;
}
/*Functie care primeste un int -id- si returneaza pozitia pe care se afla elementul sau -1 in caz contrar*/
int cauta(List* f, int id)
{

    for (int i = 0; i < f->dimensiune; i++)
    {
        Medicament* p = get(f, i);
        if (p->id == id)
            return i;

    }
    return -1;
}


/*Functie care returneaza elementul de pe o pozitie data*/
Entitate get(List* f, int i)
{
    return f->medicamente[i];
}

/*Functie care pune pe o pozitie data o entitate data si returneaza fostul element de pe pozitia data.*/
Entitate set(List* f, int poz, Entitate e)
{

    Entitate rez = f->medicamente[poz];
    f->medicamente[poz] = e;
    return rez;
}

List* copyFarmacie(List* p)
{
    List* f = malloc(sizeof(List));
    f->dimensiune = p->dimensiune;
    f->capacitate = p->capacitate;
    f->medicamente = malloc(sizeof (Medicament)*p->dimensiune);
    for(int i=0; i< p->dimensiune;i++)
        f->medicamente[i] = copyMedicament(p->medicamente[i]);

    return f;
}