//
// Created by Mihai Moldovan on 21.06.2024.
//
#include <iostream>
#include <string>
#include <random>
using namespace std;

class Channel {
public:
    virtual void send(string msg) = 0;
};

class Telefon: public Channel {
private:
    int nr_tel;
public:
    Telefon(int nr_tel): nr_tel{nr_tel} {}
    virtual void send(string msg) override {
        int r = random() % 2;
        if(r == 0) {
            throw std::exception();
        }
        cout << "dial: " << nr_tel;
    }
};

class Fax: public Telefon {
public:
    Fax(int nr_tel): Telefon{nr_tel} {};
    void send(string msg) override {
        try {
            Telefon::send(msg);
        } catch(exception& e) {
            throw exception();
        }
        cout << "sending FAX";
    }
};

class SMS: public Telefon {
public:
    SMS(int nr_tel): Telefon{nr_tel} {};
    void send(string msg) override {
        try {
            Telefon::send(msg);
        } catch(exception& e) {
            throw exception();
        }
        cout << "sending SMS";
    }

};

class Failover: public Channel {
private:
    Channel *c1, *c2;
public:
    Failover(Channel* c1, Channel* c2): c1{c1}, c2{c2} {};
    void send(string msg) override {
        try {
            c1->send(msg);
        } catch (exception& e) {
            try {
                c2->send(msg);
            } catch(exception& e) {
                throw exception();
            }
        }
    }
    ~Failover() {
        delete c1;
        delete c2;
    }
};

class Contact {
public:
    Contact(Channel* c1, Channel* c2, Channel* c3):
        c1{c1}, c2{c2}, c3{c3} {};

    void sendAlarm(string msg) {
        bool sent = false;
        while(!sent) {
            try {
                c1->send(msg);
                sent = true;
            } catch (exception& e) {
                try {
                    Failover(c2, c3);
                    sent = true;
                } catch (exception& e) {
                    cout << e.what();
                }
            }
        }
    }

    ~Contact() {
        delete c1;
        delete c2;
        delete c3;
    }
private:
    Channel* c1;
    Channel* c2;
    Channel* c3;
};

Contact* creeaza_contact() {
    Telefon* t = new Telefon(1);

    Fax* f2 = new Fax{2};
    SMS* s2 = new SMS{3};
    Telefon* t2 = new Telefon{4};
    Failover* f22 = new Failover{s2, t2};
    Failover* f21 = new Failover{f2, f22};


    Fax* f3 = new Fax{5};
    SMS* s3 = new SMS{6};
    Telefon* t3 = new Telefon{7};
    Failover* f32 = new Failover{f3, s3};
    Failover* f31 = new Failover{t3, f32};

    Contact* c = new Contact{t,f21,f31};
    return c;
}

int main() {
    Contact* c = creeaza_contact();
    c->sendAlarm("Yeyeyeye");
    cout << '\n';
    c->sendAlarm("Dadadada");
    cout << '\n';
    c->sendAlarm("Qiqiqiqi");
    cout << '\n';
    //delete c;
    return 0;
}
