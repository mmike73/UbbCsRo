//
// Created by Mihai Moldovan on 19.06.2024.
//

#ifndef PROJECT_MY_MODEL_H
#define PROJECT_MY_MODEL_H
#include "service.h"
#include <QAbstractTableModel>

class MyModel: public QAbstractTableModel {
public:
    MyModel(Service& service);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;

    QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation, int role) const;
    //bool setData(const QModelIndex& index, const QVariant& value, int role) override;

    Qt::ItemFlags flags(const QModelIndex&) const override;

    void changeMade();
private:
    Service& service;
    vector<Task> tasks;
};

class ModelStatusClosed: public MyModel {
public:
    ModelStatusClosed(Service& service): service{service}, MyModel{service} {
        tasks = service.get_all_tasks();
    };
    QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const override;
private:
    Service& service;
    vector<Task> tasks;
};


#endif //PROJECT_MY_MODEL_H
