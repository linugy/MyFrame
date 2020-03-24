#include "mylogin.h"
#include <QPushButton>

class MyLoginPrivate
{
    Q_DECLARE_PUBLIC(MyLogin)
public slots:
    explicit MyLoginPrivate(MyLogin *qPtr);
    ~MyLoginPrivate();

protected:
    MyLogin *const q_ptr;

private:
    QPushButton *loginBtn;
};

MyLoginPrivate::MyLoginPrivate(MyLogin *qPtr)
    : q_ptr(qPtr)
{
}

MyLoginPrivate::~MyLoginPrivate()
{
}
//---end---

MyLogin::MyLogin(QWidget *parent)
    : QDialog(parent), d_ptr(new MyLoginPrivate(this))
{
    initUi();
}

MyLogin::~MyLogin()
{

}

bool MyLogin::loginVerify()
{
    // 打开软件主界面
//    APP->openMainModule();

    // 隐藏登录界面
    this->hide();
    this->accept();
    this->close();

    return true;
}

void MyLogin::initUi()
{
    Q_D(MyLogin);
    d->loginBtn = new QPushButton(this);
    d->loginBtn->setText("login");


    connect(d->loginBtn, SIGNAL(clicked()), this, SLOT(loginVerify()));
}
