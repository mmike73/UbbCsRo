//
// Created by Mihai Moldovan on 10.05.2024.
//

#include "gui.h"
#include "gui_cos.h"
#include "observer.h"

void GUI::init_gui() {
    QHBoxLayout* lyMain = new QHBoxLayout{};
    setLayout(lyMain);

    auto leftLy = new QVBoxLayout;
    auto rightLy = new QVBoxLayout;

    auto formLy = new QFormLayout;
    formLy->addRow("id", id_pr);
    formLy->addRow("nume", nume_pr);
    formLy->addRow("tip", tip_pr);
    formLy->addRow("pret", pret_pr);
    formLy->addRow("producator", producator_pr);
    leftLy->addLayout(formLy);

    auto btnLy1 = new QHBoxLayout{};
    btnLy1->addWidget(btnAdd);
    btnLy1->addWidget(btnDel);
    btnLy1->addWidget(btnMod);

    auto btnLy2 = new QHBoxLayout{};
    btnLy2->addWidget(btnFilterByName);
    btnLy2->addWidget(btnFilterByType);
    btnLy2->addWidget(btnFilterByPrice);

    auto btnLy3 = new QHBoxLayout();
    btnLy3->addWidget(btnSortByName);
    btnLy3->addWidget(btnSortByPrice);
    btnLy3->addWidget(btnSortByNamePrice);

    auto btnLy4 = new QHBoxLayout{};
    btnLy4->addWidget(btnSearchId);
    btnLy4->addWidget(btnUndo);

    auto btnLy5 = new QHBoxLayout{};
    btnLy5->addWidget(btnAddCos);
    btnLy5->addWidget(btnRandomCos);
    btnLy5->addWidget(btnDelCOs);
    btnLy5->addWidget(btnEmptyCos);
    btnLy5->addWidget(btnDraw);
    btnLy5->addWidget(btnCos);

    leftLy->addLayout(btnLy1);
    leftLy->addLayout(btnLy2);
    leftLy->addLayout(btnLy3);
    leftLy->addLayout(btnLy4);

    leftLy->addLayout(btnLy5);
    leftLy->addWidget(btnExit);

    list = new QListView;
    model = new MyTableModel(service);
    list->setModel(model);

    rightLy->addWidget(list);
    load_buttons();

    lyMain->addLayout(leftLy);
    lyMain->addLayout(rightLy);
    lyMain->addLayout(btnLyCategorii);
}

void GUI::load_buttons() {
    QLayoutItem* item;
    while ((item = btnLyCategorii->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    std::multimap<std::string, int>& catalog = service.get_catalog();
    std::string prev_key = "";
    categorii.clear();
    for (const auto& i : catalog) {
        if (i.first != prev_key) {
            prev_key = i.first;
            QPushButton* b = new QPushButton(QString::fromStdString("&" + prev_key));
            categorii.push_back(b);
            btnLyCategorii->addWidget(b);
        }
    }

    for (auto& buton : categorii) {
        QObject::connect(buton, &QPushButton::clicked, [=]() {
            int nr_elemente = how_manny(buton);
            std::string rez = "Numar elemente: " + std::to_string(nr_elemente);
            QMessageBox::critical(nullptr, buton->text(), QString::fromStdString(rez));
            delete buton; // If needed, handle the button deletion properly
        });
    }
}

void GUI::load_data() {
    std::vector<Produs> produse = service.filtreaza_produse([](const Produs& a) {
        return true;
    });
    lst->clear();
    for(auto& produs:produse) {
        lst->addItem(QString::fromStdString(std::to_string(produs.get_id()) + ' ' +produs.get_nume() + " " + produs.get_tip() + " " + std::to_string(produs.get_pret()) + " " + produs.get_producator()));
    }
}

void GUI::init_connect() {
    QObject::connect(btnExit, &QPushButton::clicked, [&]() {
        QMessageBox::critical(nullptr, "Bye, bye!!!", "La revedere!");
        close();
    });
    QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
        auto id = id_pr->text();
        bool ok;
        int id_prod = id.toInt(&ok);
        if(!ok) {
            std::cerr << "ID-ul trebuie sa fie un numar intreg!\n";
        }
        auto tip = tip_pr->text();
        std::string tip_prod = tip.toStdString();
        auto nume = nume_pr->text();
        std::string nume_prod = nume.toStdString();
        auto pret = pret_pr->text();
        int pret_prod = pret.toInt(&ok);
        if(!ok) {
            std::cerr << "Pretul trebuie sa fie intreg!\n";
        }
        auto producator = producator_pr->text();
        std::string producator_prod = producator.toStdString();
        try {
            service.adauga_produs_service(id_prod, nume_prod, tip_prod, pret_prod, producator_prod);
            load_data();
        } catch( const Exception& e) {
            std::cerr << "Eroare: " << e.what();
        }
        load_buttons();
        load_list();
    });
    QObject::connect(btnMod, &QPushButton::clicked, [&]() {
        auto id = id_pr->text();
        bool ok;
        int id_prod = id.toInt(&ok);
        if(!ok) {
            std::cerr << "ID-ul trebuie sa fie un numar intreg!\n";
        }
        auto tip = tip_pr->text();
        std::string tip_prod = tip.toStdString();
        auto nume = nume_pr->text();
        std::string nume_prod = nume.toStdString();
        auto pret = pret_pr->text();
        int pret_prod = pret.toInt(&ok);
        if(!ok) {
            std::cerr << "Pretul trebuie sa fie intreg!\n";
        }
        auto producator = producator_pr->text();
        std::string producator_prod = producator.toStdString();
        if(id.isEmpty()) {
            std::cerr << "Introdu ID-ul!!!\n";
        }
        if(!nume.isEmpty()) {
            try {
                service.modifica_produs_service(id_prod, "d", nume_prod, -1);
            } catch (const Exception& e){
                std::cerr << e.what() << '\n';
            }
        }
        if(!tip.isEmpty()) {
            try {
                service.modifica_produs_service(id_prod,"t",tip_prod,-1);
            } catch (const Exception& e) {
                std::cerr << e.what() << '\n';
            }
        }
        if(!pret.isEmpty()) {
            try {
                service.modifica_produs_service(id_prod,"c","",pret_prod);
            } catch (const Exception& e) {
                std::cerr << e.what() << '\n';
            }
        }
        if(!producator.isEmpty()) {
            try {
                service.modifica_produs_service(id_prod,"p",producator_prod, -1);
            } catch (const Exception& e) {
                std::cerr << e.what() << '\n';
            }
        }
        load_data();
        load_buttons();
        load_list();

    });
    QObject::connect(btnDel, &QPushButton::clicked, [&]() {
        auto id = id_pr->text();
        bool ok;
        int id_prod = id.toInt(&ok);
        if(!ok) {
            std::cerr << "ID-ul trebuie sa fie un numar intreg!\n";
        }
        try {
            service.sterge_produs_service(id_prod);
        }catch (const Exception& e) {
            std::cerr << "Eroare: " << e.what() << '\n';
        }
        load_data();
        load_buttons();
        load_list();

    });
    QObject::connect(btnFilterByName, &QPushButton::clicked, [&]() {
        auto id = id_pr->text();
        auto tip = tip_pr->text();
        auto nume = nume_pr->text();
        std::string nume_prod = nume.toStdString();
        auto pret = pret_pr->text();
        auto producator = producator_pr->text();
        std::vector<Produs> produse = service.filtreaza_produse([&](const Produs& p) {
            if(p.get_nume() == nume_prod) return true;
            return false;
        });
        lst->clear();
        for(auto& produs:produse) {
            lst->addItem(QString::fromStdString(std::to_string(produs.get_id()) + ' ' +produs.get_nume() + " " + produs.get_tip() + " " + std::to_string(produs.get_pret()) + " " + produs.get_producator()));
        }
        load_buttons();
        load_list();

    });
    QObject::connect(btnFilterByType, &QPushButton::clicked, [&]() {
        auto id = id_pr->text();
        auto tip = tip_pr->text();
        std::string tip_prod = tip.toStdString();
        auto nume = nume_pr->text();
        auto pret = pret_pr->text();
        auto producator = producator_pr->text();
        std::vector<Produs> produse = service.filtreaza_produse([&](const Produs& p) {
            if(p.get_tip() == tip_prod) return true;
            return false;
        });
        lst->clear();
        for(auto& produs:produse) {
            lst->addItem(QString::fromStdString(std::to_string(produs.get_id()) + ' ' +produs.get_nume() + " " + produs.get_tip() + " " + std::to_string(produs.get_pret()) + " " + produs.get_producator()));
        }
    });
    QObject::connect(btnSortByName, &QPushButton::clicked, [&]() {
        auto id = id_pr->text();
        auto tip = tip_pr->text();
        auto nume = nume_pr->text();
        auto pret = pret_pr->text();
        auto producator = producator_pr->text();
        std::vector<Produs> produse = service.sorteaza_produse([](const Produs& p1, const Produs& p2) {
            return p1.get_nume() < p2.get_nume();
        });
        lst->clear();
        for(auto& produs:produse) {
            lst->addItem(QString::fromStdString(std::to_string(produs.get_id()) + ' ' +produs.get_nume() + " " + produs.get_tip() + " " + std::to_string(produs.get_pret()) + " " + produs.get_producator()));
        }
    });
    QObject::connect(btnSortByPrice, &QPushButton::clicked, [&]() {
        auto id = id_pr->text();
        auto tip = tip_pr->text();
        auto nume = nume_pr->text();
        auto pret = pret_pr->text();
        auto producator = producator_pr->text();
        std::vector<Produs> produse = service.sorteaza_produse([](const Produs& p1, const Produs& p2) {
            return p1.get_pret() < p2.get_pret();
        });
        lst->clear();
        for(auto& produs:produse) {
            lst->addItem(QString::fromStdString(std::to_string(produs.get_id()) + ' ' +produs.get_nume() + " " + produs.get_tip() + " " + std::to_string(produs.get_pret()) + " " + produs.get_producator()));
        }
    });
    QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
        try {
            service.undo();
        } catch( Exception& e) {
            std::cerr << e.what();
        }

        std::vector<Produs> produse = service.filtreaza_produse([](const Produs& p1) {
            return true;
        });
        lst->clear();
        for(auto& produs:produse) {
            lst->addItem(QString::fromStdString(std::to_string(produs.get_id()) + ' ' +produs.get_nume() + " " + produs.get_tip() + " " + std::to_string(produs.get_pret()) + " " + produs.get_producator()));
        }
    });
    QObject::connect(btnFilterByPrice,&QPushButton::clicked, [&]() {
        int pret_max = pret_pr->text().toInt();
        std::vector<Produs> produse = service.filtreaza_produse([&](const Produs& p) {
            if(p.get_pret() >= pret_max) return true;
            return false;
        });
        lst->clear();
        for(auto& produs:produse) {
            lst->addItem(QString::fromStdString(std::to_string(produs.get_id()) + " " + produs.get_nume() + " " + produs.get_tip() + " " + std::to_string(produs.get_pret()) + " " + produs.get_producator()));
        }
    });
    QObject::connect(btnSortByNamePrice,&QPushButton::clicked, [&]() {
            std::vector<Produs> produse = service.sorteaza_produse([](const Produs& a, const Produs& b) {
                if(a.get_nume() < b.get_nume()) return true;
                else if(a.get_nume() > b.get_nume()) return false;
                else if(a.get_pret() < b.get_pret()) return true;
                return false;
            });
            lst->clear();
            for(auto& produs:produse) {
            lst->addItem(QString::fromStdString(std::to_string(produs.get_id()) + " " + produs.get_nume() + " " + produs.get_tip() + " " + std::to_string(produs.get_pret()) + " " + produs.get_producator()));
        }
    });
    QObject::connect(btnSearchId,&QPushButton::clicked, [&]() {
        int id = id_pr->text().toInt();
        lst->clear();
        Produs produs = service.cauta_produs_service(id);
        lst->addItem(QString::fromStdString(std::to_string(produs.get_id()) + " " + produs.get_nume() + " " + produs.get_tip() + " " + std::to_string(produs.get_pret()) + " " + produs.get_producator()));
    });
    QObject::connect(btnCos,&QPushButton::clicked,[&]() {
        GUI_COS* g = new GUI_COS{service};
        g->show();
    });
    QObject::connect(btnDraw,&QPushButton::clicked,[&]() {
        CosDrawGUI* g = new CosDrawGUI{service};
        g->show();
    });

    QObject::connect(btnAddCos,&QPushButton::clicked,[&]() {
        auto id = id_pr->text();
        try {
            service.adauga_inc_cos(id.toInt());
        } catch (Exception& e) {
            std::cerr << e.what();
        }
    });
    QObject::connect(btnRandomCos,&QPushButton::clicked,[&]() {
        try {
            service.add_random();
        } catch (Exception& e) {
            std::cerr << e.what();
        }
    });
    QObject::connect(btnDelCOs,&QPushButton::clicked,[&]() {
        auto id = id_pr->text();
        try {
            service.sterge_din_cos(id.toInt());
        } catch (Exception& e) {
            std::cerr << e.what();
        }
    });
    QObject::connect(btnEmptyCos,&QPushButton::clicked,[&]() {
        try {
            service.goleste_cos();
        } catch (Exception& e) {
            std::cerr << e.what();
        }
    });
    return;
}

int GUI::how_manny(QPushButton* buton) {
    std::string tip = buton->text().toStdString();
    tip.erase(tip.begin());
    std::cout << tip << " ";
    std::vector<Produs> result_filter = service.filtreaza_produse([&](const Produs &p) {
        if (p.get_tip() == tip) return true;
        return false;
    });
    std::cout << result_filter.size() << '\n';
    return result_filter.size();
}

void GUI::load_list() {
    model->change_made();
}

