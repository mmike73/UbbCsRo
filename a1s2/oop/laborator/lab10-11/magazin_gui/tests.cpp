//
// Created by Mihai Moldovan on 29.03.2024.
//

#include "tests.h"
#include "domain.h"
#include "validation.h"
#include "repo.h"
#include "service.h"
#include "cos_cumparaturi.h"
#include <iostream>
#include <assert.h>
#include <vector>
#include "exception.h"

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
    Produs obj_bad_1{-1,"a","a",7,"a"};
    try {
        v.valideaza_produs(obj_bad_1);
    } catch (Exception& e) {
        assert(true);
    }
    Produs obj_bad_2{-1,"","",-7,""};
    try {
        v.valideaza_produs(obj_bad_2);
    } catch (Exception& e) {
        assert(true);
    }
    Produs obj_bad_3{-1,"aa","aa",7,""};
    try {
        v.valideaza_produs(obj_bad_3);
    } catch (Exception& e) {
        assert(true);
    }
    Produs obj_bad_4{-1,"aa","",7,"aa"};
    try {
        v.valideaza_produs(obj_bad_4);
    } catch (Exception& e) {
        assert(true);
    }
    std::string mare = "abcdefghijklmnopqrstuvwxyzabcdefghijk";
    Produs obj_bad_5{1,mare, "a", 7, "b"};
    try {
        v.valideaza_produs(obj_bad_5);
    } catch (Exception& e) {
        assert(true);
    }
    Produs obj_bad_6{1,"a", mare, 7, "b"};
    try {
        v.valideaza_produs(obj_bad_6);
    } catch (Exception& e) {
        assert(true);
    }
    Produs obj_bad_7{1,"a", "a", 7, mare};
    try {
        v.valideaza_produs(obj_bad_7);
    } catch (Exception& e) {
        assert(true);
    }
}

void Tests::test_service() {
    std::ofstream fout("/Volumes/D/Faculta/A1S2/OOP/labs/lab8-9/magazin/test_f");
    fout << "";
    fout.close();

    ProduseRepoFile rp{"/Volumes/D/Faculta/A1S2/OOP/labs/lab8-9/magazin/test_f"};
    Validation vl;
    CosCumparaturi cos{rp};

    try {
        rp.sterge_produs_dupa_id_repo(1);
    } catch (Exception& e) {
        assert(true);
    }

    ServiceProduse sv{rp,vl,cos};

    sv.adauga_produs_service(1,"lapte","aliment",7,"Monor");
    Produs returned = sv.cauta_produs_service(1);

    assert(returned.get_id() == 1);
    assert(returned.get_nume() == "lapte");
    assert(returned.get_tip() == "aliment");
    assert(returned.get_pret() == 7);
    assert(returned.get_producator() == "Monor");

    returned = sv.cauta_produs_service(2);
    assert(returned.get_id() == -1);

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

    try {
        sv.modifica_produs_service(4, "d", "", 0);
    } catch (const Exception& e) {
        assert(true);
    }

    sv.adauga_produs_service(2,"z", "a", 1, "a");
    sv.adauga_produs_service(3,"g", "a", 1, "a");
    sv.adauga_produs_service(4,"a", "a", 1, "a");
    sv.adauga_produs_service(5,"j", "a", 1, "a");
    sv.adauga_produs_service(6,"k", "a", 1, "a");
    sv.adauga_produs_service(7,"a", "a", 1, "a");
    sv.adauga_produs_service(8,"t", "a", 1, "a");
    sv.adauga_produs_service(9,"w", "a", 1, "a");
    sv.adauga_produs_service(10,"b", "a", 1, "a");
/////////////////////
    std::vector<Produs> soortat;
    soortat = sv.sorteaza_produse([=](const Produs& p1, const Produs& p2) {
        if( p1.get_nume() > p2.get_nume()) return -1;
        if( p1.get_nume() < p2.get_nume()) return 1;
        return 0;
    });

//???????
    try {
        sv.adauga_produs_service(10,"b", "a", 1, "a");
    } catch(const Exception& e) {
        assert(true);
    }
    std::vector<Produs> result = sv.filtreaza_produse([=](const Produs &p) {
        return true;
    });
    assert(result.size() == 10);
    sv.sterge_produs_service(7);

    try {
        sv.sterge_produs_service(7);
    } catch(const Exception& e) {
        assert(true);
    }

    try {
        sv.sterge_produs_service(11);
    } catch(const Exception& e) {
        assert(true);
    }


}

void Tests::test_cos_bad() {
    ProduseRepoFile rp{"/Volumes/D/Faculta/A1S2/OOP/labs/lab8-9/magazin/test_f"};
    Validation vl;
    CosCumparaturi cos{rp};
    ServiceProduse sv{rp,vl,cos};

    try {
        sv.undo();
    } catch (Exception& e) {
        assert (true);
    }

    sv.adauga_produs_service(1,"ga", "ab", 1, "a");
    sv.adauga_produs_service(2,"z", "ab", 1, "a");
    sv.adauga_produs_service(3,"g", "abc", 1, "a");
    sv.adauga_produs_service(4,"a", "abc", 1, "a");
    sv.adauga_produs_service(5,"j", "abc", 1, "a");
    sv.adauga_produs_service(6,"k", "abcd", 1, "a");
    sv.adauga_produs_service(7,"a", "abcd", 1, "a");
    sv.adauga_produs_service(8,"t", "abcd", 1, "a");
    sv.adauga_produs_service(9,"w", "abcd", 1, "a");
    sv.adauga_produs_service(10,"b", "abcde", 1, "a");
    sv.adauga_produs_service(11,"b", "abcde", 1, "a");
    sv.adauga_produs_service(12,"b", "abcde", 1, "a");

    sv.sterge_produs_service(11);
    assert(sv.cauta_produs_service(11).get_id() == -1);
    sv.undo();
    assert(sv.cauta_produs_service(11).get_id() == 11);



    sv.adauga_inc_cos(1);
    sv.adauga_inc_cos(2);
    sv.adauga_inc_cos(3);
    sv.adauga_inc_cos(4);
    sv.adauga_inc_cos(5);
    sv.adauga_inc_cos(6);
    sv.adauga_inc_cos(7);
    sv.adauga_inc_cos(8);
    sv.adauga_inc_cos(9);
    sv.adauga_inc_cos(10);

    sv.exporta_cos_s("../exports/test_exports");

    sv.adauga_inc_cos(11);

    try {
        sv.adauga_inc_cos(30);
        assert(false);
    }  catch( Exception& e) {
        assert(true);
    }

    try {
        sv.sterge_din_cos(30);
        assert(false);
    }  catch( Exception& e) {
        assert(true);
    }

    sv.sterge_din_cos(11);
    std::vector<int> v = sv.get_all_cos();
    assert(v[v.size() - 1] != 11);


    sv.goleste_cos();
    assert(sv.get_all_cos().size() == 0);

    sv.exporta_cos_s("../exports/test_export");

    sv.adauga_inc_cos(1);
    sv.adauga_inc_cos(2);
    sv.adauga_inc_cos(3);
    sv.adauga_inc_cos(4);
    sv.adauga_inc_cos(5);
    sv.adauga_inc_cos(6);
    sv.adauga_inc_cos(7);
    sv.adauga_inc_cos(8);
    sv.adauga_inc_cos(9);
    sv.adauga_inc_cos(10);

    int a[] = {2,3,4,2};
    std::multimap<std::string,int>& cat = sv.get_catalog();
    std::string prev_key = "";
    int cnt = 0, ind = 0;
    for( auto& i: cat) {
        if(i.first != prev_key) {
            if( prev_key != "") {
                assert(cnt == a[ind++]);
            }
            prev_key = i.first;
            cnt = 1;
        }
        else cnt++;
    }
}

void Tests::test_cos() {

    std::ofstream fout("/Volumes/D/Faculta/A1S2/OOP/labs/lab8-9/magazin/test_f");
    fout << "";
    fout.close();

    ProduseRepoFile rp{"/Volumes/D/Faculta/A1S2/OOP/labs/lab8-9/magazin/test_f"};
    Validation vl;
    CosCumparaturi cos{rp};
    ServiceProduse sv{rp,vl,cos};

    try {
        sv.undo();
    } catch (Exception& e) {
        assert (true);
    }

    sv.adauga_produs_service(1,"ga", "ab", 1, "a");
    sv.adauga_produs_service(2,"z", "ab", 1, "a");
    sv.adauga_produs_service(3,"g", "abc", 1, "a");
    sv.adauga_produs_service(4,"a", "abc", 1, "a");
    sv.adauga_produs_service(5,"j", "abc", 1, "a");
    sv.adauga_produs_service(6,"k", "abcd", 1, "a");
    sv.adauga_produs_service(7,"a", "abcd", 1, "a");
    sv.adauga_produs_service(8,"t", "abcd", 1, "a");
    sv.adauga_produs_service(9,"w", "abcd", 1, "a");
    sv.adauga_produs_service(10,"b", "abcde", 1, "a");
    sv.adauga_produs_service(11,"b", "abcde", 1, "a");
    sv.adauga_produs_service(12,"b", "abcde", 1, "a");

    sv.sterge_produs_service(11);
    assert(sv.cauta_produs_service(11).get_id() == -1);
    sv.undo();
    assert(sv.cauta_produs_service(11).get_id() == 11);

    sv.adauga_inc_cos(1);
    sv.adauga_inc_cos(2);
    sv.adauga_inc_cos(3);
    sv.adauga_inc_cos(4);
    sv.adauga_inc_cos(5);
    sv.adauga_inc_cos(6);
    sv.adauga_inc_cos(7);
    sv.adauga_inc_cos(8);
    sv.adauga_inc_cos(9);
    sv.adauga_inc_cos(10);

    assert(sv.get_total_cos() == 10);



    sv.goleste_cos();
    assert(sv.get_all_cos().size() == 0);
}

void Tests::run_all_tests() {
    this->test_domain();
    this->test_validation();
    this->test_service();
    this->test_cos();
    this->test_cos_bad();
    std::cout << "Teste realizate cu succes!\n";
}