#include "widget.h"
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    QHBoxLayout *h_layout = new QHBoxLayout;
    QVBoxLayout *v_layout = new QVBoxLayout;

    QLabel *srcIp_label = new QLabel;
    QLineEdit *srcIP_line_edit = new QLineEdit;

    QLabel *srcPort_label = new QLabel;
    QLineEdit *srcPort_line_edit = new QLineEdit;

    srcIp_label->setText("srcIp");
    h_layout->addWidget(srcIp_label);
    h_layout->addWidget(srcIP_line_edit);

    h_layout->addSpacing(50);

    srcPort_label->setText("srcPort");
    h_layout->addWidget(srcPort_label);
    h_layout->addWidget(srcPort_line_edit);

    QHBoxLayout *h_layout2 = new QHBoxLayout;

    QLabel *destIp_label = new QLabel;
    QLineEdit *destIP_line_edit = new QLineEdit;

    destIp_label->setText("destIp");
    h_layout2->addWidget(destIp_label);
    h_layout2->addWidget(destIP_line_edit);

    QLabel *destPort_label = new QLabel;
    QLineEdit *destPort_line_edit = new QLineEdit;

    h_layout2->addSpacing(50);

    destPort_label->setText("destPort");
    h_layout2->addWidget(destPort_label);
    h_layout2->addWidget(destPort_line_edit);

    v_layout->addLayout(h_layout);
    v_layout->addLayout(h_layout2);

    w.setLayout(v_layout);
    w.show();

    return a.exec();
}
