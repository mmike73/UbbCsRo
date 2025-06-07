#include<string.h>
#include<stdlib.h>
#include "service.h"
#include "medicament.h"
#include "myList.h"

Farmacie createFarmacie()
{
    Farmacie listaMeds;
    listaMeds.lista = createList();
    listaMeds.lista_undo = createList();
    return listaMeds;
}

void destroyFarmacie(Farmacie* f)
{
    destroyList(f->lista);
    for( int i = 0; i < f->lista_undo->dimensiune; ++i)
        destroyList(f->lista_undo->medicamente[i]);
    free(f->lista_undo->medicamente);
    free(f->lista_undo);
}

/*Adauga  un medicament in lista.
 * Pre: list- de tip Farmacie*, id-int, nume - char*, concentratie-float
 * Post: 0 daca entitatea exista deja in lista, 1 altfel
 */
int addEnt(Farmacie* list, int id, char* nume, float concentratie, int stoc)
{
    Medicament* e = createMedicament(id, nume, concentratie, stoc);
    if(valideazaMedicament(e) == 1)
    {
        //
        add_undo_state(list);
        //
        addEntitate(list->lista,e);
        return 1;
    }
    else
    {
        destroyMedicament(e);
        return 0;
    }
}
/*Functie care sterge o entitate
 *Pre:list de tip Farmacie*, id de tip int
 * Post: 1 daca id-ul este in lista si a fost sters, 0 altfel
 */
int deleteEnt(Farmacie* list, int id)
{
    if(checkId(list,id))
    {
        //
        add_undo_state(list);
        //
        deleteEntitate(list->lista,id);
        return 1;
    }
    return 0;
}

/*Face update la un medicament.
 * Pre: list- de tip Farmacie*, id-int, nume - char*, concentratie-float
 * Post: 0 daca entitatea exista deja in lista si s-a facut modificarea, 1 altfel
 */
int updateEnt(Farmacie* list, int id, char* nume, float concentratie)
{
    for(int i=0;i<list->lista->dimensiune;i++)
    {
        if(getId(get(list->lista,i))==id)
        {
            int stoc = getStoc(get(list->lista,i));
            Entitate e = createMedicament(id,nume,concentratie,stoc);
            //
            add_undo_state(list);
            //
            updateMedicament(list->lista,e);
            return 0;
        }

    }
    return -1;
}

/*Cauta daca un id este in lista*/
int checkId(Farmacie* list, int id)
{
    if(cauta(list->lista,id) != -1)
        return 1;
    return 0;
}

/*Adauga un singur produs pe stoc*/
void addStoc(Farmacie* list, int id)
{
    int poz = cauta(list->lista,id);
    Medicament* m = get(list->lista,poz);
    //
    add_undo_state(list);
    //
    setStoc(m,m->stoc+1);

}

/*Dealoca tot*/
void destroyAll(Farmacie* list)
{
    destroyFarmacie(list);
}


/*Functie care sorteaza medicamentele crescator dupa stocul lor. Returneaza o farmacie cu medicamentele ordonate*/
List* sortareStoc(Farmacie* list)
{
    List* f = copyFarmacie(list->lista);
    for(int i=0; i<f->dimensiune-1;i++)
        for(int j=i+1; j<f->dimensiune;j++)
            if(getStoc(f->medicamente[i])> getStoc(f->medicamente[j]))
            {
                Medicament* m1 = get(f,i);
                Medicament* m2 = get(f,j);
                set(f,i,m2);
                set(f,j,m1);
            }

    return f;
}

/*Functie care sorteaza medicamentele alfabetic. Returneaza o farmacie cu medicamentele in ordine alfabetica.*/
List* sortareNume(Farmacie* list)
{
    List* f = copyFarmacie(list->lista);
    for(int i=0;i<f->dimensiune-1;i++)
        for(int j=i+1;j<f->dimensiune;j++)
            if(strcmp(getNume(f->medicamente[i]),getNume(f->medicamente[j]))>0)
            {
                Medicament* m1 = get(f,i);
                Medicament* m2 = get(f,j);
                set(f,i,m2);
                set(f,j,m1);
            }
    return f;
}

//
//pune ca si criteroiu filtrarea in fumctie de prima litara din nume
int criteriu_nume( void* medicament, void* filtru) {
    char* denumire = (char*) getNume(medicament);
    if(denumire[0] == *((char*)(filtru))) return 0;
    return 1;
}

//pune ca si criteroiu filtrarea in fumctie de stocul de medicamente
int criteriu_stoc( void* medicament, void* filtru) {
    int valoare = getStoc(medicament);
    if(valoare >= *(int*)filtru) return 1;
    return 0;
}


//filtreaza lista de medicamente in functie de criteriul de filtrare
List* filter_generic(Farmacie* list, int(*criteriu_filtrare)(void*, void*), void* filtru) {
    List* f = copyFarmacie(list->lista);

    for(int i=0; i<f->dimensiune;i++)
    {
        Medicament* m = get(f,i);
        if( criteriu_filtrare(m, filtru))
            deleteEntitate(f,m->id), i--;
    }

    return f;
}

//

/*Functie care filtreaza farmacia. Returneaza o farmacie doar cu medicamentele care au stocul mai mic decat o valoare data*/
List* filterStoc(Farmacie* list, int val)
{
    List* f = copyFarmacie(list->lista);

    for(int i=0; i<f->dimensiune;i++)
    {
        Medicament* m = get(f,i);
        if(m->stoc>=val)
            deleteEntitate(f,m->id), i--;
    }

    return f;
}

/*Functie care filtreaza farmacia. Returneaza o farmacie doar cu medicamentele care incep cu litera data*/
List* filterNume(Farmacie* list, char litera)
{
    List* f = copyFarmacie(list->lista);

    for(int i=0; i<f->dimensiune;i++)
    {
        Medicament* m = get(f,i);
        if(m->nume[0] != litera)
            deleteEntitate(f,m->id), i--;
    }

    return f;
}

/**
 * Functia adauga la lista de undo starea curenta a listei de medicamente
 * @param list - lista de medicamente
 * @param undo_list - lista lista cu starile dinainte de o modificare
 */
void add_undo_state(Farmacie* list) {
    List* copy_farmacie = copyFarmacie(list->lista);
    addEntitate(list->lista_undo, copy_farmacie);
}

/**
 * Functia restaureaza datele dinainte de ultima modificare
 * @param list
 */
void restore_previous(Farmacie* list) {
    destroyList(list->lista);
    list->lista = copyFarmacie(list->lista_undo->medicamente[list->lista_undo->dimensiune - 1]);
    list->lista_undo->dimensiune--;
}
