//
// Created by Mihai Moldovan on 21.06.2024.
//
#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

class Fruct {
public:
    //Fruct(const unique_ptr<Fruct>& other)
    virtual void tipareste() = 0;
    virtual bool eCuSamburi() {
        return false;
    }
};

class CuSamburi: public Fruct {
public:
    Fruct* f;

    CuSamburi(Fruct* f): f{f} {}

    virtual void tipareste() override {
        f->tipareste();
        cout << " cu samburi ";
    }

    virtual bool eCuSamburi() override {
        return true;
    }

    virtual ~CuSamburi() {
        delete f;
    }
};

class Pepene: public Fruct {
private:
    float kg;
public:
    Pepene(float kg): kg{kg} {}

    virtual void tipareste() override {
        //Fruct::tipareste();
        cout << "pepene ";
    }
};

class PepeneRosu: public Pepene {
public:
    PepeneRosu(float kg): Pepene(kg) {}
    virtual void tipareste() override {
        Pepene::tipareste();
        cout << "rosu ";
    }
};

class PepeneGalben: public Pepene {
public:
    PepeneGalben(float kg): Pepene(kg) {}
    virtual void tipareste() override {
        Pepene::tipareste();
        cout << "galben ";
    }
};

class Cos {
public:
    void add(Fruct* f) {
        if(f->eCuSamburi()) {
            cu_samburi.push_back(f);
        } else {
            fara_samburi.push_back(f);
        }
    }

    vector<Fruct*> get_all(bool samburi) {
        if(samburi) {
            return cu_samburi;
        } else {
            return fara_samburi;
        }
    }

    ~Cos() {
        for(auto& i:cu_samburi) delete i;
        for(auto& i:fara_samburi) delete i;
    }

private:
    vector<Fruct*> cu_samburi;
    vector<Fruct*> fara_samburi;
};

Cos* creeaza_cos() {
    Cos* cos = new Cos;
    Fruct* p_r_f = new PepeneRosu(5);

    Fruct* p_r = new PepeneRosu(10);
    Fruct* p_r_c = new CuSamburi(p_r);

    Fruct* p_g_f = new PepeneGalben(2);

    Fruct* p_g = new PepeneGalben(6);
    Fruct* p_g_c = new CuSamburi(p_g);

    cos->add(p_r_f);
    cos->add(p_r_c);
    cos->add(p_g_f);
    cos->add(p_g_c);

    return cos;
}

int main() {
    Cos* c  = creeaza_cos();
    vector<Fruct*> all_c = c->get_all(true);
    vector<Fruct*> all_f = c->get_all(false);

    for(auto& i:all_c) {
        i->tipareste();
        cout << '\n';
    }
    cout << '\n';
    for(auto& i:all_f) {
        i->tipareste();
        cout << '\n';
    }
    return 0;
}