#include "circlewidget.h"

#include<QPainter>
CircleWidget::CircleWidget(QWidget *parent):QFrame(parent)
{
    m_timerId=startTimer(1000);
    m_times=0;
}
CircleWidget::~CircleWidget()
{

}
void CircleWidget::paintEvent(QPaintEvent *event)
{
        QPainter painter(this);
        int width=this->width();
        int height=this->height();
        painter.setPen(Qt::NoPen);
        if(m_times==0)
        {
         QBrush brush(QColor(0xFF,0xFF,0xFF));
         painter.setBrush(brush);
         m_times=1;
        }
        else
        {
            QBrush brush(QColor(0x88,0x00,0xFF));
            painter.setBrush(brush);
           m_times=0;
        }
        m_times++;
        if(m_times==1)
        {
        m_times=0;
        }

         painter.drawEllipse(0,0,40,40);


}
void CircleWidget::timerEvent(QTimerEvent *event)
{

        update();

}
