//
// Created by Mihai Moldovan on 22.06.2024.
//

#ifndef PROJECT_GUI_H
#define PROJECT_GUI_H
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QFormLayout>
#include "service.h"
#include "my_model.h"

class GUI: public QWidget, public Observer {
private:
    Service& s;
    void init_window();
    void load_data();
    void make_connections();

    MyModel* model = new MyModel(s);
    QTableView* tabel = new QTableView;

    QLineEdit* denumire = new QLineEdit;
    QLineEdit* tip = new QLineEdit;
    QRadioButton* nr_cilindri_1 = new QRadioButton{"1"};
    QRadioButton* nr_cilindri_2 = new QRadioButton{"2"};
    QRadioButton* nr_cilindri_4 = new QRadioButton{"4"};
    QRadioButton* nr_cilindri_8 = new QRadioButton{"8"};

    QPushButton* del = new QPushButton{"Delete"};
    QPushButton* mod = new QPushButton{"Update"};
    QPushButton* exit = new QPushButton{"Exit"};

    QVBoxLayout* mainly = new QVBoxLayout;
    QHBoxLayout* upper = new QHBoxLayout;
    QHBoxLayout* radio = new QHBoxLayout;

    QVBoxLayout* right = new QVBoxLayout;
    QVBoxLayout* left = new QVBoxLayout;

    QGraphicsView* gv = new QGraphicsView;
    QGraphicsScene* sv = new QGraphicsScene;



    QFormLayout* form = new QFormLayout;

    vector<QGraphicsEllipseItem*> cilindri;



public:
    GUI(Service& s);
    ~GUI();

    void update() {
        load_data();
    }

};


#endif //PROJECT_GUI_H
