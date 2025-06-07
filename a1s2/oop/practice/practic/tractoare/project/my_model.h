//
// Created by Mihai Moldovan on 14.06.2024.
//

#ifndef PROJECT_MY_MODEL_H
#define PROJECT_MY_MODEL_H
#include <QAbstractTableModel>
#include <QTableView>
#include <string>
#include "service.h"
using std::string;

class MyTableModel: public QAbstractTableModel {
public:
    MyTableModel(Service& service);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    Qt::ItemFlags flags(const QModelIndex &)const;

    void changeMade();

    void set_tip_selectat(string tip_nou) {
        tip_selectat = tip_nou;
    }
private:
    Service& service;
    vector<Tractor> tractoare;
    map<string,int> count;
    string tip_selectat;
};


#endif //PROJECT_MY_MODEL_H
