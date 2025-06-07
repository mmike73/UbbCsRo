//
// Created by Mihai Moldovan on 22.06.2024.
//

#include "service.h"

Service::Service(Repo &r): r{r} {}

Utilaj Service::cauta_utilaj(int id) {
    try {
        return r.search(id);
    } catch(Exception& e) {
        throw Exception(e.what());
    }
}

Utilaj Service::mdoifica_denumire_utilaj(int id, string denumire) {
   try {
       Utilaj u = cauta_utilaj(id);
       u.set_denumire(denumire);
       r.modifica(id, u);
   } catch(Exception& e) {
        std::cout << e.what();
   }
   Utilaj i{-1,"","",-1};
   return i;
}

Utilaj Service::modifica_tip_utilaj(int id, string tip) {
    try {
        Utilaj u = cauta_utilaj(id);
        u.set_tip(tip);
        r.modifica(id, u);
    }catch (Exception& e) {
        std::cout << e.what();
    }
    Utilaj i{-1,"","",-1};
    return i;
}

Utilaj Service::modifica_numar_cilindri_utilaj(int id, int nr_cil) {
    Utilaj u = cauta_utilaj(id);
    u.set_cilindri(nr_cil);
    r.modifica(id, u);
}

void Service::sterge_utilaj(int id) {
    r.del(id);
}
vector<Utilaj> Service::get_all() {
    return r.getAll();
}
map<string, int> Service::get_tipuri() {
    return r.getTipuri();
}
map<int, int> Service::get_cilindri() {
    return r.getCilindri();
}