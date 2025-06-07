//
// Created by Mihai Moldovan on 22.06.2024.
//

#include "gui.h"

GUI::GUI(Service& s): s{s} {
    s.addObserver(this);
    init_window();
    load_data();
    make_connections();
}

GUI::~GUI() {
    s.removeObserver(this);
}

void GUI::init_window() {
    setLayout(mainly);

    tabel->setModel(model);

    upper->addWidget(tabel);
    form->addRow("&Denumire",denumire);
    form->addRow("&Sterge",tip);

    radio->addWidget(nr_cilindri_1);
    radio->addWidget(nr_cilindri_2);
    radio->addWidget(nr_cilindri_4);
    radio->addWidget(nr_cilindri_8);

    form->addRow("Cilindri",radio);
    form->addRow(mod);
    form->addRow(del);
    form->addRow(exit);

    upper->addLayout(form);

    mainly->addLayout(upper);
    mainly->addWidget(gv);

    gv->setFixedSize(1000,400);
    sv->setSceneRect(0,0,999,499);
    gv->setScene(sv);

}
void GUI::load_data() {
    model->changeMade();
    int c[] = {1,2,4,8};
    cilindri.clear();
    for(int i = 0 ; i <= 3;++i) {
        float x = model->nr_cilindri.find(c[i])->second * 10;
        //float y = c[i] * 10;
        QGraphicsEllipseItem* cil = new QGraphicsEllipseItem{15,10,x,x};
        cil->setBrush(Qt::red);
        cilindri.push_back(cil);
        cil->setFlags(QGraphicsEllipseItem::ItemIsSelectable | QGraphicsEllipseItem::ItemIsFocusable);

    }
    int dist = sv->width()/6;
    int start = dist;
    for(auto& i:cilindri) {
        i->setPos(start,sv->height() / 2);
        sv->addItem(i);
        start += dist;
    }


}
void GUI::make_connections() {
    QObject::connect(exit,&QPushButton::clicked,[&]() {
        close();
    });
    QObject::connect(mod,&QPushButton::clicked,[&]() {
        if(tabel->selectionModel()->selectedIndexes().size() != 0) {
            string denumire_nooua = denumire->text().toStdString();
            string tip_nou = tip->text().toStdString();
            int row = tabel->selectionModel()->selectedIndexes()[0].row();
            int id_selectat = stoi(model->data(model->index(row, 0)).toString().toStdString());

            Utilaj u = s.cauta_utilaj(id_selectat);
            try {
                s.mdoifica_denumire_utilaj(u.get_id(), denumire_nooua);
            } catch (Exception& e) {
                std::cout << e.what();
            }
            try {
                s.modifica_tip_utilaj(u.get_id(), tip_nou);
            } catch (Exception& e) {
                std::cout << e.what();
            }
            load_data();
        }
    });
    QObject::connect(del,&QPushButton::clicked,[&]() {
        if(tabel->selectionModel()->selectedIndexes().size() != 0) {
            int row = tabel->selectionModel()->selectedIndexes()[0].row();
            int id_selectat = stoi(model->data(model->index(row, 0)).toString().toStdString());
            s.sterge_utilaj(id_selectat);
            load_data();
        }

    });
    QObject::connect(tabel->selectionModel(),&QItemSelectionModel::selectionChanged,[&]() {
        if(tabel->selectionModel()->selectedIndexes().size() != 0) {
            int row = tabel->selectionModel()->selectedIndexes()[0].row();
            int id_selectat = stoi(model->data(model->index(row,0)).toString().toStdString());

            Utilaj t = s.cauta_utilaj(id_selectat);

            denumire->setText(QString::fromStdString(t.get_denumire()));
            tip->setText(QString::fromStdString(t.get_tip()));
            int nr_cil = t.get_cilindri();
            if(nr_cil == 1) {
                nr_cilindri_1->setAcceptDrops(true);
            } else if(nr_cil == 2) {
                //nr_cilindri_2->setEnabled();
            } else if(nr_cil == 4) {
                nr_cilindri_4->setAcceptDrops(true);
            } else if(nr_cil == 8) {
                //nr_cilindri_8->setEnabled();
            }
        }
    });
}
