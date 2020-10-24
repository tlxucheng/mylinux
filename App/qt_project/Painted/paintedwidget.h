#ifndef PAINTEDWIDGET_H
#define PAINTEDWIDGET_H

#include <QWidget>

class QPainter;

class PaintedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintedWidget(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:

};

#endif // PAINTEDWIDGET_H
