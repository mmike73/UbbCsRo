//
// Created by Mihai Moldovan on 14.06.2024.
//

#include <assert.h>
#include <iostream>
#include "test.h"
#include "valid.h"
#include "domain.h"
#include "repo.h"
#include "exception.h"
#include "service.h"

void Test::test_domain() {
    Tractor t(1,"UTB","harb",16);
    assert(t.get_id() == 1);
    assert(t.get_denumire() == "UTB");
    assert(t.get_tip() == "harb");
    assert(t.get_nr_roti() == 16);
    t.set_nr_roti(4);
    assert(t.get_nr_roti() == 4);
}

void Test::test_repo() {
    Repo r("test_file");
    vector<Tractor> init_file = r.get_all();

    Tractor t(4,"INTERNATIONAL","harb",16);
    assert(r.get_all().size() == 3);
    r.add(t);
    assert(r.get_all().size() == 4);

    std::ofstream fout("../test_file");
    for(auto &i: init_file) {
        fout << i.str();
        std::cout << i.str();
    }

    map<string ,int> occ = r.get_occurences();
    assert(occ.find(init_file[0].get_tip())->second == 2);
    assert(occ.find(init_file[1].get_tip())->second == 1);
}

void Test::test_service() {
    Repo r("test_file");
    Valid v;
    Service s(r,v);
    vector<Tractor> init_file = r.get_all();

    Tractor t(4,"INTERNATIONAL","harb",16);
    assert(s.get_all_tractoare().size() == 3);
    s.add_tractor(t);
    assert(s.get_all_tractoare().size() == 4);
    s.modifica_nr_roti(1,12);
    vector<Tractor> verif = r.get_all();
    assert(verif[0].get_nr_roti() == 12);

    std::ofstream fout("../test_file");
    for(auto &i: init_file) {
        fout << i.str();
        std::cout << i.str();
    }
}

void Test::test_valid() {
    Tractor t(1,"UTB","harb",16);
    Valid v;
    v.valideaza_tractor(t);
    Tractor t_invalid(-1,"","",17);
    try {
        v.valideaza_tractor(t_invalid);
    } catch (Exception& e) {
        std::cout << e.what();
    }
}

void Test::run_all() {
    test_domain();
    test_repo();
    test_service();
    test_valid();
    std::cout << "Teste realizate cu succes!\n";
}
