//
// Created by Mihai Moldovan on 08.03.2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "repo.h"

/**
 *
 * @param repo
 */
void distruge_repo_m_p( VectorDinamic *repo) {
    for( int i = 0; i < repo->dimensiune; ++i)
        disctruge_materie_prima(((MateriePrima *)(repo->elems[i])));
    distruge_repo(repo);
}

/**
 * cauta o materie prima cu denumirea transmisa prim parametru
 * @param repo_cofetarie RepoMP - structura de date in care se memoreaza materiile prime
 * @param denumire char string - max 30 de caractere - denumirea obiectului care se cauta
 * @return pozitia elementului in structura de date sau -1, daca elementul nu exista
 */
int exista_in_repo(VectorDinamic *repo_cofetarie, char *denumire) {
    for( int i = 0; i < repo_cofetarie->dimensiune; ++i) {
        if (strcmp( ((MateriePrima *)(repo_cofetarie->elems[i]))->denumire, denumire) == 0)
            return i;
    }
    return -1;
}

/**
 * adauga strctura de tip MateriePrima in structura de tip RepoMP
 * @param repo_cofetarie RepoMP - structura care retine materiile prime
 * @param materie_prima MateriePrima - o materie prima
 */
void adaugare_m_p( VectorDinamic *repo_cofetarie, Element el) {
    int pozitie = exista_in_repo(repo_cofetarie, ((MateriePrima *)(el))->denumire);
    if( pozitie >= 0) {
        ((MateriePrima *)(repo_cofetarie->elems[pozitie]))->cantitate += ((MateriePrima *)(el))->cantitate;
        disctruge_materie_prima(el);
    }
    else {
        adaugare_element(repo_cofetarie, el);
    }
}

/**
 * actualizeaza producatorul sau stocul unei materii prime
 * @param repo_cofetarie RepoMP - structura care emmoreaza materiile prime
 * @param denumire_m_p char string - max 30 de caractere - denumirea materiei prime
 * @param producator char string - max 30 de caractere - producatorul cu care se actualizeaza
 * @param stoc int - -1 atunic cand se doreste actualizarea producatorului
 *                   primeste valoare mai mare sau egala cu 0 atunci cand se doreste modificarea stocului materiei prime
 */
int actualizare_materie_prima( VectorDinamic *repo_cofetarie, char denumire_m_p[], char producator[], int stoc) {
    int ind = exista_in_repo(repo_cofetarie, denumire_m_p);
    if( ind == -1) {
        fprintf(stderr, "Materia prima introdusa nu exista!!!");
        return -1;
    }
    if( stoc == -1) {
        set_producator(repo_cofetarie->elems[ind], producator);
    }
    if(stoc >= 0) {
        set_cantitate(repo_cofetarie->elems[ind], stoc);
    }
    return 0;
}

/**
 * cauta o materie prima cu denumirea transmisa prim parametru
 * @param repo_cofetarie RepoMP - structura de date in care se memoreaza materiile prime
 * @param denumire char string - max 30 de caractere - denumirea obiectului care se cauta
 * @return pozitia elementului in structura de date sau -1, daca elementul nu exista
 */
int cautare_materie_prima_dupa_denumire( VectorDinamic *repo_cofetarie, char denumire[]) {
    for( int i = 0; i < repo_cofetarie->dimensiune; ++i)
        if( strcmp(((MateriePrima *)(repo_cofetarie->elems[i]))->denumire, denumire) == 0)
            return i;
    return -1;
}

/**
 * elimina un element din structura RepoMp
 * @param repo_cofetarie  RepoMP - structura care memoreaza toate materiile prime
 * @param denumire char string - denumirea materiei prime care se doreste eliminata
 * raises eerror - daca elementul nu exista in repo
 */
int stergere_m_p( VectorDinamic *repo_cofetarie, int poz) {
    disctruge_materie_prima(((MateriePrima *)(repo_cofetarie->elems[poz])));
    stergere_element(repo_cofetarie, poz);
    return 0;
}
