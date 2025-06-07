//
// Created by Mihai Moldovan on 18.05.2024.
//

#ifndef P1_GUI_H
#define P1_GUI_H
#include <QtWidgets/qwidget.h>
#include <QtWidgets/QApplication>

#include <QtWidgets/QPushButton>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlistwidget.h>

#include "service.h"
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

class GUI: public QWidget {
public:
    GUI(Service& service): service{service} {
        init_gui();
        load_data();
        make_connections();
    }

    void init_gui();
    void load_data();
    void make_connections();
    void change_total();

private:
    Service& service;

    QLineEdit* nume = new QLineEdit;
    QLineEdit* socket = new QLineEdit;
    QLineEdit* pret = new QLineEdit;

    QPushButton* add_placa = new QPushButton("&Adauga placa de baza");
    QPushButton* filtter_cpu_socket = new QPushButton("&Filtreaza dupa socket");

    QListWidget* lst_procesoare = new QListWidget;
    QListWidget* lst_placi = new QListWidget;

    QListWidgetItem* cpu;
    QListWidgetItem* motherboard;

    QLabel* total = new QLabel;
};


#endif //P1_GUI_H
