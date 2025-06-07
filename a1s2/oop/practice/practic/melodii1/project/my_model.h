//
// Created by Mihai Moldovan on 18.06.2024.
//

#ifndef PROJECT_MY_MODEL_H
#define PROJECT_MY_MODEL_H
#include "service.h"
#include <QAbstractTableModel>

class MyModel: public QAbstractTableModel{
public:
    MyModel(Service& service);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;

    Qt::ItemFlags flags(const QModelIndex &) const override;

    void chandeMade();

    vector<Melodie> melodii;
    map<int,int> ranks;
    map<string,int> nr_piese;

private:
    Service& service;

};


#endif //PROJECT_MY_MODEL_H
