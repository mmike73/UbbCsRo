//
// Created by Mihai Moldovan on 22.06.2024.
//

#ifndef PROJECT_MY_MODEL_H
#define PROJECT_MY_MODEL_H
#include <QAbstractTableModel>
#include "service.h"

class MyModel: public QAbstractTableModel {
public:
    MyModel(Service& s);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    Qt::ItemFlags flags(const QModelIndex &)const;

    void changeMade();

    map<int,int> nr_cilindri;
private:
    Service& s;
    vector<Utilaj> utilaje;
    map<string,int> aparitii;

};


#endif //PROJECT_MY_MODEL_H
