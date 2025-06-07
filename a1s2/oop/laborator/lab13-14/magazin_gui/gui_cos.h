//
// Created by Mihai Moldovan on 25.05.2024.
//

#ifndef MAGAZIN_GUI_GUI_COS_H
#define MAGAZIN_GUI_GUI_COS_H
#include "service.h"
#include <QtWidgets/qwidget.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/QPushButton>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QPainter>
#include <qmessagebox.h>
#include <vector>
#include <string>
#include "exception.h"
#include "domain.h"
#include "observer.h"
#include "models.h"

class GUI_COS: public QWidget, public Observer {
public:
    GUI_COS(ServiceProduse& service): service{service} {
        init_window();
        load_data();
        load_table();
        init_connect();
        service.addObserver(this);
    }

    QListWidget* lst = new QListWidget;
    QTableWidget* tbl = new QTableWidget(0,3);

    QLineEdit* id_pr = new QLineEdit;
    QLineEdit* nume_fisier = new QLineEdit;

    QPushButton* btnAddCos = new QPushButton("&Adauga in cos");
    QPushButton* btnRandom = new QPushButton("&Adauga 10 elemente");
    QPushButton* btnRmCos = new QPushButton("&Sterge din cos");
    QPushButton* btnSaveCos = new QPushButton("&Salveaza cos");
    QPushButton* btnGolesteCos = new QPushButton("&Goleste cos");


private:
    ServiceProduse& service;

    QListView* list;
    MyTableModel* model;

    void init_window();
    void load_data();
    void load_table();
    void reload_data(std::vector<int>& produse_cos);
    void init_connect();

    void update() override {
        model->change_made();
    }

    ~GUI_COS() {
        service.removeObsever(this);
    }
};

class CosDrawGUI: public QWidget, public Observer {
private:
    ServiceProduse& service;

    QTableView* table;
    MyTableModel* model;


    ~CosDrawGUI() {
        service.removeObsever(this);
    }

    void paintEvent(QPaintEvent*) override {
        QPainter p{this};
        int x = 50, y = 50;
        for(auto& i:service.get_all_cos()) {
            Produs prod = service.cauta_produs_service(i);
            p.drawRect(x,y,10,10);
            x += (rand() % 30);
            y += (rand() % 20);
        }
    }

public:
    CosDrawGUI(ServiceProduse& service): service{service} {
        service.addObserver(this);
        setAttribute(Qt::WA_DeleteOnClose);
        update();
    }

    void update() override {
        repaint();
    }
};


#endif //MAGAZIN_GUI_GUI_COS_H
