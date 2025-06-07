//
// Created by Mihai Moldovan on 08.03.2024.
//
#include <stdio.h>
#include <string.h>
#include "service.h"
#include "repo.h"
#include "vector_dinamic.h"
#include <unistd.h>


void run( VectorDinamic *repo_materii_prime) {
    char comanda[11] = "";
    while(1) {
        printf(">>> ");
        scanf("%10s", comanda);
        if(strcmp(comanda, "exit") == 0) {
            distruge_repo(repo_materii_prime);
            return;
        }
        else if( strlen(comanda) != 0) {
            if(strcmp(comanda, "add") == 0) {
                printf("Introdu o materie prima (maxim 30 de caractere): ");
                char denumire_m_p[101] = "";
                scanf("%100s", denumire_m_p);
                printf("Introdu denumirea producatorului (maxim 30 de caractere): ");
                char producator[101] = "";
                scanf("%100s", producator);
                printf("Introdu cantitatea (kg): ");
                int cantitate;
                scanf("%d", &cantitate);
                int ok = adauga_materie_prima( repo_materii_prime, denumire_m_p, producator, cantitate);
                sleep(1);
                if( ok == -1) continue;
                printf("Materie prima adaugata cu succes!!!\n");
            }
            else if(strcmp(comanda, "mod") == 0) {
                char camp_modificare[101];
                printf("Introdu campul pe care vrei sa il modifici (producator / cantitate): ");
                scanf("%100s", camp_modificare);
                if( strcmp(camp_modificare, "producator") == 0) {
                    char materie_prima_mod[101], producator_nou[101];
                    printf("Introdu materia prima pe care vrei sa o modifici: ");
                    scanf("%s", materie_prima_mod);
                    printf("Introdu denumirea noului producator: ");
                    scanf("%100s", producator_nou);
                    modifica_materie_prima(repo_materii_prime, materie_prima_mod, producator_nou, -1);
                    printf("Modificare realizata cu succes!!!\n");
                }
                else if( strcmp(camp_modificare, "cantitate") == 0) {
                    char materie_prima_mod[101];
                    int stoc_nou;
                    printf("Introdu materia prima pe care vrei sa o modifici: ");
                    scanf("%s", materie_prima_mod);
                    printf("Introdu noul stoc: ");
                    scanf("%d", &stoc_nou);
                    modifica_materie_prima(repo_materii_prime, materie_prima_mod, "", stoc_nou);
                    printf("Modificare realizata cu succes!!!\n");
                }
                else {
                    fprintf(stderr, "Nu exista campul introdus!!!\n");
                }
            }
            else if(strcmp(comanda, "del") == 0) {
                printf("Introdu denumirea materiei prime de sters: ");
                char denumire_m_p[101] = "";
                scanf("%100s", denumire_m_p);
                int succes = sterge_materie_prima(repo_materii_prime, denumire_m_p);
                if(succes == 1) printf("Stergere realizata cu succes!!!\n");
            }
            else if(strcmp(comanda, "view") == 0) {
                int nr_materii_prime = get_lungime(repo_materii_prime);
                Element toate_m_p[nr_materii_prime];
                vizualizeaza_toate(repo_materii_prime, toate_m_p);
                for( int i = 0; i < nr_materii_prime; ++i)
                    printf("%s %s %d\n", ((struct MateriePrima *)(toate_m_p[i]))->denumire, ((struct MateriePrima *)(toate_m_p[i]))->producator, ((struct MateriePrima *)(toate_m_p[i]))->cantitate);
            }
            else if(strcmp(comanda, "sort") == 0) {
                char c[2] = "";
                printf("Campul dupa care se sorteaza (d - denumire / p - producator / q - cantitate): ");
                scanf("%s", c);
                char d[2] = "";
                printf("Directia dupa care se sorteaza (c - crescatoare / d - descrescatoare): ");
                scanf("%s", d);
                int cnt_mo = get_lungime(repo_materii_prime);
                Element sortate[cnt_mo];
                ordoneaza_dupa(repo_materii_prime, sortate, c[0], d[0]);
                for( int i = 0; i < cnt_mo; ++i)
                    printf("%s %s %d\n", ((struct MateriePrima *)(sortate[i]))->denumire, ((struct MateriePrima *)(sortate[i]))->producator, ((struct MateriePrima *)(sortate[i]))->cantitate);
            }
            else if(strcmp(comanda, "filter") == 0) {
                char criteriu[101] = "";
                printf("Introdu criteriul dupa care sa se faca filtrarea (caracter / cantitate): ");
                scanf("%100s", criteriu);
                //you have to get the number of filtered items
                if(strcmp(criteriu, "caracter") == 0) {
                    char c[2] = "";
                    printf("Introdu un caracter: ");
                    scanf("%s", c);
                    int cnt_mp = get_lungime(repo_materii_prime);
                    Element filtrate[cnt_mp];
                    int cnt_filtered = vizualizeaza_materii_care_incep_cu_litera(repo_materii_prime, filtrate, c[0]);
                    printf("%d\n", cnt_filtered);
                    if (cnt_filtered > 0) {
                        for (int i = 0; i < cnt_filtered; ++i)
                            printf("%s %s %d\n", ((struct MateriePrima *) (filtrate[i]))->denumire,
                                   ((struct MateriePrima *) (filtrate[i]))->producator,
                                   ((struct MateriePrima *) (filtrate[i]))->cantitate);
                    }
                }
                else if(strcmp(comanda, "cantitate")) {
                    int q;
                    printf("Introdu o cantitate maxima: ");
                    scanf("%d", &q);
                    int cnt_mp = get_lungime(repo_materii_prime);
                    Element filtrate[cnt_mp];
                    int cnt_filtered = vizualizeaza_materii_care_are_cantitatea_mai_mica_decat(repo_materii_prime, filtrate, q);
                    if (cnt_filtered > 0) {
                        for (int i = 0; i < cnt_filtered; ++i)
                            printf("%s %s %d\n", ((struct MateriePrima *) (filtrate[i]))->denumire,
                                   ((struct MateriePrima *) (filtrate[i]))->producator,
                                   ((struct MateriePrima *) (filtrate[i]))->cantitate);
                    }
                }

            }
            else if(strlen(comanda) != 0) {
                printf("Comanda invalida!!!\n");
            }
        }
    }
}