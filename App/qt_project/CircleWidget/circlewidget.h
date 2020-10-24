#ifndef CIRCLEWIDGET_H
#define CIRCLEWIDGET_H

#include <QFrame>
#include <QTimer>

class CircleWidget:public QFrame
{
    Q_OBJECT
public:
    CircleWidget(QWidget *parent);
    ~CircleWidget();
private:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
private:
    int m_timerId;
    int m_times;

};

#endif // CIRCLEWIDGET_H
