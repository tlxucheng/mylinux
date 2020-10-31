#include "widget.h"
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

//    w.resize(800, 600);
    //QLabel *pImageLabel = new QLabel;
    QLineEdit *pUserLineEdit = new QLineEdit;
    QLineEdit *pPasswordLineEdit = new QLineEdit;
    QCheckBox *pRememberCheckBox = new QCheckBox;
    QCheckBox *pAutoLoginCheckBox = new QCheckBox;
    QPushButton *pLoginButton = new QPushButton;
    QPushButton *pRegisterButton = new QPushButton;
    QPushButton *pForgotButton = new QPushButton;

    pLoginButton->setFixedHeight(30);
    pUserLineEdit->setFixedWidth(200);

//    设置头像
//    QPixmap pixmap(":/Images/logo");
//    pImageLabel->setFixedSize(90, 90);
//    pImageLabel->setPixmap(pixmap);
//    pImageLabel->setScaledContents(true);

    // 设置文本
    pUserLineEdit->setPlaceholderText(QStringLiteral("QQ号码/手机/邮箱"));
    pPasswordLineEdit->setPlaceholderText(QStringLiteral("密码"));
    pPasswordLineEdit->setEchoMode(QLineEdit::Password);
    pRememberCheckBox->setText(QStringLiteral("记住密码"));
    pAutoLoginCheckBox->setText(QStringLiteral("自动登录"));
    pLoginButton->setText(QStringLiteral("登录"));
    pRegisterButton->setText(QStringLiteral("注册账号"));
    pForgotButton->setText(QStringLiteral("找回密码"));

    QGridLayout *pLayout = new QGridLayout();
    // 头像 第0行，第0列开始，占3行1列
//    pLayout->addWidget(pImageLabel, 0, 0, 3, 1);
    // 用户名输入框 第0行，第1列开始，占1行2列
    pLayout->addWidget(pUserLineEdit, 0, 1, 1, 2);
    pLayout->addWidget(pRegisterButton, 0, 4);
    // 密码输入框 第1行，第1列开始，占1行2列
    pLayout->addWidget(pPasswordLineEdit, 1, 1, 1, 2);
    pLayout->addWidget(pForgotButton, 1, 4);
    // 记住密码 第2行，第1列开始，占1行1列 水平居左 垂直居中
    pLayout->addWidget(pRememberCheckBox, 2, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    // 自动登录 第2行，第2列开始，占1行1列 水平居右 垂直居中
    pLayout->addWidget(pAutoLoginCheckBox, 2, 2, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
    // 登录按钮 第3行，第1列开始，占1行2列
    pLayout->addWidget(pLoginButton, 3, 1, 1, 2);
    // 设置水平间距
    pLayout->setHorizontalSpacing(10);
    // 设置垂直间距
    pLayout->setVerticalSpacing(10);
    // 设置外间距
    pLayout->setContentsMargins(10, 10, 10, 10);
    //setLayout(pLayout);

    w.setLayout(pLayout);
    w.show();

    return a.exec();
}
