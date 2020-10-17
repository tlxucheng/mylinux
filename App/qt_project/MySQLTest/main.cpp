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
            qDebug() << "select failed";
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
            qDebug() << "select success";

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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    //show_data_by_qdebug();
    show_data_by_view();

    return a.exec();
    //return 0;
}
