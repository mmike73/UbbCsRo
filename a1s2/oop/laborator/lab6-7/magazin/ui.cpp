//
// Created by Mihai Moldovan on 28.03.2024.
//

#include "ui.h"
#include <string>
#include <cctype>
#include <iostream>
#include <vector>
#include <algorithm>
#include "comparatori.h"
#include "exception.h"

void strip(std::string& str);
std::vector<std::string> split_string(std::string str, char separator);
bool is_number(std::string& number);

void UI::adauga_produs(std::vector<std::string>& params) {
    std::string id, nume, tip, pret, producator;
    int id_produs, pret_produs;
    if(!(params.size() == 1 || params.size() == 6)) {
        throw Exception( "Numar parametri invalid!!!\n");
        return;
    }
    else if(params.size() == 1) {
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
    }
    else {
        id = params[1];
        nume = params[2];
        tip = params[3];
        pret = params[4];
        producator = params[5];
    }
    if(is_number(id)) id_produs = stoi(id);
    else {
        throw Exception( "Tip de date invalid! ID-ul trebuie sa fie un numar intreg pozitiv!\n");
        return;
    }
    if(is_number(pret)) pret_produs = stoi(pret);
    else {
        throw Exception( "Tip de date invalid! Pretul trebuie sa fie un numar intreg pozitiv!\n");
        return;
    }
    service.adauga_produs_service(id_produs, nume, tip, pret_produs, producator);
}

void UI::modifica_produs(std::vector<std::string>& params) {
    std::string id, camp, valoare;
    int id_produs, pret_produs;
    if(!(params.size() == 1 || params.size() == 4)) {
        throw Exception( "Numar parametri invalid!!!\n");
        return;
    }
    else if(params.size() == 1) {
        std::cout << "Introdu ID-ul produsului: ";
        std::cin >> id;
        strip(id);
        std::cout << "Introdu campul pe care doresti sa il modifici (d/t/c(pret)/p): ";
        std::cin >> camp;
        strip(camp);
        std::cout << "Introdu valoarea noua (numar intreg pentru pret): ";
        std::cin >> valoare;
        strip(valoare);
    }
    else {
        id = params[1];
        camp = params[2];
        valoare = params[3];
    }
    std::vector<std::string> campuri = {"d", "t", "c", "p"};
    if( std::count(campuri.begin(), campuri.end(), camp) == 0) {
        throw Exception( "Camp invalid!!!\n");
        return;
    }
    if(is_number(id)) id_produs = stoi(id);
    else {
        throw Exception( "Tip de date invalid! ID-ul trebuie sa fie un numar intreg pozitiv!\n");
        return;
    }
    if( camp == "c" && is_number(valoare)) pret_produs = stoi(valoare);
    else if(camp == "c") {
        throw Exception( "Tip de date invalid! Pretul trebuie sa fie un numar intreg pozitiv!\n");
        return;
    }
    service.modifica_produs_service(id_produs, camp, valoare, pret_produs);
}

void UI::sterge_produs(std::vector<std::string>& params) {
    std::string id;
    int id_produs;
    if( !(params.size() == 1 || params.size() == 2)) {
        throw Exception( "Numar parametri invalid!\n");
        return;
    }
    else if( params.size() == 1) {
        std::cout << "Introdu ID-ul produsului pe care vrei sa il stergi: ";
        std::cin >> id;
        strip(id);
    }
    else if( params.size() == 2) {
        id = params[1];
    }
    if(is_number(id)) id_produs = stoi(id);
    else {
        throw Exception( "ID-ul trebuie sa fie un numar natural pozitiv nenul!!!\n");
        return;
    }
    service.sterge_produs_service(id_produs);
}
///////
////////
void UI::vizualizeaza_produse(std::vector<std::string>& params) {
    std::vector<std::string> campuri = {"d", "t", "c", "p"};
    if( params.size() == 2 && params[1] == "a") {
        Vector<Produs> result_filter = service.filtreaza_produse(filtru_vid, "", 0);
        for( auto& i:result_filter) {
            std::cout << i.get_id() << " " << i.get_nume() << " " << i.get_tip() << " " << i.get_pret() << " " << i.get_producator()  << '\n';
        }
    }
    else if( params.size() == 2 && is_number(params[1])) {
        int id_produs = stoi(params[1]);
        Produs i = service.cauta_produs_service(id_produs);
        std::cout << i.get_id() << " " << i.get_nume() << " " << i.get_tip() << " " << i.get_pret() << " " << i.get_producator()  << '\n';
    }
    else if( params.size() == 3 && std::count(campuri.begin(), campuri.end(), params[1]) == 0) {
        throw Exception( "Camp invalid!!!\n");
        return;
    }
    else if( params.size() == 3){
        if( params[1] == "d") {
            Vector<Produs> result_filter = service.filtreaza_produse(filtru_nume, params[2], 0);
            for( auto& i:result_filter) {
                std::cout << i.get_id() << " " << i.get_nume() << " " << i.get_tip() << " " << i.get_pret() << " " << i.get_producator()  << '\n';
            }
        }

        if( params[1] == "p") {
            Vector<Produs> result_filter = service.filtreaza_produse(filtru_producator, params[2], 0);
            for( auto& i:result_filter) {
                std::cout << i.get_id() << " " << i.get_nume() << " " << i.get_tip() << " " << i.get_pret() << " " << i.get_producator()  << '\n';
            }
        }
        if( params[1] == "t") {
            Vector<Produs> result_filter = service.filtreaza_produse(filtru_tip, params[2], 0);
            for( auto& i:result_filter) {
                std::cout << i.get_id() << " " << i.get_nume() << " " << i.get_tip() << " " << i.get_pret() << " " << i.get_producator()  << '\n';
            }
        }
        if( params[1] == "c") {
            if(!is_number(params[3])) {
                throw Exception( "Parametrul trebuie sa fie numar intreg!!!\n");
                return;
            }
            Vector<Produs> result_filter = service.filtreaza_produse(filtru_pret, "", stoi(params[2]));
            for( auto& i:result_filter) {
                std::cout << i.get_id() << " " << i.get_nume() << " " << i.get_tip() << " " << i.get_pret() << " " << i.get_producator()  << '\n';
            }
        }
    }
    else {
        throw Exception("Parametri invalizi!\n");
    }
}


void UI::sorteaza_produse(std::vector<std::string>& params) {
    if( params.size() == 3) {
        if( params[2] == "c" || params[2] == "d") {
            if (params[2] == "c") {
                if (params[1] == "d") {
                    Vector<Produs> result_sort = service.sorteaza_produse(cmp_nume_c);
                    for (auto &i: result_sort) {
                        std::cout << i.get_id() << " " << i.get_nume() << " " << i.get_tip() << " " << i.get_pret() << " "
                                  << i.get_producator() << '\n';
                    }
                }
                if (params[1] == "d+c") {
                    Vector<Produs> result_sort = service.sorteaza_produse(cmp_nume_pret_c);
                    for (auto &i: result_sort) {
                        std::cout << i.get_id() << " " << i.get_nume() << " " << i.get_tip() << " " << i.get_pret() << " "
                                  << i.get_producator() << '\n';
                    }
                }
                if (params[1] == "c") {
                    Vector<Produs> result_sort = service.sorteaza_produse(cmp_pret_c);
                    for (auto &i: result_sort) {
                        std::cout << i.get_id() << " " << i.get_nume() << " " << i.get_tip() << " " << i.get_pret() << " "
                                  << i.get_producator() << '\n';
                    }
                }
            } else if (params[2] == "d") {
                if (params[1] == "d") {
                    Vector<Produs> result_sort = service.sorteaza_produse(cmp_nume_d);
                    for (auto &i: result_sort) {
                        std::cout << i.get_id() << " " << i.get_nume() << " " << i.get_tip() << " " << i.get_pret() << " "
                                  << i.get_producator() << '\n';
                    }
                }
                if (params[1] == "d+c") {
                    Vector<Produs> result_sort = service.sorteaza_produse(cmp_nume_pret_d);
                    for (auto &i: result_sort) {
                        std::cout << i.get_id() << " " << i.get_nume() << " " << i.get_tip() << " " << i.get_pret() << " "
                                  << i.get_producator() << '\n';
                    }
                }
                if (params[1] == "c") {
                    Vector<Produs> result_sort = service.sorteaza_produse(cmp_pret_d);
                    for (auto &i: result_sort) {
                        std::cout << i.get_id() << " " << i.get_nume() << " " << i.get_tip() << " " << i.get_pret() << " "
                                  << i.get_producator() << '\n';
                    }
                }
            }

        }
        else {
            throw Exception( "Directie invalida!!!");
        }
    }
    else {
        throw Exception( "Parametri invalizi!\n");
    }
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
    std::vector<std::string>commands = {"add", "mod", "del", "view", "filter", "sort"};
    std::cout << "Tasteaza 'help' pentru a accesa comenzile.\n";

    while(user_input != "exit") {
        std::cout << ">>> ";
        getline(std::cin, user_input);
        strip(user_input);
        if(user_input == "exit") continue;
        else if(user_input == "help") {
            help();
            continue;
        }
        std::vector<std::string> parts = split_string(user_input, ' ');
        if(parts.empty() == 1) continue;
        else if( std::count(commands.begin(), commands.end(), parts[0]) == 0) {
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
            }
        } catch ( const Exception& e) {
            std::cerr << "Eroare: " << e.what() << std::endl;
        }
    }
}

///
void strip(std::string& str)
{
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
    for(int i = 0; i < str.size(); i++){
        if(str[i] == separator){
            if(current != ""){
                result.push_back(current);
                current = "";
            }
            continue;
        }
        current += str[i];
    }
    if(current.empty() != 1)
        result.push_back(current);
    return result;
}

bool is_number(std::string& number) {
    return std::all_of(number.begin(), number.end(), ::isdigit);
}
