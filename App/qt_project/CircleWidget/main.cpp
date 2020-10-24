#include "mainwindow.h"
#include "circlewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    CircleWidget w;
    w.show();

    return a.exec();
}
