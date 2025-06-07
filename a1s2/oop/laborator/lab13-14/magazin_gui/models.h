//
// Created by Mihai Moldovan on 29.05.2024.
//

#ifndef MAGAZIN_GUI_MODELS_H
#define MAGAZIN_GUI_MODELS_H
#include <QAbstractTableModel>
#include <QTableView>
#include <QListView>
#include "domain.h"
#include "service.h"
#include <vector>
#include <string>
using std::vector;
using std::string;

class MyTableModel: public QAbstractTableModel {
public:
    MyTableModel(ServiceProduse& service);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    //bool setData(const QModelIndex & index, const QVariant & value, int role);
    Qt::ItemFlags flags(const QModelIndex &) const;
    void change_made();
    ServiceProduse& service;
};


#endif //MAGAZIN_GUI_MODELS_H
