//
// Created by Mihai Moldovan on 22.05.2024.
//

#include "gui.h"


void GUI::init_gui() {
    QHBoxLayout* mainly = new QHBoxLayout;
    setLayout(mainly);
    QVBoxLayout* rightly = new QVBoxLayout;
    QVBoxLayout* leftly = new QVBoxLayout;

    leftly->addWidget(table);

    auto formly = new QFormLayout;
    formly->addRow("ID",id);
    formly->addRow("content",content);
    formly->addRow("PID",pid_str);
    formly->addRow("level",level);

    rightly->addLayout(formly);
    rightly->addWidget(add_item);
    rightly->addWidget(exit);

    mainly->addLayout(leftly);
    mainly->addLayout(rightly);
}

void GUI::load_data() {
    table->clear();
    vector<Log> logs = service.get_all();
    table->setRowCount(0);
    int row = 0,col = 0;
    for(auto& log:logs) {
        table->insertRow(row);
        QTableWidgetItem* item1 = new QTableWidgetItem(QString::fromStdString(log.get_id()));
        table->setItem(row,col,item1);
        col++;
        QTableWidgetItem* item2 = new QTableWidgetItem(QString::fromStdString(log.get_content()));
        table->setItem(row,col,item2);
        col++;
        QTableWidgetItem* item3 = new QTableWidgetItem(QString::fromStdString(std::to_string(log.get_PID())));
        table->setItem(row,col,item3);
        col++;
        QTableWidgetItem* item4 = new QTableWidgetItem(QString::fromStdString(log.get_level()));
        table->setItem(row,col,item4);
        if(log.get_level() == "info") {
            item1->setBackground(QBrush{Qt::green});
            item2->setBackground(QBrush{Qt::green});
            item3->setBackground(QBrush{Qt::green});
            item4->setBackground(QBrush{Qt::green});
        }
        if(log.get_level() == "warning") {
            item1->setBackground(QBrush{Qt::yellow});
            item2->setBackground(QBrush{Qt::yellow});
            item3->setBackground(QBrush{Qt::yellow});
            item4->setBackground(QBrush{Qt::yellow});
        }
        if(log.get_level() == "error") {
            item1->setBackground(QBrush{Qt::red});
            item2->setBackground(QBrush{Qt::red});
            item3->setBackground(QBrush{Qt::red});
            item4->setBackground(QBrush{Qt::red});
        }
        if(log.get_level() == "critical") {
            item1->setBackground(QBrush{Qt::red});
            item2->setBackground(QBrush{Qt::red});
            item3->setBackground(QBrush{Qt::red});
            item4->setBackground(QBrush{Qt::red});
        }
        col = 0;
        row++;
    }

}
void GUI::init_connections() {
    QObject::connect(add_item,&QPushButton::clicked,[&]() {
        string id_log = id->text().toStdString();
        string content_log = this->content->text().toStdString();
        string level_log = this->level->text().toStdString();
        bool ok;
        int pid_log = this->pid_str->text().toInt(&ok);
        if(ok) {
            Log l(id_log,content_log,pid_log,level_log);
            //try {
            service.add_log(l);
            //} catch(Exception& e) {
            //    std::cerr << e.what();
            //}
            load_data();
        }

    });

    QObject::connect(exit,&QPushButton::clicked,[]() {
        std::exit(0);
    });
}