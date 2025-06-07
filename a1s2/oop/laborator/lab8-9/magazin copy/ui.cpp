//
// Created by Mihai Moldovan on 28.03.2024.
//

#include "ui.h"
#include <string>
#include <cctype>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <functional>
#include <map>
#include "exception.h"

void strip(std::string &str);

std::vector<std::string> split_string(std::string str, char separator);

bool is_number(std::string &number);

void UI::adauga_produs(std::vector<std::string> &params) {
    std::string id, nume, tip, pret, producator;
    int id_produs, pret_produs;
    if (!(params.size() == 1 || params.size() == 6)) {
        throw Exception("Numar parametri invalid!!!\n");
    } else if (params.size() == 1) {
        std::cout << "Introdu ID-ul noului produs: ";
        std::cin >> id;
        strip(id);
        std::cout << "Introdu denumirea noului produs: ";
        std::cin >> nume;
        strip(nume);
        std::cout << "Introdu tipul noului produs: ";
        std::cin >> tip;
        strip(tip);
        std::cout << "Introdu pretul noului produs: ";
        std::cin >> pret;
        strip(pret);
        std::cout << "Introdu producatorul noului produs: ";
        std::cin >> producator;
        strip(producator);
    } else {
        id = params[1];
        nume = params[2];
        tip = params[3];
        pret = params[4];
        producator = params[5];
    }
    if (is_number(id)) id_produs = stoi(id);
    else {
        throw Exception("Tip de date invalid! ID-ul trebuie sa fie un numar intreg pozitiv!\n");
    }
    if (is_number(pret)) pret_produs = stoi(pret);
    else {
        throw Exception("Tip de date invalid! Pretul trebuie sa fie un numar intreg pozitiv!\n");
    }
    service.adauga_produs_service(id_produs, nume, tip, pret_produs, producator);
}

void UI::modifica_produs(std::vector<std::string> &params) {
    std::string id, camp, valoare;
    int id_produs, pret_produs;
    if (!(params.size() == 1 || params.size() == 4)) {
        throw Exception("Numar parametri invalid!!!\n");
    } else if (params.size() == 1) {
        std::cout << "Introdu ID-ul produsului: ";
        std::cin >> id;
        strip(id);
        std::cout << "Introdu campul pe care doresti sa il modifici (d/t/c(pret)/p): ";
        std::cin >> camp;
        strip(camp);
        std::cout << "Introdu valoarea noua (numar intreg pentru pret): ";
        std::cin >> valoare;
        strip(valoare);
    } else {
        id = params[1];
        camp = params[2];
        valoare = params[3];
    }
    std::vector<std::string> campuri = {"d", "t", "c", "p"};
    if (std::count(campuri.begin(), campuri.end(), camp) == 0) {
        throw Exception("Camp invalid!!!\n");
        return;
    }
    if (is_number(id)) id_produs = stoi(id);
    else {
        throw Exception("Tip de date invalid! ID-ul trebuie sa fie un numar intreg pozitiv!\n");
    }
    if (camp == "c" && is_number(valoare)) pret_produs = stoi(valoare);
    else if (camp == "c") {
        throw Exception("Tip de date invalid! Pretul trebuie sa fie un numar intreg pozitiv!\n");
    }
    service.modifica_produs_service(id_produs, camp, valoare, pret_produs);
}

void UI::sterge_produs(std::vector<std::string> &params) {
    std::string id;
    int id_produs;
    if (!(params.size() == 1 || params.size() == 2)) {
        throw Exception("Numar parametri invalid!!!\n");
    } else if (params.size() == 1) {
        std::cout << "Introdu ID-ul produsului pe care vrei sa il stergi: ";
        std::cin >> id;
        strip(id);
    } else if (params.size() == 2) {
        id = params[1];
    }
    if (is_number(id)) id_produs = stoi(id);
    else {
        std::cout << "ID-ul trebuie sa fie un numar natural pozitiv nenul!!!\n";
    }
    service.sterge_produs_service(id_produs);
}

void UI::print_catalog(std::vector<std::string>& params) {
    std::multimap<std::string,int>& catalog = service.get_catalog();
    std::string prevKey = "";
    for( const auto& i: catalog) {
        if(i.first != prevKey) {
            std::vector<Produs> result_filter = service.filtreaza_produse([=](const Produs &p) {
                if (p.get_tip() == i.first) return true;
                return false;
            });
            std::cout << "Produse de tip " << i.first <<":\n";
            for( auto&k :result_filter) {
                std::cout << k.get_id() << " " << k.get_nume() << " " << k.get_tip() << " " << k.get_pret() << " "
                          << k.get_producator() << '\n';
            }
            prevKey = i.first;
        }
    }
}

void UI::undo() {
    service.undo();
}

///////
////////
void UI::vizualizeaza_produse(std::vector<std::string> &params) {
    std::vector<std::string> campuri = {"d", "t", "c", "p"};
    if (params.size() == 2 && params[1] == "a") {
        std::vector<Produs> result_filter = service.filtreaza_produse([](const Produs &p) {
            return true;
        });
        for (auto &i: result_filter) {
            std::cout << i.get_id() << " " << i.get_nume() << " " << i.get_tip() << " " << i.get_pret() << " "
                      << i.get_producator() << '\n';
        }
    } else if (params.size() == 2 && is_number(params[1])) {
        int id_produs = stoi(params[1]);
        Produs i = service.cauta_produs_service(id_produs);
        std::cout << i.get_id() << " " << i.get_nume() << " " << i.get_tip() << " " << i.get_pret() << " "
                  << i.get_producator() << '\n';
    } else if (params.size() == 3 && std::count(campuri.begin(), campuri.end(), params[1]) == 0) {
        throw Exception("Camp invalid!!!\n");
    } else if (params.size() == 3) {
        std::vector<Produs> result_filter;
        //std::string fil = params[2];
        if (params[1] == "d")
            result_filter = service.filtreaza_produse([=](const Produs &p) {
                if (p.get_nume() == params[2]) return true;
                return false;
            });
        if (params[1] == "p")
            result_filter = service.filtreaza_produse([=](const Produs &p) {
                if (p.get_producator() == params[2]) return true;
                return false;
        });
        if (params[1] == "t")
            result_filter = service.filtreaza_produse([=](const Produs &p) {
                    if (p.get_tip() == params[2]) return true;
                    return false;
            });
        if (params[1] == "c") {
            if (!is_number(params[3])) {
                throw Exception("Parametrul trebuie sa fie numar intreg!!!\n");
            }
            result_filter = service.filtreaza_produse([=](const Produs &p) {
                if (p.get_pret() == stoi(params[2])) return true;
                return false;
            });
        }
        for (auto &i: result_filter) {
            std::cout << i.get_id() << " " << i.get_nume() << " " << i.get_tip() << " " << i.get_pret() << " "
                      << i.get_producator() << '\n';
        }
    } else {
        throw Exception("Parametri invalizi!!!\n");
    }
}


void UI::sorteaza_produse(std::vector<std::string> &params) {
    if (params.size() == 3) {
        if (params[2] == "c" || params[2] == "d") {
            std::vector<Produs> result_sort;
            if (params[2] == "c") {
                if (params[1] == "d") result_sort = service.sorteaza_produse([=](const Produs& p1, const Produs& p2) {
                        if( p1.get_nume() > p2.get_nume()) return -1;
                        if( p1.get_nume() < p2.get_nume()) return 1;
                        return 0;
                });///de aicisa
                if (params[1] == "d+c") {
                    result_sort = service.sorteaza_produse([=](const Produs& p1, const Produs& p2) {
                        if( p1.get_nume() > p2.get_nume()) return -1;
                        if( p1.get_nume() < p2.get_nume()) return 1;
                        if( p1.get_pret() > p2.get_pret()) return -1;
                        if( p1.get_pret() < p2.get_pret()) return 1;
                        return 0;
                    });
                }
                if (params[1] == "c") {
                    result_sort = service.sorteaza_produse([=](const Produs& p1, const Produs& p2) {
                        if( p1.get_pret() > p2.get_pret()) return -1;
                        if( p1.get_pret() < p2.get_pret()) return 1;
                        return 0;
                    });
                }
            } else if (params[2] == "d") {
                if (params[1] == "d") result_sort = service.sorteaza_produse([](const Produs& p1, const Produs& p2) {
                    if( p1.get_nume() < p2.get_nume()) return -1;
                    if( p1.get_nume() > p2.get_nume()) return 1;
                    return 0;
                });
                if (params[1] == "d+c") result_sort = service.sorteaza_produse([](const Produs& p1, const Produs& p2) {
                    if( p1.get_nume() > p2.get_nume()) return 1;
                    if( p1.get_nume() < p2.get_nume()) return -1;
                    if( p1.get_pret() > p2.get_pret()) return 1;
                    if( p1.get_pret() < p2.get_pret()) return -1;
                    return 0;
                });
                if (params[1] == "c") result_sort = service.sorteaza_produse([](const Produs& p1, const Produs& p2) {
                    if( p1.get_pret() < p2.get_pret()) return -1;
                    if( p1.get_pret() > p2.get_pret()) return 1;
                    return 0;
                });
            }
            for (auto &i: result_sort) {
                std::cout << i.get_id() << " " << i.get_nume() << " " << i.get_tip() << " " << i.get_pret() << " "
                          << i.get_producator() << '\n';
            }
        } else {
            throw Exception("Directie invalida!!!\n");
        }
    } else {
        throw Exception("Parametri invalizi!!!\n");
    }
}

void UI::adauga_produs_in_cos(std::vector<std::string> &params) {
    if (params.size() != 2) {
        throw Exception("Numar parametri invalid!!!\n");
    }
    if (!is_number(params[1])) {
        throw Exception("Parametru invalid!!!\n");
    }
    int id = stoi(params[1]);
    service.adauga_inc_cos(id);
}

///
void UI::sterge_produs_in_cos(std::vector<std::string> &params) {
    if (params.size() != 2) {
        throw Exception("Numar parametri invalid!!!\n");
    }
    if (!is_number(params[1])) {
        throw Exception("Parametru invalid!!!\n");
    }
    service.sterge_din_cos(stoi(params[1]));
}

void UI::vizualizeaza_produse_cos(std::vector<std::string> &params) {
    if (params.size() != 1) {
        throw Exception("Numar parametri invalid!!!\n");
    }
    std::vector<int> rez = service.get_all_cos();

    for (auto &i: rez) {
        Produs &n = service.cauta_produs_service(i);
        std::cout << n.get_id() << " " << n.get_nume() << " " << n.get_tip() << " " << n.get_pret() << " "
                  << n.get_producator() << '\n';
    }
    std::cout << '\n';
}

void UI::clear_cos(std::vector<std::string> &params) {
    if (params.size() != 1) {
        throw Exception("Numar parametri invalid!!!\n");
    }
    service.goleste_cos();
}

void UI::random_cos(std::vector<std::string> &params) {
    if (params.size() != 2) {
        throw Exception("Numar parametri invalid!!!\n");
    }
    if (!is_number(params[1])) {
        throw Exception("Parametru invalid!!!\n");
    }
    std::vector<Produs> result_filter = service.filtreaza_produse([](const Produs&) {return true;});
    std::mt19937 mt{std::random_device{}()};
    std::uniform_int_distribution<> dist(0, result_filter.size() - 1);
    int i = 0, p, n_elem = stoi(params[1]);
    while (++i <= n_elem) {
        p = dist(mt);
        service.adauga_inc_cos(result_filter[p].get_id());
    }
}

void UI::export_cos(std::vector<std::string> &params) {
    if (params.size() != 2) {
        throw Exception("Numar parametri invalid!!!\n");
    }
    std::string cale_fisier = "../exports/" + params[1];
    service.exporta_cos_s(cale_fisier);
}

void help() {
    std::cout << "add / mod / del / view / sort / exit          #pentru a accesa introducerea ghidata\n";
    std::cout << "add id(int) denumire(string) tip(string) pret(int) producator(string)\n";
    std::cout << "mod id(int) camp(d/t/c(pret)/p) valoare(int(cost)/string(restul)\n";
    std::cout << "del id(int)\n";
    std::cout << "view a                                        #pentru a vedea toate produsele\n";
    std::cout << "view numar_natural(id-ul produsului cautatt)  #pentru a cauta un produs dupa id\n";
    std::cout << "view camp(c(cost)/n/p)                        #pentru a filtra produsele\n";
    std::cout << "sort camp(d/c(cost)/d+c) directie(c/d)\n";
}


void UI::run() {
    std::string user_input;
    //implementez filter ca si view cu conditii supimentare
    std::vector<std::string> commands = {"add", "mod", "del", "view", "filter", "sort", "add_cos", "del_cos",
                                         "view_cos", "clear_cos", "random_cos", "export_cos","catalog", "undo"};
    std::cout << "Tasteaza 'help' pentru a accesa comenzile.\n";

    while (user_input != "exit") {
        std::cout << "Total cos: " << service.get_total_cos() << "\n" << ">>> ";
        getline(std::cin, user_input);
        strip(user_input);
        if (user_input == "exit") continue;
        else if (user_input == "help") {
            help();
            continue;
        }
        std::vector<std::string> parts = split_string(user_input, ' ');
        if (parts.empty() == 1) continue;
        else if (std::count(commands.begin(), commands.end(), parts[0]) == 0) {
            std::cout << "Comanda invalida!!!\n";
            continue;
        }
        try {
            if (parts[0] == "add") {
                adauga_produs(parts);
            } else if (parts[0] == "mod") {
                modifica_produs(parts);
            } else if (parts[0] == "del") {
                sterge_produs(parts);
            } else if (parts[0] == "view") {
                vizualizeaza_produse(parts);
            } else if (parts[0] == "sort") {
                sorteaza_produse(parts);
            } else if (parts[0] == "add_cos") {
                adauga_produs_in_cos(parts);
            } else if (parts[0] == "del_cos") {
                sterge_produs_in_cos(parts);
            } else if (parts[0] == "view_cos") {
                vizualizeaza_produse_cos(parts);
            } else if (parts[0] == "clear_cos") {
                clear_cos(parts);
            } else if (parts[0] == "random_cos") {
                random_cos(parts);
            } else if (parts[0] == "export_cos") {
                export_cos(parts);
            } else if (parts[0] == "catalog") {
                print_catalog(parts);
            } else if (parts[0] == "undo") {
                undo();
            }
        } catch (const Exception &e) {
            std::cerr << "Eroare: " << e.what() << std::endl;
        }
    }
}

///
void strip(std::string &str) {
    if (str.length() == 0) {
        return;
    }

    auto start_it = str.begin();
    auto end_it = str.rbegin();
    while (std::isspace(*start_it)) {
        ++start_it;
        if (start_it == str.end()) break;
    }
    while (std::isspace(*end_it)) {
        ++end_it;
        if (end_it == str.rend()) break;
    }
    int start_pos = start_it - str.begin();
    int end_pos = end_it.base() - str.begin();
    str = start_pos <= end_pos ? std::string(start_it, end_it.base()) : "";
}

std::vector<std::string> split_string(std::string str, char separator) {
    std::vector<std::string> result;
    std::string current = "";
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == separator) {
            if (current != "") {
                result.push_back(current);
                current = "";
            }
            continue;
        }
        current += str[i];
    }
    if (current.empty() != 1)
        result.push_back(current);
    return result;
}

bool is_number(std::string &number) {
    return std::all_of(number.begin(), number.end(), ::isdigit);
}
