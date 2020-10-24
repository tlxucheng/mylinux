#include "widget.h"
#include <QDebug>
#include <QTimerEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(400, 400);
    setWindowTitle(tr("Paint Demo"));

    m_circle_px = 0;
    m_circle_py = 0;

    m_Timeid = startTimer(200);
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen     pen(Qt::red);
    QBrush brush(QColor::fromRgb(141, 121, 81));

    painter.setPen(pen);
    painter.setPen(Qt::NoPen);
    painter.setBrush(brush);

    //painter.translate(QPoint(0, 200));
    //painter.drawEllipse(QPoint(px, px*px), 10, 10);
    qDebug() << m_circle_px;
    qDebug() << m_circle_py;
    painter.drawEllipse(QPoint(m_circle_px, m_circle_py), 10, 10);

}

void Widget::timerEvent(QTimerEvent *)
{
    update();
    if(m_circle_px >= 400)
    {
        m_circle_px = 0;
    }
    m_circle_px += 10;
    m_circle_py = 4*m_circle_px - m_circle_px * m_circle_px / 100;
}

Widget::~Widget()
{

}
