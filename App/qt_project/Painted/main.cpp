#include "mainwindow.h"
#include <QApplication>
#include "paintedwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PaintedWidget w;
    w.show();

    return a.exec();
}
