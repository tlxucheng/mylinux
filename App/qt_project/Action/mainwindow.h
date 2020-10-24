#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Action;
class QLabel;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void open();
private:
    QAction *m_openAction;
    QLabel  *m_msgLabel;
};

#endif // MAINWINDOW_H
