//
// Created by Mihai Moldovan on 20.05.2024.
//

#include "teste.h"


void Teste::test_domain() {
    Apartament a{1,50,"Dorobanților",160000};
    assert(a.get_pret() == 160000);
    assert(a.get_id() == 1);
    assert(a.get_suprafata() == 50);
    assert(a.get_strada() == "Dorobanților");
    a.set_pret(190000);
    assert(a.get_pret() == 190000);
    a.set_strada("Nicolae Titulescu");
    assert(a.get_strada() == "Nicolae Titulescu");
    a.set_suprafata(70);
    assert(a.get_suprafata() == 70);
    a.text();
}
void Teste::test_repo() {

}
void Teste::test_service() {
    Apartament a{1,50,"Dorobanților",160000};
    Repo r("/Volumes/D/Faculta/A1S2/OOP/practice/partial/untitled/test_file");
    Service s(r);
    vector<Apartament> rez = s.get_all();
    assert(rez.size() == 5);
    s.sterge_apartament(2);
    assert(s.get_all().size() == 4);
    s.sterge_apartament(3);
    assert(s.get_all().size() == 3);
    s.sterge_apartament(3);
    assert(s.get_all().size() == 3);

    std::ofstream fout("/Volumes/D/Faculta/A1S2/OOP/practice/partial/untitled/test_file");
    for(auto& i:rez)
        fout << i.get_id() << ',' <<i.get_suprafata() <<',' << i.get_strada() <<','<<i.get_pret() << '\n';
    fout.close();

    Repo r2("/Volumes/D/Faculta/A1S2/OOP/practice/partial/untitled/test_file");
    Service s2(r2);
    rez = s2.filtreaza([](Apartament& a) {
        return a.get_pret() > 100000;
    });
    assert(rez.size() == 3);
}
void Teste::run_all() {
    test_domain();
    test_repo();
    test_service();
}
