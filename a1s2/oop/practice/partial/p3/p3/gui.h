//
// Created by Mihai Moldovan on 21.05.2024.
//

#ifndef P3_GUI_H
#define P3_GUI_H
#include <vector>
#include <iostream>
#include "domain.h"
#include "service.h"
#include "exception.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QBoxLayout>

using std::vector;

class GUI: public QWidget {
public:
    GUI(Service& service): service{service} {
        init_gui();
        load_data();
        init_connections();
    }

    QListWidget* lst = new QListWidget;

    QPushButton* detalii_elev = new QPushButton("&Detalii");
    QPushButton* sort_nume = new QPushButton("&Sorteaza dupa nume");
    QPushButton* desen_pictura = new QPushButton("&Desen + Pictura");
    QPushButton* fotografie = new QPushButton("&Fotografie");
    QPushButton* muzica = new QPushButton("&Muzica");
    QPushButton* informatica = new QPushButton("&Informatica");
    QPushButton* jurnalism = new QPushButton("&Jurnalism");

    QLineEdit* ateliere = new QLineEdit;

    QTableWidget* table = new QTableWidget(100,3);

    void init_gui();
    void load_data();
    void init_connections();

private:
    Service& service;
};


#endif //P3_GUI_H
