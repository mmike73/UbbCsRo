//
// Created by Mihai Moldovan on 20.05.2024.
//

#include "gui.h"

void GUI::init_gui() {
    QHBoxLayout* mainly = new QHBoxLayout;//mainly is a qhboxlayout
    setLayout(mainly);

    QVBoxLayout* leftly = new QVBoxLayout;
    QVBoxLayout* rightly = new QVBoxLayout;

    leftly->addWidget(lst);

    auto formly = new QFormLayout;
    formly->addRow("Suprafata minima",smin);
    formly->addRow("Suprafata maxima",smax);
    formly->addRow("Pret minim",pmin);
    formly->addRow("Pret maxim",pmax);

    rightly->addLayout(formly);

    rightly->addWidget(btnDel);
    rightly->addWidget(btnFilterP);
    rightly->addWidget(btnFilterS);

    mainly->addLayout(leftly);
    mainly->addLayout(rightly);
}
void GUI::load_data() {
    lst->clear();
    vector<Apartament> all = service.get_all();
    for(auto& i:all) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(i.text()));
        string data = std::to_string(i.get_id());
        item->setData(Qt::UserRole, QString::fromStdString(data));
        lst->addItem(item);
    }
}

void GUI::init_connections() {
    QObject::connect(btnDel,&QPushButton::clicked,[&]() {
        if(!lst->selectedItems().empty()) {
            int id_del = lst->selectedItems()[0]->data(Qt::UserRole).toInt();
            service.sterge_apartament(id_del);
            load_data();
        }
    });
    QObject::connect(btnFilterS,&QPushButton::clicked,[&]() {
        bool ok;
        int suprafata_maxima = smax->text().toInt(&ok);
        if(ok) {
            int suprafata_minima = smin->text().toInt(&ok);
            if(ok) {
                vector<Apartament> filtrat = service.filtreaza([suprafata_maxima, suprafata_minima](Apartament &a) {
                    if (suprafata_minima <= a.get_suprafata() && a.get_suprafata() <= suprafata_maxima)
                        return true;
                    return false;
                });
                lst->clear();
                for(auto& i:filtrat) {
                    QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(i.text()));
                    string id_ap = std::to_string(i.get_id());
                    item->setData(Qt::UserRole, QString::fromStdString(id_ap));
                    lst->addItem(item);
                }
            }
        } else {

        }
    });
    QObject::connect(btnFilterP,&QPushButton::clicked,[&]() {
        bool ok;
        int pret_maxim = pmax->text().toInt(&ok);
        if(ok) {
            int pret_minim = pmin->text().toInt(&ok);
            if (ok) {
                vector<Apartament> filtrat = service.filtreaza([pret_minim,pret_maxim](Apartament &a) {
                    if (pret_minim <= a.get_pret() && a.get_pret() <= pret_maxim)
                        return true;
                    return false;
                });
                lst->clear();
                for(auto& i:filtrat) {
                    QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(i.text()));
                    string id_ap = std::to_string(i.get_id());
                    item->setData(Qt::UserRole, QString::fromStdString(id_ap));
                    lst->addItem(item);
                }
            }
        }
    });
}