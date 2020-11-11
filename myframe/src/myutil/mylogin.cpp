#include "mylogin.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <mycore/mycore.h>
#include <mycore/myclassabs.h>
#include <mywidget/mylogindialog.h>
#include <QDebug>

class MyLoginPrivate
{
    Q_DECLARE_PUBLIC(MyLogin)
public slots:
    explicit MyLoginPrivate(MyLogin *qPtr);
    ~MyLoginPrivate();

protected:
    MyLogin *const q_ptr;

private:
    MyLoginDialog *loginDilog;
    QPushButton *loginBtn;
    QString curModuleUrl;
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
    // 打开模块
    APP->openModuleUrl(getModuleUrl());

    // 隐藏登录界面
    this->hide();
    this->accept();
    this->close();

    return true;
}

void MyLogin::setModuleTitle(const QString &iTitle)
{
    Q_UNUSED(iTitle);
}

void MyLogin::setModuleUrl(const QString &iUrl)
{
    Q_D(MyLogin);
    d->curModuleUrl = iUrl;
}

QString MyLogin::getModuleUrl()
{
    Q_D(MyLogin);
    return d->curModuleUrl;
}

void MyLogin::initUi()
{
    Q_D(MyLogin);
    d->loginDilog = new MyLoginDialog(this);
    if (d->loginBtn = qobject_cast<QPushButton *>(d->loginDilog->loginBtn())) {
        connect(d->loginBtn, SIGNAL(clicked()), this, SLOT(loginVerify()));
    }
}
