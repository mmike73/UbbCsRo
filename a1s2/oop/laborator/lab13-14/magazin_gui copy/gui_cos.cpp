//
// Created by Mihai Moldovan on 25.05.2024.
//

#include "gui_cos.h"
#include "observer.h"

void GUI_COS::init_window() {
    QHBoxLayout* lyMain = new QHBoxLayout{};
    setLayout(lyMain);

    auto leftLy = new QVBoxLayout;
    auto rightLy = new QVBoxLayout;

    auto formLy = new QFormLayout{};
    formLy->addRow("id", id_pr);
    formLy->addRow("nume_fisier", nume_fisier);

    auto btnLy1 = new QHBoxLayout{};
    btnLy1->addWidget(btnAddCos);
    btnLy1->addWidget(btnRandom);
    btnLy1->addWidget(btnRmCos);
    btnLy1->addWidget(btnGolesteCos);

    auto btnLy2 = new QHBoxLayout{};
    btnLy2->addWidget(btnSaveCos);

    rightLy->addLayout(formLy);
    rightLy->addLayout(btnLy1);
    rightLy->addLayout(btnLy2);

    leftLy->addWidget(lst);
    leftLy->addWidget(tbl);

    lyMain->addLayout(leftLy);
    lyMain->addLayout(rightLy);
}

void GUI_COS::load_data() {
    std::vector<int> cos = service.get_all_cos();
    lst->clear();
    for(auto& i:cos) {
        Produs& p = service.cauta_produs_service(i);
        lst->addItem(QString::fromStdString(std::to_string(p.get_id())) + " " + QString::fromStdString(p.get_nume()) + " " + QString::fromStdString(std::to_string(p.get_pret())));
    }
}

void GUI_COS::load_table() {
    std::vector<int> cos = service.get_all_cos();
    tbl->setRowCount(0);
    int row = 0,col = 0;
    for(auto& i:cos) {
        tbl->insertRow(row);
        Produs& p = service.cauta_produs_service(i);
        QTableWidgetItem* item1 = new QTableWidgetItem(QString::fromStdString(std::to_string(p.get_id())));
        tbl->setItem(row,col,item1);
        col++;
        QTableWidgetItem* item2 = new QTableWidgetItem(QString::fromStdString(p.get_nume()));
        tbl->setItem(row,col,item2);
        col++;
        QTableWidgetItem* item3 = new QTableWidgetItem(QString::fromStdString(std::to_string(p.get_pret())));
        tbl->setItem(row,col,item3);
        col = 0;
        row++;
    }
}

void GUI_COS::reload_data(std::vector<int>& produse_cos) {
    lst->clear();
    for(auto& i:produse_cos) {
        Produs& p = service.cauta_produs_service(i);
        lst->addItem(QString::fromStdString(std::to_string(p.get_id())) + " " + QString::fromStdString(p.get_nume()) + " " + QString::fromStdString(std::to_string(p.get_pret())));
    }
}


void GUI_COS::init_connect() {
    QObject::connect(btnAddCos,&QPushButton::clicked,[&]() {
        auto id = id_pr->text();
        try {
            service.adauga_inc_cos(id.toInt());
        } catch (Exception& e) {
            std::cerr << e.what();
        }
        load_data();
    });
    QObject::connect(btnRandom,&QPushButton::clicked,[&]() {
        try {
            service.add_random();
        } catch (Exception& e) {
            std::cerr << e.what();
        }
        load_data();
    });
    QObject::connect(btnRmCos,&QPushButton::clicked,[&]() {
        auto id = id_pr->text();
        try {
            service.sterge_din_cos(id.toInt());
        } catch (Exception& e) {
            std::cerr << e.what();
        }
        load_data();
    });
    QObject::connect(btnSaveCos,&QPushButton::clicked,[&]() {
        auto fisier = nume_fisier->text();
        try {
            service.exporta_cos_s("../exports/" + fisier.toStdString());
        } catch (Exception& e) {
            std::cerr << e.what();
        }
        load_data();
    });
    QObject::connect(btnGolesteCos,&QPushButton::clicked,[&]() {
        try {
            service.goleste_cos();
        } catch (Exception& e) {
            std::cerr << e.what();
        }
        load_data();
    });
}

