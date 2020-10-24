#include "paintedwidget.h"
#include <QPainter>

PaintedWidget::PaintedWidget(QWidget *parent) :
    QWidget(parent)
{
    resize(400, 400);
    setWindowTitle(tr("Paint Demo"));
}

void PaintedWidget::paintEvent(QPaintEvent *)
{
    static int px = 0;

    QPainter painter(this);
    QPen     pen(Qt::red);
    //QBrush   brush(Qt::cyan);
    QBrush brush(QColor::fromRgb(141, 121, 81));

    //pen.setWidth(3);
    //brush.setStyle(Qt::Dense1Pattern);

    painter.setPen(pen);

    painter.setPen(Qt::NoPen);

    painter.setBrush(brush);

    painter.drawRect(0, 0, 100, 100);

    brush.setColor(QColor::fromRgb(171, 165, 141));
    painter.setBrush(brush);
    painter.drawRect(100, 0, 100, 100);

    qDebug("px: %d", px);

    painter.drawEllipse(QPoint(200, 200), 10, 10);
}
