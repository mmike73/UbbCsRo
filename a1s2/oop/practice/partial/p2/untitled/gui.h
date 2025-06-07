//
// Created by Mihai Moldovan on 20.05.2024.
//

#ifndef UNTITLED_GUI_H
#define UNTITLED_GUI_H
#include <vector>
#include <string>
#include "domain.h"
#include "service.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qwidget.h> // pentru qwidget.h
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QFormLayout>

using std::vector;

class GUI: public QWidget {
public:

    GUI(Service& service): service{service} {
        init_gui();
        load_data();
        init_connections();
    }

    void init_gui();
    void load_data();
    void init_connections();

    QListWidget* lst = new QListWidget;

    QPushButton* btnDel = new QPushButton("&Sterge");
    QPushButton* btnFilterS = new QPushButton("&Filtreaza dupa suprafata");
    QPushButton* btnFilterP = new QPushButton("&Filtreaza dupa pret");

    QLineEdit* smin = new QLineEdit();
    QLineEdit* smax = new QLineEdit();
    QLineEdit* pmin = new QLineEdit();
    QLineEdit* pmax = new QLineEdit();

    QListWidgetItem* apartament;
private:
    Service& service;
};


#endif //UNTITLED_GUI_H
