#include "widget.h"
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QSize>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    w.resize(800, 600);
    //w.setFixedSize(w.width(), w.height());
//    w.setWindowFlags(Qt::WindowTitleHint);
//    w.setWindowFlags(w.windowFlags()&~Qt::WindowMaximizeButtonHint);
//    w.setWindowFlags(Qt::WindowMaximizeButtonHint);

    w.setWindowFlags(Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);

    QPushButton *pb1 = NULL;
    QPushButton *pb2 = NULL;
    QPushButton *pb3 = NULL;
    QGridLayout *pg = NULL;

    pb1 = new QPushButton("AAA");
    pb2 = new QPushButton("BBB");
    pb3 = new QPushButton("CCC");
    pg = new QGridLayout;

    pb1->setFixedHeight(100);

    pg->setVerticalSpacing(50);      /* 设置垂直间距 */
    pg->setHorizontalSpacing(100);   /* 设置水平间距 */

    pg->addWidget(pb1, 0, 0, 1, 1);
    pg->addWidget(pb2, 0, 1, 1, 1);
    pg->addWidget(pb3, 1, 0, 1, 1);

    w.setLayout(pg);
    //pg->setRowMinimumHeight(1,50);

    w.show();

    return a.exec();
}
