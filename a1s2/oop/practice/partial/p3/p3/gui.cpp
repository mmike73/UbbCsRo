//
// Created by Mihai Moldovan on 21.05.2024.
//

#include "gui.h"

void GUI::init_gui() {
    QHBoxLayout* mainly = new QHBoxLayout;
    setLayout(mainly);

    QVBoxLayout* leftly = new QVBoxLayout;
    QVBoxLayout* rightly1 = new QVBoxLayout;
    QVBoxLayout* rightly2 = new QVBoxLayout;

    leftly->addWidget(lst);
    rightly1->addWidget(ateliere);

    rightly2->addWidget(desen_pictura);
    rightly2->addWidget(fotografie);
    rightly2->addWidget(muzica);
    rightly2->addWidget(informatica);
    rightly2->addWidget(jurnalism);

    mainly->addLayout(leftly);
    mainly->addLayout(rightly1);
    mainly->addLayout(rightly2);

    mainly->addWidget(table);
}
void GUI::load_data() {
    lst->clear();
    vector<Elev> e = service.get_all();
    for(const auto& i: e) {
        QListWidgetItem * item = new QListWidgetItem(QString::fromStdString(i.get_str()));
        item->setData(Qt::UserRole, i.get_nr_matricol());
        lst->addItem(item);
    }
}
void GUI::init_connections() {
    QObject::connect(lst,&QListWidget::itemSelectionChanged,[&]() {
        if(lst->selectedItems().size() != 0) {
            int nr_mat = lst->selectedItems()[0]->data(Qt::UserRole).toInt();
            try {
                Elev elev = service.cauta_dupa_nr(nr_mat);
                ateliere->clear();
                ateliere->setText(QString::fromStdString(elev.get_ateliere()));
            } catch(Exception& e) {
                std::cerr << e.what();
                return;
            }
        }
    });
    QObject::connect(desen_pictura,&QPushButton::clicked,[&]() {
        vector<Elev> rez = service.filtreaza_dupa_activitate("desen+pictura");
        table->clear();
        int ind = 0;
        int col = 0;
        for(auto& i:rez) {
            QTableWidgetItem* item1 = new QTableWidgetItem(QString::fromStdString(std::to_string(i.get_nr_matricol())));
            QTableWidgetItem* item2 = new QTableWidgetItem(QString::fromStdString(i.get_nume()));
            QTableWidgetItem* item3 = new QTableWidgetItem(QString::fromStdString(i.get_scoala()));
            table->setItem(ind,col,item1);
            ++col;
            table->setItem(ind,col,item2);
            ++col;
            table->setItem(ind,col,item3);
            ++ind;
            col = 0;
        }
    });
    QObject::connect(fotografie,&QPushButton::clicked,[&]() {
        vector<Elev> rez = service.filtreaza_dupa_activitate("fotografie");
        table->clear();
        int ind = 0;
        int col = 0;
        for(auto& i:rez) {
            QTableWidgetItem* item1 = new QTableWidgetItem(QString::fromStdString(std::to_string(i.get_nr_matricol())));
            QTableWidgetItem* item2 = new QTableWidgetItem(QString::fromStdString(i.get_nume()));
            QTableWidgetItem* item3 = new QTableWidgetItem(QString::fromStdString(i.get_scoala()));
            table->setItem(ind,col,item1);
            ++col;
            table->setItem(ind,col,item2);
            ++col;
            table->setItem(ind,col,item3);
            ++ind;
            col = 0;
        }
    });
    QObject::connect(muzica,&QPushButton::clicked,[&]() {
        vector<Elev> rez = service.filtreaza_dupa_activitate("muzica");
        table->clear();
        int ind = 0;
        int col = 0;
        for(auto& i:rez) {
            QTableWidgetItem* item1 = new QTableWidgetItem(QString::fromStdString(std::to_string(i.get_nr_matricol())));
            QTableWidgetItem* item2 = new QTableWidgetItem(QString::fromStdString(i.get_nume()));
            QTableWidgetItem* item3 = new QTableWidgetItem(QString::fromStdString(i.get_scoala()));
            table->setItem(ind,col,item1);
            ++col;
            table->setItem(ind,col,item2);
            ++col;
            table->setItem(ind,col,item3);
            ++ind;
            col = 0;
        }
    });
    QObject::connect(informatica,&QPushButton::clicked,[&]() {
        vector<Elev> rez = service.filtreaza_dupa_activitate("informatica");
        table->clear();
        int ind = 0;
        int col = 0;
        for(auto& i:rez) {
            QTableWidgetItem* item1 = new QTableWidgetItem(QString::fromStdString(std::to_string(i.get_nr_matricol())));
            QTableWidgetItem* item2 = new QTableWidgetItem(QString::fromStdString(i.get_nume()));
            QTableWidgetItem* item3 = new QTableWidgetItem(QString::fromStdString(i.get_scoala()));
            table->setItem(ind,col,item1);
            ++col;
            table->setItem(ind,col,item2);
            ++col;
            table->setItem(ind,col,item3);
            ++ind;
            col = 0;
        }
    });
    QObject::connect(jurnalism,&QPushButton::clicked,[&]() {
        vector<Elev> rez = service.filtreaza_dupa_activitate("jurnalism");
        table->clear();
        int ind = 0;
        int col = 0;
        for(auto& i:rez) {
            QTableWidgetItem* item1 = new QTableWidgetItem(QString::fromStdString(std::to_string(i.get_nr_matricol())));
            QTableWidgetItem* item2 = new QTableWidgetItem(QString::fromStdString(i.get_nume()));
            QTableWidgetItem* item3 = new QTableWidgetItem(QString::fromStdString(i.get_scoala()));
            table->setItem(ind,col,item1);
            ++col;
            table->setItem(ind,col,item2);
            ++col;
            table->setItem(ind,col,item3);
            ++ind;
            col = 0;
        }
    });
}