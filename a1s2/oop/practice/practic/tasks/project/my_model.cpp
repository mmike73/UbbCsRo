//
// Created by Mihai Moldovan on 19.06.2024.
//

#include "my_model.h"

MyModel::MyModel(Service& service): service{service} {
    tasks = service.get_all_tasks();
}

int MyModel::rowCount(const QModelIndex& index) const {
    return tasks.size();
}
int MyModel::columnCount(const QModelIndex& index) const {
    return 4;
}

QVariant MyModel::data(const QModelIndex& index, int role) const {
    int col = index.column() + 1;
    int row = index.row();
    if(role == Qt::DisplayRole) {
        string data;
        if(col == 1) {
            data = std::to_string(tasks[row].get_id());
        } else if( col == 2) {
            data = tasks[row].get_descriere();
        } else if( col == 3) {
            vector<string> programmers = tasks[row].get_programatori();
            for(auto& prog:programmers) {
                data += prog + '\n';
            }
        } else if( col == 4) {
            data = tasks[row].get_stare();
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
            } else if( section == 1) {
                return QString("%1").arg("Descriere");
            } else if( section == 2) {
                return QString("%1").arg("Programatori");
            } else if( section == 3) {
                return QString("%1").arg("Stare");
            }
        }
    }
    return QVariant();
}

Qt::ItemFlags MyModel::flags(const QModelIndex&) const {
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

void MyModel::changeMade() {
    tasks = service.get_all_tasks();
    emit layoutChanged();
}

QVariant ModelStatusClosed::data(const QModelIndex& index, int role) const {
    int col = index.column() + 1;
    int row = index.row();
    if(role == Qt::DisplayRole) {
        string data;
        if(col == 1) {
            data = std::to_string(tasks[row].get_id());
        } else if( col == 2) {
            data = tasks[row].get_descriere();
        } else if( col == 3) {
            vector<string> programmers = tasks[row].get_programatori();
            for(auto& prog:programmers) {
                data += prog + '\n';
            }
        } else if( col == 4) {
            data = tasks[row].get_stare();
        }
        return QString("%1").arg(QString::fromStdString(data));
    }
    return QVariant();
}
