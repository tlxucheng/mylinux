#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    void paintEvent(QPaintEvent *);

protected:
    void timerEvent(QTimerEvent *event);
    int m_Timeid;

private:
    double m_circle_px;
    double m_circle_py;

};

#endif // WIDGET_H
