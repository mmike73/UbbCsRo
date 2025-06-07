//
// Created by Mihai Moldovan on 18.05.2024.
//

#include "gui.h"
#include <string>

void GUI::init_gui() {
    QHBoxLayout* lyMain = new QHBoxLayout{};
    setLayout(lyMain);

    auto leftLy = new QVBoxLayout;
    auto rightLy = new QVBoxLayout;

    QLabel* label1 = new QLabel(this);
    label1->setText("Procesoare:");
    leftLy->addWidget(label1);
    leftLy->addWidget(lst_procesoare);
    QLabel* label2 = new QLabel(this);
    label2->setText("Placi:");
    leftLy->addWidget(label2);
    leftLy->addWidget(lst_placi);

    auto formLy = new QFormLayout;
    formLy->addRow("nume",nume);
    formLy->addRow("socket",socket);
    formLy->addRow("pret",pret);
    rightLy->addLayout(formLy);

    rightLy->addWidget(total);

    rightLy->addWidget(add_placa);
    rightLy->addWidget(filtter_cpu_socket);

    lyMain->addLayout(leftLy);
    lyMain->addLayout(rightLy);
}
void GUI::load_data() {
    vector<Procesor> all_cpus = service.get_procesoare();
    vector<PlacaDeBaza> all_motherboards = service.get_placi();
    lst_placi->clear();
    lst_procesoare->clear();
    for(auto& i: all_cpus) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(i.get_nume() + " " + i.get_socket()));
        item->setData(Qt::UserRole, QString::fromStdString(i.get_nume()));
        lst_procesoare->addItem(item);
    }
    for(auto& i: all_motherboards) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(i.get_nume() + " " + i.get_socket()));
        item->setData(Qt::UserRole, QString::fromStdString(i.get_nume()));
        lst_placi->addItem(item);
    }
}
void GUI::make_connections() {
    QObject::connect(add_placa, &QPushButton::clicked, [&]() {
        string nume_cpu = nume->text().toStdString();
        string socket_cpu = socket->text().toStdString();
        bool ok;
        int pret_cpu = pret->text().toInt(&ok);
        if(ok == false) {
            std::cerr << "Pretul trbuie sa fie un intreg pozitiv!";
        }
        try {
            service.add_placa(nume_cpu,socket_cpu,pret_cpu);
            std::cout << "Added";
        } catch(Exception& e) {
            std:: cerr << e.what();
        }
        load_data();
    });
    QObject::connect(filtter_cpu_socket,&QPushButton::clicked, [&]() {
        string name = cpu->data(Qt::UserRole).toString().toStdString();
        const Procesor proc = service.cauta_procesor(name);

        vector<PlacaDeBaza> compatibile = service.filtreaza_placi([=](const PlacaDeBaza& p) {
            if(p.get_socket() == proc.get_socket()) return true;
            return false;
        });
        lst_placi->clear();
        for(auto& i: compatibile) {
            lst_placi->addItem(QString::fromStdString(i.get_nume() + " " + i.get_socket()));
        }
    });
    QObject::connect(lst_procesoare, &QListWidget::itemSelectionChanged, [&]() {
        if(!lst_procesoare->selectedItems().empty()) {
            cpu = lst_procesoare->selectedItems().first();
            change_total();
        } else {
            delete cpu;
            cpu = new QListWidgetItem;
        }
        std::cout << cpu->text().toStdString() << '\n';
    });
    QObject::connect(lst_placi, &QListWidget::itemSelectionChanged, [&]() {
        if(!lst_placi->selectedItems().empty()) {
            motherboard = lst_placi->selectedItems().first();
            change_total();
        } else {
            delete motherboard;
            motherboard = new QListWidgetItem;
        }
        std::cout << motherboard->text().toStdString() << '\n';
    });
}

void GUI::change_total() {
    if(!lst_placi->selectedItems().empty() && !lst_procesoare->selectedItems().empty()) {
        string name = cpu->data(Qt::UserRole).toString().toStdString();
        Procesor p = service.cauta_procesor(name);
        name = motherboard->data(Qt::UserRole).toString().toStdString();
        PlacaDeBaza b = service.cauta_placa(name);

        int pret = b.get_pret();
        pret += p.get_pret();

        string pret_total = std::to_string(pret);
        total->setText("Total: " + QString::fromStdString(pret_total));
    }
    else {
        total->setText("Total: 0");
    }
}
