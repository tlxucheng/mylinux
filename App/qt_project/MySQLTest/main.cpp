#include "mainwindow.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QMessageBox>
#include <QSqlRecord>
#include <QDebug>
#include <QObject>
#include <QSqlError>
#include <QTableView>
#include <QAbstractItemView>
#include <QHeaderView>
#include <QSqlRecord>

bool connect_mysql(const QString &dbName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    //db.setHostName("192.168.0.107");
    db.setHostName("localhost");
    db.setDatabaseName(dbName);
    db.setUserName("root");
    //db.setPassword("123456");
    if(!db.open())
    {
        QMessageBox::critical(0, QObject::tr("Database Error"), db.lastError().text());
        return false;
    }

    qDebug() << "mysql connect success";

    return true;
}

void show_data_by_qdebug()
{
    if(connect_mysql("emicall_cc_running"))
    {
        QSqlTableModel model;
        model.setTable("yunzhi_nursing");
        //model.setFilter(QString("cc_number = '%1'").arg("cc_pc_101_1000_000148ec_1598949284_389279533"));
        //model.setFilter("id > 0");
        if(model.select())
        {
            for(int i = 0; i < model.rowCount(); ++i)
            {
                QSqlRecord record = model.record(i);
                int project_number = record.value("project_number").toInt();
                qDebug() << "project_number: " << project_number;
            }
        }
        else
        {
            qDebug() << "select failed!";
        }
    }
}

void show_data_by_view()
{
    if(connect_mysql("test_db"))
    {
        QSqlTableModel *model = new QSqlTableModel;
        model->setTable("yunzhi_nursing");
        //model.setFilter(QString("cc_number = '%1'").arg("cc_pc_101_1000_000148ec_1598949284_389279533"));
        //model.setFilter("id > 0");
        model->setSort(1, Qt::AscendingOrder);
        //model->setHeaderData(1, Qt::Horizontal, "id");
        //model->setHeaderData(2, Qt::Horizontal, "api_push_data");
        if(model->select())
        {
            qDebug() << "select success!";

            QTableView *view = new QTableView;

            view->setModel(model);
            view->setSelectionMode(QAbstractItemView::SingleSelection);
            view->setSelectionBehavior(QAbstractItemView::SelectRows);
            view->resizeColumnsToContents();
            view->setEditTriggers(QAbstractItemView::NoEditTriggers);

            QHeaderView *header = view->horizontalHeader();
            header->setStretchLastSection(true);

            view->show();
        }
        else
        {
            qDebug() << "select failed";
        }
    }
}

void insert_data()
{
    if(connect_mysql("test_db"))
    {
        QSqlTableModel model;
        model.setTable("yunzhi_nursing");
        int row = 0;
        model.insertRows(row, 1);
        model.setData(model.index(row, 1), 3);
        model.setData(model.index(row, 2), 300);
        model.setData(model.index(row, 3), "2020-10-23");
        model.setData(model.index(row, 4), "16:30:00");
        model.setData(model.index(row, 5), "");
        model.setData(model.index(row, 6), 1602163888);
        model.setData(model.index(row, 7), 1602163888);

        model.submitAll();
    }
    else
    {
        qDebug() << "insert failed";
    }
}

void insert_data2()
{
    if(connect_mysql("test_db"))
    {
        QSqlTableModel model;
        model.setTable("yunzhi_nursing");
        QSqlRecord record = model.record();
        record.setValue("project_type", 3);
        record.setValue("project_number", 120);
        record.setValue("project_date", "2020-10-24");
        record.setValue("project_time", "01:29:00");

        model.insertRecord(4, record);
        model.submitAll();
    }
    else
    {
        qDebug() << "insert failed";
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    //show_data_by_qdebug();
    qDebug() << "before insert";
    //insert_data2();
    show_data_by_view();
    qDebug() << "after insert";

    return a.exec();
    //return 0;
}
