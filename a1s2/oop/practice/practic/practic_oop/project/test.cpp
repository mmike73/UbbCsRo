//
// Created by Mihai Moldovan on 22.06.2024.
//

#include "test.h"
#include "domain.h"
#include "repo.h"

void Test::test_domain() {
    Utilaj u{1,"UTB","tractor",4};
    assert(u.get_tip() == "tractor");
    assert(u.get_id() == 1);
    assert(u.get_cilindri() == 4);
    assert(u.get_denumire() == "UTB");
    assert(u.to_string() == "1,UTB,tractor,4\n");

    u.set_tip("combina");
    assert(u.get_tip() == "combina");
    u.set_denumire("new holland");
    assert(u.get_denumire() == "new holland");
    u.set_cilindri(6);
    assert(u.get_cilindri() == 6);
    assert(u.to_string() == "1,new holland,combina,6\n");
}

void Test::test_service() {

}
void Test::test_repo() {
    Repo r{"/Users/mihaimoldovan/Desktop/practic_oop/project/test_file"};
    vector<Utilaj> all = r.getAll();
    for(int i = 0; i < all.size(); ++i ) {
        assert( all[i].get_id() - 1 == i);
    }
    r.del(1);
    assert(r.getAll()[0].get_id() == 2);
    r.del(2);
    assert(r.getAll()[0].get_id() == 3);

    r.modifica(3,all[all.size() - 1]);
    assert(r.getAll().back().get_id() == 8);

    std::ofstream fout("/Users/mihaimoldovan/Desktop/practic_oop/project/test_file");
    for(auto& i:all) {
        fout << i.to_string();

        std::cout <<"all" <<  i.to_string();
    }
    fout.close();
}
void Test::run_all() {
    test_repo();
    test_service();
    test_domain();
    std::cout << "Teste finalizate cu succes!\n";
}