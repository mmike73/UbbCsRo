//
// Created by Mihai Moldovan on 08.03.2024.
//

#ifndef COFETARIE_DOMAIN_H
#define COFETARIE_DOMAIN_H

typedef struct MateriePrima {
    char* denumire;
    char* producator;
    int cantitate;
}MateriePrima;

struct MateriePrima *creeaza_materie_prima( char denumire[], char producator[], int cantitate);
void disctruge_materie_prima( struct MateriePrima* m_p);
void set_denumire( struct MateriePrima* mp, char denumire_noua[]);
void set_producator( struct MateriePrima* mp, char producator_nou[]);
void set_cantitate( struct  MateriePrima* mp, int cantitate_noua);
void get_denumire(struct MateriePrima* mp, char *denumire);
void get_producator(struct MateriePrima* mp, char *producator);
void get_cantitate(struct MateriePrima* mp, int *cantitate);



#endif //COFETARIE_DOMAIN_H
