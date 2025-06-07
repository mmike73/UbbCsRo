//
// Created by Mihai Moldovan on 18.06.2024.
//

#include "my_model.h"

MyModel::MyModel(Service& service):
    service{service},
    melodii{service.get_all_melodii()},
    ranks{service.get_all_ranks()},
    nr_piese{service.get_all_artists()} {};

int MyModel::rowCount(const QModelIndex &) const {
    return melodii.size();
}

int MyModel::columnCount(const QModelIndex&) const {
    return 5;
}

QVariant MyModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int column = index.column() + 1;
    if(role == Qt::DisplayRole) {
        string data;
        if(column == 1) {
            data = std::to_string(melodii[row].get_id());
        } else if(column == 2) {
            data = melodii[row].get_titlu();
        } else if(column == 3) {
            data = melodii[row].get_artist();
        } else if(column == 4) {
            data = std::to_string(melodii[row].get_rank());
        } else if(column == 5) {
            data = std::to_string(ranks.find(melodii[row].get_rank())->second);
        } else if(column == 6) {
            data = std::to_string(nr_piese.find(melodii[row].get_artist())->second);
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
                return QString("%1").arg("Titlu");
            } else if(section == 2) {
                return QString("%1").arg("Artist");
            } else if(section == 3) {
                return QString("%1").arg("Rank");
            } else if(section == 4) {
                return QString("%1").arg("Nr piese cu acelasi rank");
            }
        }
    }
    return QVariant();
}

bool MyModel::setData(const QModelIndex& index, const QVariant& value, int role) {

}

Qt::ItemFlags MyModel::flags(const QModelIndex &) const {
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

void MyModel::chandeMade() {
    melodii = service.get_all_melodii();
    ranks = service.get_all_ranks();
    nr_piese = service.get_all_artists();
    emit layoutAboutToBeChanged();
    emit layoutChanged();
}
