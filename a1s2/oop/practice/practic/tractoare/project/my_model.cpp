//
// Created by Mihai Moldovan on 14.06.2024.
//

#include "my_model.h"

MyTableModel::MyTableModel(Service& service): service{service} {
    tractoare = service.get_all_tractoare();
    count = service.get_all_types();
};

int MyTableModel::rowCount(const QModelIndex &) const {
    return tractoare.size();
}

int MyTableModel::columnCount(const QModelIndex &) const {
    return 5;
}

QVariant MyTableModel::data(const QModelIndex &index, int role) const {
    int column = index.column() + 1;
    int row = index.row();
    if(role == Qt::DisplayRole) {
        string data;
        if(column == 1) {
            data = std::to_string(tractoare[row].get_id());
        } else if(column == 2) {
            data = tractoare[row].get_denumire();
        } else if(column == 3) {
            data = tractoare[row].get_tip();
        } else if(column == 4) {
            data = std::to_string(tractoare[row].get_nr_roti());
        } else if(column == 5) {
            data = std::to_string(count.find(tractoare[row].get_tip())->second);
        }
        return QString("%1").arg(QString::fromStdString(data));
    }
    if(role == Qt::BackgroundRole) {
        if(/*column == 1 &&*/ tractoare[row].get_tip() == tip_selectat) {
            QBrush bg(Qt::red);
            return bg;
        }
    }
    return QVariant();
}

QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role == Qt::DisplayRole) {
        if(orientation == Qt::Horizontal) {
            if(section == 0) {
                return QString("%1").arg("ID");
            } else if(section == 1) {
                return QString("%1").arg("Denumire");
            } else if(section == 2) {
                return QString("%1").arg("Tip");
            } else if(section == 3) {
                return QString("%1").arg("Numar roti");
            } else if(section == 4) {
                return QString("%1").arg("Numar tractoare de acelasi tip");
            }
        } else {
            return QString("%1").arg(section);
        }
    }
    return QVariant();
}

//
bool MyTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(role == Qt::EditRole) {
        int row = index.row();
        int column = index.column();
    }
}
//

Qt::ItemFlags MyTableModel::flags(const QModelIndex &)const {
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

void MyTableModel::changeMade() {
    tractoare = service.get_all_tractoare();
    count = service.get_all_types();
    emit layoutAboutToBeChanged();
    emit layoutChanged();
}