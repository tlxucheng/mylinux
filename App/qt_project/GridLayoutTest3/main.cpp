#include "widget.h"
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    w.resize(500, 400);

    QGridLayout *layout = new QGridLayout;

    QLabel *srcIp_label = new QLabel;
    QLineEdit *srcIp_line_edit = new QLineEdit;

    QLabel *srcPort_label = new QLabel;
    QLineEdit *srcPort_line_edit = new QLineEdit;

    QLabel *destIp_label = new QLabel;
    QLineEdit *destIp_line_edit = new QLineEdit;

    QLabel *destPort_label = new QLabel;
    QLineEdit *destPort_line_edit = new QLineEdit;

    srcIp_label->setText("SrcIp");
    layout->addWidget(srcIp_label, 0,0,1,1);
    layout->addWidget(srcIp_line_edit, 0,1,1,1);

    srcPort_label->setText("SrcPort");
    layout->addWidget(srcPort_label, 0,2,1,1);
    srcPort_line_edit->setFixedWidth(50);
    layout->addWidget(srcPort_line_edit, 0,3,1,1);

    destIp_label->setText("DestIp");
    layout->addWidget(destIp_label, 1,0,1,1);
    layout->addWidget(destIp_line_edit, 1,1,1,1);

    destPort_label->setText("DestPort");
    layout->addWidget(destPort_label, 1,2,1,1);
    destPort_line_edit->setFixedWidth(50);
    layout->addWidget(destPort_line_edit, 1,3,1,1);

    layout->setRowStretch(2, 1);

    //layout->setVerticalSpacing(1);

    layout->setContentsMargins(50, 10, 50, 10);

    w.setLayout(layout);

    w.show();

    return a.exec();
}
