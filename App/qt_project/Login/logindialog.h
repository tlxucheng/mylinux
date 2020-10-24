#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
private:
    QLabel      *m_userLable;
    QLabel      *m_pwdLable;
    QLineEdit   *m_userLineEdit;
    QLineEdit   *m_pwdLineEdit;
    QPushButton *m_loginBtn;
    QPushButton *m_exitBtn;

//public slots:
private slots:
    void button_login();
    void button_close();

signals:
    void signal_username(QString);
};

#endif // LOGINDIALOG_H
