//
// Created by Mihai Moldovan on 22.06.2024.
//

#include "my_model.h"

MyModel::MyModel(Service& s): s{s} {
    utilaje = s.get_all();
    aparitii = s.get_tipuri();
    nr_cilindri = s.get_cilindri();
}

int MyModel::rowCount(const QModelIndex &parent) const {
    return utilaje.size();
}

int MyModel::columnCount(const QModelIndex &parent) const {
    return 5;
}

QVariant MyModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int col = index.column() + 1;
    if(role == Qt::DisplayRole) {
        string data;
        if(col == 1) {
            data = std::to_string(utilaje[row].get_id());
        } else if(col == 2) {
            data = utilaje[row].get_denumire();
        } else if(col == 3) {
            data = utilaje[row].get_tip();
        } else if(col == 4) {
            data = std::to_string(utilaje[row].get_cilindri());
        } else if(col == 5) {
            data = std::to_string(aparitii.find(utilaje[row].get_tip())->second);
        }
        return QString("%1").arg(QString::fromStdString(data));
    }
    return QVariant();
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role == Qt::DisplayRole) {
        if(orientation == Qt::Horizontal) {
            if(section == 0) {
                return QString("%1").arg("ID");
            } else if(section == 1) {
                return QString("%1").arg("Denumire");
            } else if(section == 2) {
                return QString("%1").arg("Tip");
            } else if(section == 3) {
                return QString("%1").arg("Numar cilindri");
            } else if(section == 4) {
                return QString("%1").arg("Numar utilaje de acelasi tip");
            }
        } else {
            return QString("%1").arg(section);
        }
    }
    return QVariant();
}

bool MyModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(role == Qt::EditRole) {
        int row = index.row();
        int column = index.column();
    }
}

Qt::ItemFlags MyModel::flags(const QModelIndex &)const {
    return Qt::ItemIsSelectable| Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

void MyModel::changeMade() {
    emit layoutChanged();
    utilaje = s.get_all();
    aparitii = s.get_tipuri();
}