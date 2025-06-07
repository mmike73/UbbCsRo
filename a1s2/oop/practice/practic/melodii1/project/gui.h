//
// Created by Mihai Moldovan on 18.06.2024.
//

#ifndef PROJECT_GUI_H
#define PROJECT_GUI_H
#include "my_model.h"
#include "observer.h"
#include "exception.h"
#include <QWidget>
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QSlider>
#include <QLineEdit>
#include <QPainter>
#include <QFormLayout>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>

class GUI: public QWidget, public Observer {
private:

    void init_window();
    void load_data();
    void make_connections();

    QVBoxLayout* main_ly = new QVBoxLayout;
    QHBoxLayout* main_ly_1 = new QHBoxLayout;

    MyModel* model;
    QTableView* table = new QTableView;

    QLineEdit* edit_title = new QLineEdit;
    QLineEdit* id_sel = new QLineEdit;
    QSlider* slider_rank = new QSlider{Qt::Horizontal};

    QPushButton* modifica = new QPushButton{"&Modifica"};
    QPushButton* sterge = new QPushButton{"&Sterge"};
    QPushButton* exit = new QPushButton{"&Exit"};

    Service& service;

    QGraphicsScene* gs = new QGraphicsScene;
    QGraphicsView* gv = new QGraphicsView;

    void update() override {
        model->chandeMade();
    }

public:
    GUI(Service& service): service{service} {
        service.addObserver(this);
        init_window();
        make_connections();
    };

    ~GUI() {
        service.removeObserver(this);
    }
};


#endif //PROJECT_GUI_H
