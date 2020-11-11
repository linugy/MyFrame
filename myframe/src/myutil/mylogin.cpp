#include "mylogin.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
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
};

MyLoginPrivate::MyLoginPrivate(MyLogin *qPtr)
    : q_ptr(qPtr)
{
}

MyLoginPrivate::~MyLoginPrivate()
{
}

//---------------end--------------

MyLogin::MyLogin(QWidget *parent)
    : QDialog(parent), d_ptr(new MyLoginPrivate(this))
{
    initUi();
}

MyLogin::~MyLogin()
{

}

/**
* \brief 进行登录验证，如果成功，那么隐藏登录界面；如果失败，则弹出提示框
*/
bool MyLogin::loginVerify()
{
    Q_D(MyLogin);
    bool isSucceed = false;
    // 测试
    if (d->loginDilog->getUserName() == "admin" && d->loginDilog->getPassword() == "admin") {
        isSucceed = true;
    }

    if (isSucceed) {
        this->hide();
        this->accept();
        this->close();
        return true;
    } else {
        QMessageBox::warning(this, "Login", "Login failed!");
        return false;
    }
}

void MyLogin::setUserName(const QString &iUserName)
{
    Q_D(MyLogin);
    if (d->loginDilog != nullptr) {
        d->loginDilog->setUserName(iUserName);
    }
}

void MyLogin::setPassword(const QString &iPassword)
{
    Q_D(MyLogin);
    if (d->loginDilog != nullptr) {
        d->loginDilog->setPassword(iPassword);
    }
}

void MyLogin::initUi()
{
    Q_D(MyLogin);
    d->loginDilog = new MyLoginDialog(this);
    if (d->loginBtn = qobject_cast<QPushButton *>(d->loginDilog->loginBtn())) {
        connect(d->loginBtn, SIGNAL(clicked()), this, SLOT(loginVerify()));
    }
}
