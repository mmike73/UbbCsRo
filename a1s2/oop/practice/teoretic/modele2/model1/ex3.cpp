#include <algorithm>
#include <string>
#include <vector>
#include <memory>
#include <iostream>

using std::string;
using std::vector;
using std::sort;

class Mancare {
private:
    int pret;

public:
    Mancare() = default;
    Mancare(int pret);
    virtual ~Mancare() = default; // Ensure polymorphic destruction
    int getPret() const {
        return pret;
    }
    virtual string descriere() = 0;
};

Mancare::Mancare(int pret) : pret{pret} {}

class Burger : public Mancare {
private:
    string nume;

public:
    Burger(string nume, int pret);
    string getNume() const {
        return nume;
    }
    string descriere() override {
        return nume;
    }
};

Burger::Burger(string nume, int pret) : Mancare(pret), nume{nume} {}

class cuCartof : public Mancare {
private:
    std::unique_ptr<Mancare> m;

public:
    cuCartof(std::unique_ptr<Mancare> m);
    string descriere() override {
        return m->descriere() + " cu cartof";
    }
    int getPret() const {
        return m->getPret() + 3;
    }
};

cuCartof::cuCartof(std::unique_ptr<Mancare> m) : Mancare(m->getPret()), m{std::move(m)} {}

class cuSos : public Mancare {
private:
    std::unique_ptr<Mancare> m;

public:
    cuSos(std::unique_ptr<Mancare> m);
    string descriere() override {
        return m->descriere() + " cu sos";
    }
    int getPret() const {
        return m->getPret() + 2;
    }
};

cuSos::cuSos(std::unique_ptr<Mancare> m) : Mancare(m->getPret()), m{std::move(m)} {}

vector<std::unique_ptr<Mancare>> creaza_lista_mancare() {
    vector<std::unique_ptr<Mancare>> lista;
    auto bigMac = std::make_unique<Burger>("BigMac", 15);
    lista.push_back(std::make_unique<Burger>("BigMac", 15));
    lista.push_back(std::make_unique<cuCartof>(std::make_unique<cuSos>(std::move(bigMac))));
    auto zinger = std::make_unique<Burger>("Zinger", 25);
    lista.push_back(std::make_unique<cuCartof>(std::make_unique<Burger>("Zinger", 25)));
    lista.push_back(std::make_unique<cuSos>(std::make_unique<Burger>("Zinger", 25)));
    return lista;
}

int main() {
    vector<std::unique_ptr<Mancare>> rez = creaza_lista_mancare();
    std::sort(rez.begin(), rez.end(), [](const std::unique_ptr<Mancare>& m1, const std::unique_ptr<Mancare>& m2) {
        return m1->getPret() < m2->getPret();
    });

    for (const auto& m : rez) {
        std::cout << m->descriere() << " " << m->getPret() << std::endl;
    }

    return 0;
}
