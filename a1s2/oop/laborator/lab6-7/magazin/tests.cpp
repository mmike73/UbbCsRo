//
// Created by Mihai Moldovan on 29.03.2024.
//

#include "tests.h"
#include "domain.h"
#include "validation.h"
#include "repo.h"
#include "service.h"
#include "comparatori.h"
#include "exception.h"
#include <iostream>
#include <assert.h>
#include <vector>

void Tests::test_domain() {
    Produs obj{1,"lapte","aliment",7,"Monor"};
    assert(obj.get_id() == 1);
    assert(obj.get_nume() == "lapte");
    assert(obj.get_tip() == "aliment");
    assert(obj.get_pret() == 7);
    assert(obj.get_producator() == "Monor");

    Produs alt_obj{2,"da","da",4,"da"};
    alt_obj = obj;
    obj.set_nume("iaurt");

    assert(obj.get_nume() == "iaurt");
    obj.set_tip("lactat");
    assert(obj.get_tip() == "lactat");
    obj.set_pret(10);
    assert(obj.get_pret() == 10);
    obj.set_producator("Romfulda");
    assert(obj.get_producator() == "Romfulda");

    assert(alt_obj.get_id() == 1);
    assert(alt_obj.get_nume() == "lapte");
    assert(alt_obj.get_tip() == "aliment");
    assert(alt_obj.get_pret() == 7);
    assert(alt_obj.get_producator() == "Monor");
}

void Tests::test_validation() {
    Validation v;
    Produs obj{1,"lapte","aliment",7,"Monor"};
    assert(v.valideaza_produs(obj) == true);
    try {
        Produs obj_bad_1{-1, "a", "a", 7, "a"};
    } catch( const Exception& e) {
        assert(true);
    }
    try {
        Produs obj_bad_2{-1,"","",-7,""};
    } catch( const Exception& e) {
        assert(true);
    }
    try {
        Produs obj_bad_3{-1,"aa","aa",7,""};
    } catch( const Exception& e) {
        assert(true);
    }
    try {
        Produs obj_bad_4{-1,"aa","",7,"aa"};
    } catch( const Exception& e) {
        assert(true);
    }try {
        std::string mare = "abcdefghijklmnopqrstuvwxyzabcdefghijk";
        Produs obj_bad_5{1,mare, "a", 7, "b"};
    } catch( const Exception& e) {
        assert(true);
    }try {
        std::string mare = "abcdefghijklmnopqrstuvwxyzabcdefghijk";
        Produs obj_bad_7{1,"a", "a", 7, mare};
    } catch( const Exception& e) {
        assert(true);
    }
}

void Tests::test_service() {
    ProduseRepo rp;
    Validation vl;
    ServiceProduse sv{rp,vl};

    sv.adauga_produs_service(1,"lapte","aliment",7,"Monor");
    Produs returned = sv.cauta_produs_service(1);

    assert(returned.get_id() == 1);
    assert(returned.get_nume() == "lapte");
    assert(returned.get_tip() == "aliment");
    assert(returned.get_pret() == 7);
    assert(returned.get_producator() == "Monor");

    returned = sv.cauta_produs_service(2);

    assert(returned.get_id() == -1);

    sv.modifica_produs_service(1, "d", "iaurt", 0);
    sv.modifica_produs_service(1, "t", "lactat", 0);
    sv.modifica_produs_service(1, "c", "", 10);
    sv.modifica_produs_service(1, "p", "Romfulda", 0);

    returned = sv.cauta_produs_service(1);

    assert(returned.get_nume() == "iaurt");
    assert(returned.get_tip() == "lactat");
    assert(returned.get_pret() == 10);
    assert(returned.get_producator() == "Romfulda");

    sv.modifica_produs_service(4, "d", "", 0);


    //std::cout << "############################################ Vector ########################################\n";
    sv.adauga_produs_service(5,"z", "a", 1, "a");
    sv.adauga_produs_service(2,"g", "a", 1, "a");
    sv.adauga_produs_service(8,"s", "a", 1, "a");
    sv.adauga_produs_service(3,"j", "a", 1, "a");
    sv.adauga_produs_service(6,"k", "a", 1, "a");
    sv.adauga_produs_service(7,"a", "a", 1, "a");
    sv.adauga_produs_service(4,"t", "a", 1, "a");
    sv.adauga_produs_service(9,"w", "a", 1, "a");
    sv.adauga_produs_service(10,"b", "a", 1, "a");

    sv.adauga_produs_service(10,"b", "a", 1, "a");

    //std::cout << "############################################ Vector ########################################\n";

    //std::cout << "############################################ FILTREAZA ########################################\n";

    Vector<Produs> result = sv.filtreaza_produse(filtru_vid,"",0);

    //std::cout << "############################################ FILTREAZA ########################################\n";

    assert(result.size() == 10);

    //std::cout << "############################################ SORTEAZA ########################################\n";


    result = sv.sorteaza_produse(cmp_nume_c);


    //std::cout << "############################################ SORTEAZA ########################################\n";

    assert(result.size() == 10);

    sv.sterge_produs_service(7);

    //returned = sv.cauta_produs_service(7);

    //assert(returned.get_id() == -1);

    sv.sterge_produs_service(11);
}

void Tests::test_comparatori() {
    Produs obj1{1,"lapte","aliment",7,"Monor"};
    Produs obj2{2,"iaurt","lactat",10,"Romfulda"};

    assert(cmp_nume_c(obj1, obj2) == -1);
    assert(cmp_pret_c(obj1, obj2) == 1);
    assert(cmp_nume_pret_c(obj1,obj2) == -1);

    assert(cmp_nume_c(obj2, obj1) == 1);
    assert(cmp_pret_c(obj2, obj1) == -1);
    assert(cmp_nume_pret_c(obj2,obj1) == 1);

    assert(cmp_nume_c(obj1, obj1) == 0);
    assert(cmp_pret_c(obj1, obj1) == 0);
    assert(cmp_nume_pret_c(obj1,obj1) == 0);

    assert(cmp_nume_d(obj1, obj1) == 0);
    assert(cmp_pret_d(obj1, obj1) == 0);
    assert(cmp_nume_pret_d(obj1,obj1) == 0);

    assert(cmp_nume_d(obj1, obj2) == 1);
    assert(cmp_pret_d(obj1, obj2) == -1);
    assert(cmp_nume_pret_d(obj1,obj2) == 1);

    assert(filtru_nume(obj1, "lapte", 0) == true);
    assert(filtru_tip(obj1, "aliment", 0) == true);
    assert(filtru_pret(obj1, "", 7) == true);
    assert(filtru_producator(obj1, "Monor", 0) == true);

    assert(filtru_nume(obj1, "da", 0) == false);
    assert(filtru_tip(obj1, "da", 0) == false);
    assert(filtru_pret(obj1, "", 9) == false);
    assert(filtru_producator(obj1, "da", 0) == false);
}

void Tests::run_all_tests() {
    this->test_domain();
    this->test_validation();
    this->test_service();
    this->test_comparatori();
    std::cout << "Teste realizate cu succes!\n";
}