//
// Created by Mihai Moldovan on 29.05.2024.
//

#include "models.h"


MyTableModel::MyTableModel(ServiceProduse& service): service(service) {
}
int MyTableModel::rowCount(const QModelIndex &) const {
    return service.get_all().size();
}
int MyTableModel::columnCount(const QModelIndex &) const {
    return 1;
}
QVariant MyTableModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        Produs& produs = service.get_all()[index.row()];
        string item = std::to_string(produs.get_id()) + ' ' +produs.get_nume() + " " + produs.get_tip() + " " + std::to_string(produs.get_pret()) + " " + produs.get_producator();
        return QString("%1").arg(QString::fromStdString(item));
    }
    return QVariant();
}

void MyTableModel::change_made() {
    emit layoutAboutToBeChanged();
    emit layoutChanged();
}
/*
bool setData(const QModelIndex & index, const QVariant & value, int role) {
    if(role==Qt::EditRole) {
        int row = index.row();
        int column = index.column();
        m_gridData[index.row()][index.column()] = value.toString();
        QModelIndex topLeft = createIndex(row,column);
        emit dataChanged(topLeft,topLeft);
    }
    return true;
}
*/
Qt::ItemFlags  MyTableModel::flags(const QModelIndex &) const {
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}


