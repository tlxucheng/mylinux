#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("UserInfo"));
   //-----------左侧--------
   UserNameLabel = new QLabel(tr("用户名："));
   UserNameLineEdit = new QLineEdit;
   NameLabel = new QLabel(tr("姓名："));
   NameLineEdit = new QLineEdit;
   SexLabel = new QLabel(tr("性别："));
   SexComboBox = new QComboBox;
   SexComboBox->addItem(tr("女"));
   SexComboBox->addItem(tr("男"));
   DepartmentLabel = new QLabel(tr("部门："));
   DepartmentTextEdit = new QTextEdit;
   AgeLabel = new QLabel(tr("年龄："));
   AgeLineEdit = new QLineEdit;
   OtherLabel = new QLabel(tr("备注："));
   //设定控件风格，setFrameStyle（）是QFrame的方法。参数指定由形状（shape）和阴影（shadow）配合设定
   //六种形状：NoFrame、Panel、Box、HLine、VLine及WinPanel；
   //三种阴影：Plain、Raised及Sunken。
   OtherLabel->setFrameStyle(QFrame::Panel |QFrame::Sunken);

   //左部布局，由于不是主布局管理器，所以不指定父窗口
   LeftLayout = new QGridLayout();
   //向布局中加入需要布局的控件
   LeftLayout->addWidget(UserNameLabel, 0, 0);
   LeftLayout->addWidget(UserNameLineEdit, 0, 1);
   LeftLayout->addWidget(NameLabel, 1, 0);
   LeftLayout->addWidget(NameLineEdit, 1, 1);


   LeftLayout->addWidget(SexLabel, 2, 0);
   LeftLayout->addWidget(SexComboBox, 2, 1);
   LeftLayout->addWidget(DepartmentLabel, 3, 0);
   LeftLayout->addWidget(DepartmentTextEdit, 3, 1);
   LeftLayout->addWidget(AgeLabel, 4, 0);
   LeftLayout->addWidget(AgeLineEdit, 4, 1);
   LeftLayout->addWidget(OtherLabel, 5, 0, 1, 2);
   //setColumnStretch()设定占用空间比例。
   //第一列和第二列比例为1:3.即使对话框框架大小改变，该比例也不会改变
   LeftLayout->setColumnStretch(0, 1);
   LeftLayout->setColumnStretch(1, 3);

   QGridLayout *mainLayout = new QGridLayout(this);
   mainLayout->addLayout(LeftLayout, 0, 0);
   mainLayout->setSizeConstraint(QLayout::SetFixedSize);
}

Dialog::~Dialog()
{

}
