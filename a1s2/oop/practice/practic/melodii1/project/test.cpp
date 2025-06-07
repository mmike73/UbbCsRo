//
// Created by Mihai Moldovan on 18.06.2024.
//

#include "test.h"

void Test::test_domain() {
    Melodie m{1,"Bumba","Zumba",1};
    assert(m.get_id() == 1);
    assert(m.get_artist() == "Zumba");
    assert(m.get_rank() == 1);
    assert(m.get_titlu() == "Bumba");
    m.set_artist("BUMBA");
    assert(m.get_artist() == "BUMBA");
    m.set_titlu("ZUMBA");
    assert(m.get_titlu() == "ZUMBA");
    m.set_rank(10);
    assert(m.get_rank() == 10);
}
void Test::test_repo() {
    Repo r("/Volumes/D/Faculta/A1S2/OOP/practice/practic/melodii1/project/test_file");
    vector<Melodie> tmp = r.get_all_melodii();
    assert(tmp.size() == 5);
    r.sterge_melodie(5);
    assert(r.get_all_melodii().size() == 4);
    r.adauga_melodie(tmp[4]);
    assert(r.get_all_melodii().size() == 5);

    Melodie mod = r.cauta_melodie(2);
    mod.set_rank(8);
    r.modifica_melodie(2,mod);
    //assert(r.cauta_melodie(2).get_rank() == 8);
    mod.set_rank(10);
    r.modifica_melodie(2,mod);
}

void Test::test_service() {

}

void Test::test_all() {
    test_domain();
    test_service();
    test_repo();
}
