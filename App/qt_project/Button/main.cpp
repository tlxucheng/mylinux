#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    QPushButton *button = new QPushButton("Quit");
    button->show();

    return a.exec();
}
