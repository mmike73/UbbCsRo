//
// Created by Mihai Moldovan on 22.05.2024.
//

#ifndef PRACTIC_OOP_GUI_H
#define PRACTIC_OOP_GUI_H
#include "service.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QCheckBox>



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

    QPushButton* add_item = new  QPushButton("&Adauga");
    QPushButton* exit = new  QPushButton("&Exit");

    QLineEdit* id = new QLineEdit;
    QLineEdit* content = new QLineEdit;
    QLineEdit* pid_str = new QLineEdit;
    QLineEdit* level = new QLineEdit;

    QCheckBox* info = new QCheckBox;
    QCheckBox* warning = new QCheckBox;
    QCheckBox* error = new QCheckBox;
    QCheckBox* critical = new QCheckBox;

    QTableWidget* table = new QTableWidget(0,4);

private:
    Service& service;
};


#endif //PRACTIC_OOP_GUI_H
