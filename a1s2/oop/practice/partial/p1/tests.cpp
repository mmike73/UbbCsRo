//
// Created by Mihai Moldovan on 18.05.2024.
//

#include "tests.h"
#include "domain_placa.h"
#include "domain_procesor.h"
#include "service.h"
#include "repo.h"
#include <assert.h>
#include <string>
using std::string;

void Tests::test_domain() {
    PlacaDeBaza p{"Asus 1234","am4",250};
    assert(p.get_nume() == "Asus 1234");
    assert(p.get_socket() == "am4");
    assert(p.get_pret() == 250);
    p.set_nume("Gygabyte 4321");
    assert(p.get_nume() == "Gygabyte 4321");
    p.set_socket("1151");
    assert(p.get_socket() == "1151");
    p.set_pret(130);
    assert(p.get_pret() == 130);
}
void Tests::test_repo() {
    Repo<PlacaDeBaza> r;
    PlacaDeBaza p1{"Asus 1234","am4",250};
    PlacaDeBaza p2{"Gygabyte 4321","1151",130};
    r.add_item(p1);
    r.add_item(p2);
    assert(r.get_all().size() == 2);
    PlacaDeBaza found = r.search_item("Asus 1234");
    assert(found.get_nume() == "Asus 1234");
    assert(found.get_socket() == "am4");
    assert(found.get_pret() == 250);
    r.del_item("Asus 1234");
    assert(r.get_all().size() == 1);
}

void Tests::tese_service() {
    Repo<PlacaDeBaza> b;
    Repo<Procesor> p;
    Validator v;
    Service s{b,p,v};


}

void Tests::run_all() {
    test_domain();
    test_repo();
    tese_service();
}