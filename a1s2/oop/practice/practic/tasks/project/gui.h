//
// Created by Mihai Moldovan on 19.06.2024.
//

#ifndef PROJECT_GUI_H
#define PROJECT_GUI_H
#include "service.h"
#include "my_model.h"
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QTableView>
#include "validation.h"
#include <sstream>
using std::getline;
using std::stringstream;

class GUI: public QWidget, public Observer {
private:
    Service& service;

    void init_windows();
    void load_data();
    void make_connections();

    QHBoxLayout* main_ly = new QHBoxLayout;
    QHBoxLayout* left_ly = new QHBoxLayout;

    MyModel* model;
    QTableView* table = new QTableView;

    QPushButton* add = new QPushButton{"&Adauga"};
    QPushButton* filter = new QPushButton{"&Filtreaza"};
    QPushButton* search = new QPushButton{"&Cauta"};
    QPushButton* exit = new QPushButton{"&Exit"};

    QLineEdit* id = new QLineEdit;
    QLineEdit* desc = new QLineEdit;
    QLineEdit* progr = new QLineEdit;
    QLineEdit* stare = new QLineEdit;

    void update() override {
        load_data();
    }

public:
    GUI(Service& service);

};


#endif //PROJECT_GUI_H
