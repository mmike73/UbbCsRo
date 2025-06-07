//
// Created by Mihai Moldovan on 10.05.2024.
//

#ifndef MAGAZIN_GUI_GUI_H
#define MAGAZIN_GUI_GUI_H
#include "service.h"
#include <QtWidgets/qwidget.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/QPushButton>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <qmessagebox.h>
#include <vector>
#include <string>
#include "exception.h"
#include "domain.h"

class GUI: public QWidget {
public:
    GUI(ServiceProduse &service_produs) : service{service_produs} {
        init_gui();
        load_data();
        init_connect();
    }

    //friend class GUI_COS;

    //forms
    QLineEdit* id_pr = new QLineEdit;
    QLineEdit* nume_pr = new QLineEdit;
    QLineEdit* tip_pr = new QLineEdit;
    QLineEdit* pret_pr = new QLineEdit;
    QLineEdit* producator_pr = new QLineEdit;

    //lista
    QListWidget* lst = new QListWidget;

    //butoane
    QPushButton* btnAdd = new QPushButton("&Adauga");
    QPushButton* btnDel = new QPushButton("&Sterge");
    QPushButton* btnMod = new QPushButton("&Modifica");
    QPushButton* btnSearchId = new QPushButton("&Cauta ID");
    QPushButton* btnExit = new QPushButton("&Exit");
    QPushButton* btnSortByName = new QPushButton("&Sorteaza dupa nume");
    QPushButton* btnSortByPrice = new QPushButton("&Sorteaza dupa pret");
    QPushButton* btnSortByNamePrice = new QPushButton("&Sorteaza dupa pret si nume");
    QPushButton* btnFilterByName = new QPushButton("&Filtreaza dupa nume");
    QPushButton* btnFilterByType = new QPushButton("&Filtreaza dupa tip");
    QPushButton* btnFilterByPrice = new QPushButton("&Filtreaza dupa pret");
    QPushButton* btnUndo = new QPushButton("&Undo");

    QVBoxLayout* btnLyCategorii = new QVBoxLayout{};

    std::vector<QPushButton*> categorii;

private:
    ServiceProduse& service;

    void load_buttons();
    int how_manny(QPushButton* buton);
    void init_gui();
    void load_data();
    void init_connect();
    };

class GUI_COS: public QWidget{
public:
    GUI_COS(ServiceProduse& service): service{service} {
        init_window();
        load_data();
        init_connect();
    }

    QListWidget* lst = new QListWidget;

    QLineEdit* id_pr = new QLineEdit;
    QLineEdit* nume_fisier = new QLineEdit;

    QPushButton* btnAddCos = new QPushButton("&Adauga in cos");
    QPushButton* btnRmCos = new QPushButton("&Sterge din cos");
    QPushButton* btnSaveCos = new QPushButton("&Salveaza cos");
    QPushButton* btnGolesteCos = new QPushButton("&Goleste cos");


private:
    ServiceProduse& service;
    void init_window();
    void load_data();
    void init_connect();
};


#endif //MAGAZIN_GUI_GUI_H
