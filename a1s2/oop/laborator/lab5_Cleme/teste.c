#include "teste.h"
#include "medicament.h"
#include "myList.h"
#include "service.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

void testValideazaMedicament()
{
    int idRau = -1;
    char* numeRau = "";
    float concentratieRea = -1.0;
    int stocRau = 0;
    Medicament* o = createMedicament(19,numeRau,9,10);
    assert(valideazaMedicament(o)==-1);

    Medicament* i = createMedicament(19,"ksdjn",-9,10);
    assert(valideazaMedicament(i)==-1);

    Medicament* d = createMedicament(19,"sdkhb",9,-10);
    assert(valideazaMedicament(d)==-1);


    Medicament *m = createMedicament(idRau,numeRau,concentratieRea,stocRau);
    assert(valideazaMedicament(m)==-1);

    int idBun = 19;
    char* numeBun = "nurofen";
    float concentratieBuna = 0.88;
    int stocBun = 7;
    Medicament *p = createMedicament(idBun,numeBun,concentratieBuna,stocBun);
    assert(valideazaMedicament(p)==1);

    destroyMedicament(m);
    destroyMedicament(p);
    destroyMedicament(o);
    destroyMedicament(i);
    destroyMedicament(d);

}

void testUpdate()
{
    Farmacie list = createFarmacie();
    List* f = list.lista;
    Medicament* m = createMedicament(19,"nurofen",3,10);
    setStoc(m,10);
    addEntitate(f,m);

    assert(updateEnt(&list,20,"newname",9)==-1);
    assert(updateEnt(&list,19,"newname",10)==0);

    destroyAll(&list);

}
void testCauta()
{
    Farmacie list = createFarmacie();
    List* f = list.lista;
    Medicament* m = createMedicament(19,"nurofen",3,10);
    addEntitate(f,m);
    assert(checkId(&list,19)==1);
    assert(checkId(&list,30)==0);

    destroyAll(&list);
}

void testAddEntitate()
{
    Farmacie list = createFarmacie();

    addEnt(&list,19,"nurofen",3,10);
    addEnt(&list,20,"paracetamol",4,10);
    addEnt(&list,10,"ceva",10,2);
    assert(list.lista->dimensiune==3);
    Medicament* p = get(list.lista,0);

    assert(19 == p->id);
    assert(10 == p->stoc);
    assert(3 == p->concentratie);

    assert(addEnt(&list,-12,"a",-1,0)==0);

    destroyAll(&list);

}

void testDeleteEntitate()
{
    Farmacie list = createFarmacie();
    List* f = list.lista;
    Medicament* m = createMedicament(19,"nurofen",3,10);
    Medicament* m1 = createMedicament(21,"ceva",8,10);
    Medicament* m3 = createMedicament(22,"ceva",8,10);
    Medicament* m4 = createMedicament(26,"ceva",8,10);
    Medicament* m5 = createMedicament(23,"ceva",8,10);
    addEntitate(f,m);
    addEntitate(f,m3);
    addEntitate(f,m1);
    addEntitate(f,m4);
    addEntitate(f,m5);
    assert(deleteEnt(&list,20)==0);
    assert(deleteEnt(&list,22)==1);
    destroyAll(&list);
}

void testAsiguraCapacitate()
{
    List* f = createList();
    Medicament* m = createMedicament(19,"nurofen",3,10);
    Medicament* m1 = createMedicament(20,"ceva",8,100);
    Medicament* m2 = createMedicament(21,"altceva",1,19);
    addEntitate(f,m);
    addEntitate(f,m1);
    assert(f->capacitate==2);
    addEntitate(f,m2);
    assert(f->capacitate==4);
    assert(f->dimensiune==3);
    destroyList(f);

}

void testAddStoc()
{
    Farmacie list = createFarmacie();

    addEnt(&list,19,"nurofen",9,10);
    addStoc(&list,19);
    Medicament* m = get(list.lista,0);
    assert(getStoc(m)==11);

    destroyAll(&list);

}

void testSortareStoc()
{
    Farmacie list = createFarmacie();

    addEnt(&list,19,"nurofen",3,10);
    addEnt(&list,21,"ceva",8,100);
    addEnt(&list,22,"ceva",8,1);
    addEnt(&list,26,"ceva",8,3);
    addEnt(&list,23,"ceva",8,9);

    List* f1 = sortareStoc(&list);

    assert(f1->dimensiune==5);

    for(int i=0; i<f1->dimensiune-1;i++)
    {
        Medicament* m1 = get(f1,i);
        Medicament* m2 = get(f1,i+1);
        assert(m1->stoc <= m2->stoc);

    }

    destroyList(f1);
    destroyAll(&list);
}

void testSortareNume()
{
    Farmacie list = createFarmacie();

    addEnt(&list,19,"nurofen",3,10);
    addEnt(&list,21,"ceva",8,100);
    addEnt(&list,22,"aaa",8,1);
    addEnt(&list,26,"cea",8,3);
    addEnt(&list,23,"eva",8,9);

    List* f1 = sortareNume(&list);

    assert(f1->dimensiune==5);

    for(int i=0; i<f1->dimensiune-1;i++)
    {
        Medicament* m1 = get(f1,i);
        Medicament* m2 = get(f1,i+1);
        assert((int)strcmp(m1->nume,m2->nume) < 0);

    }

    destroyList(f1);
    destroyAll(&list);
}

void testFilterStoc()
{
    Farmacie list = createFarmacie();

    addEnt(&list,19,"nurofen",3,10);
    addEnt(&list,21,"ceva",8,100);
    addEnt(&list,22,"aaa",8,1);
    addEnt(&list,26,"cea",8,3);
    addEnt(&list,23,"eva",8,9);

    List* f1 = filterStoc(&list, 10);

    assert(f1->dimensiune == 3);
    assert(getStoc(f1->medicamente[0]) == 1);
    assert(getStoc(f1->medicamente[1]) == 3);
    assert(getStoc(f1->medicamente[2]) == 9);

    destroyList(f1);
    destroyAll(&list);
}

void testFilterNume()
{
    Farmacie list = createFarmacie();

    addEnt(&list,19,"nurofen",3,10);
    addEnt(&list,21,"ceva",8,100);
    addEnt(&list,22,"aaa",8,1);
    addEnt(&list,26,"cea",8,3);
    addEnt(&list,23,"eva",8,9);

    List* f1 = filterNume(&list, 'c');

    assert(f1->dimensiune == 2);
    assert(getId(f1->medicamente[0]) == 21);
    assert(getId(f1->medicamente[1]) == 26);

    destroyList(f1);
    destroyAll(&list);
}
//
void test_undo() {
    Farmacie list = createFarmacie();

    addEnt(&list,19,"nurofen",3,10);
    addEnt(&list,20,"paracetamol",4,10);
    addEnt(&list,10,"ceva",10,2);
    assert(list.lista->dimensiune==3);
    restore_previous(&list);
    assert(list.lista->dimensiune==2);
    restore_previous(&list);
    assert(list.lista->dimensiune==1);
    assert(deleteEnt(&list,19)==1);
    assert(list.lista->dimensiune==0);
    addEnt(&list,19,"nurofen",3,10);
    char denumire[] = "xanax";
    updateEnt(&list,19,denumire,4);
    //assert(strcmp(getNume(get(&list,0)), "xanax") == 0);
    //assert(getStoc(get(&list,0)) == 4);
    printf("undo");
}
//
void runAllTests()
{
    testValideazaMedicament();
    testCauta();
    testAddEntitate();
    testDeleteEntitate();
    testUpdate();
    testAsiguraCapacitate();
    testAddStoc();
    testSortareNume();
    testSortareStoc();
    testFilterNume();
    testFilterStoc();
    test_undo();
}


