//
// Created by Mihai Moldovan on 14.06.2024.
//

#ifndef PROJECT_GUI_H
#define PROJECT_GUI_H
#include "service.h"
#include "exception.h"
#include "observer.h"
#include "my_model.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QFormLayout>
#include <QMessageBox>
#include <QGraphicsView>
#include <exception>

class GUI: public QWidget, public Observer {
private:
    Service& service;

    MyTableModel* model;
    QTableView* table = new QTableView;

    QVBoxLayout* main_layout = new QVBoxLayout;
    QHBoxLayout* left_right_ly = new QHBoxLayout;

    QVBoxLayout* left_ly = new QVBoxLayout;
    QVBoxLayout* mid_ly = new QVBoxLayout;
    QVBoxLayout* right_ly = new QVBoxLayout;

    QLineEdit* id = new QLineEdit();
    QLineEdit* denumire = new QLineEdit;
    QLineEdit* tip = new QLineEdit;
    QLineEdit* nr_roti = new QLineEdit;

    QPushButton* adaugare = new QPushButton("&Adaugare");
    QPushButton* exit = new QPushButton("&Exit");

    QComboBox* tipuri_tr = new QComboBox;

    QPainter* desen = new QPainter;

    QGraphicsView* gview = new QGraphicsView;
    QGraphicsScene* gscene = new QGraphicsScene;

    QGraphicsEllipseItem* ball;

    void init_window();
    void make_connections();
    void load_data();

    void update() override {
        model->changeMade();
    }

public:
    GUI(Service& service): service{service} {
        service.addObserver(this);
        init_window();
        make_connections();
        load_data();
    };

    ~GUI() {
        service.removeObserver(this);
    }
};

class Circle: public QGraphicsEllipseItem {
public:
    Circle() {
        QGraphicsEllipseItem(15,10,20,20);
        this->setBrush(Qt::red);
    }
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        std::cout << "Mousepress\n";
        QGraphicsEllipseItem::mousePressEvent(event);
    }

};

#endif //PROJECT_GUI_H
