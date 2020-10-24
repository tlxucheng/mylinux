#include "logindialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent)
{
    m_userLable = new QLabel(this);
    m_userLable->move(70,80);
    m_userLable->setText("用户名");
    m_userLineEdit = new QLineEdit(this);
    m_userLineEdit->move(140,80);
    m_userLineEdit->setPlaceholderText("请输入用户名");

    m_pwdLable = new QLabel(this);
    m_pwdLable->move(70,130);
    m_pwdLable->setText("密码");
    m_pwdLineEdit = new QLineEdit(this);
    m_pwdLineEdit->move(140,130);
    m_pwdLineEdit->setPlaceholderText("请输入密码");

    m_loginBtn = new QPushButton(this);
    m_loginBtn->move(70,200);
    m_loginBtn->setText("登录");

    m_exitBtn = new QPushButton(this);
    m_exitBtn->move(220,200);
    m_exitBtn->setText("退出");

    connect(m_loginBtn, SIGNAL(clicked(bool)), this, SLOT(button_login()));
    connect(m_exitBtn,  SIGNAL(clicked(bool)), this, SLOT(button_close()));
    //connect(m_loginBtn, &QPushButton::clicked, this, &LoginDialog::login);
    //connect(m_exitBtn, &QPushButton::clicked, this, &LoginDialog::button_close);
}

LoginDialog::~LoginDialog()
{

}

void LoginDialog::button_login()
{
    if(m_userLineEdit->text().trimmed() == "quest"
       && m_pwdLineEdit->text().trimmed() == "123")
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this, "警告", "用户名或者密码错误", QMessageBox::Yes);
        m_userLineEdit->clear();
        m_pwdLineEdit->clear();
        m_userLineEdit->setFocus();
    }
}

/* 如果写成 void LoginDialog::close()， 会crash */
void LoginDialog::button_close()
{
    this->close();
    exit(0);
}
