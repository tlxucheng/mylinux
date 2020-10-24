#include "mainwindow.h"
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QKeySequence>
#include <QToolBar>
#include <QMessageBox>
#include <QLabel>
#include <QStatusBar>
#include <QString>
#include <QFileDialog>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_openAction = new QAction(tr("&Open"), this);
    m_openAction->setShortcut(QKeySequence::Open);
    m_openAction->setStatusTip(tr("Open a file."));
    m_openAction->setIcon(QIcon(":/Open.png"));

    connect(m_openAction, SIGNAL(triggered()), this, SLOT(open()));

    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(m_openAction);
    QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar->addAction(m_openAction);

    m_msgLabel = new QLabel;
    m_msgLabel->setMinimumSize(m_msgLabel->sizeHint());
    m_msgLabel->setAlignment(Qt::AlignHCenter);
    //statusBar()->addWidget(m_msgLabel);
    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
}

MainWindow::~MainWindow()
{

}

void MainWindow::open()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg *.png)"));
    if(0 == path.length())
    {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files"));
    }
    else
    {
        QMessageBox::information(NULL, tr("Path"), tr("You selected") + path);
    }

    QColor color = QColorDialog::getColor(Qt::white, this);
    QString msg = QString("r: %1, g: %2, b: %3").arg(QString::number(color.red()),
                                                     QString::number(color.green()), QString::number(color.blue()));
    QMessageBox::information(NULL, "Select color", msg);

}
