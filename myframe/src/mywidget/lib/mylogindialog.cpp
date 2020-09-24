#include "mylogindialog.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFont>

class MyLoginDialogPrivate {
    Q_DECLARE_PUBLIC(MyLoginDialog)
public:
    explicit MyLoginDialogPrivate(MyLoginDialog * qptr);
    ~MyLoginDialogPrivate();

protected:
    MyLoginDialog* const q_ptr;
    QPushButton *loginBtn;
    QLineEdit *username;
    QLineEdit *password;
};

MyLoginDialogPrivate::MyLoginDialogPrivate(MyLoginDialog *qptr)
    : q_ptr(qptr)
{

}

MyLoginDialogPrivate::~MyLoginDialogPrivate()
{

}

//------------end---------------------

MyLoginDialog::MyLoginDialog(QWidget *parent)
    : QWidget(parent), d_ptr(new MyLoginDialogPrivate(this))
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint );
    setFixedSize(400, 200);
    initUi();
}

MyLoginDialog::~MyLoginDialog()
{

}

QPushButton *MyLoginDialog::loginBtn()
{
    Q_D(MyLoginDialog);
    return d->loginBtn;
}

void MyLoginDialog::initUi()
{
    Q_D(MyLoginDialog);
    QHBoxLayout *hLayout = new QHBoxLayout(this);


    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addStretch(1);
    vLayout->setSpacing(10);

    d->username = new QLineEdit(this);
    vLayout->addWidget(d->username);
    d->username->setFixedSize(200, 30);
    d->username->setFont(QFont("Timers", 16));
    d->username->setPlaceholderText(tr("username"));

    d->password = new QLineEdit(this);
    vLayout->addWidget(d->password);
    d->password->setFont(QFont("Timers", 16));
    d->password->setFixedSize(200, 30);
    d->password->setPlaceholderText(tr("password"));

    d->loginBtn = new QPushButton(this);
    vLayout->addWidget(d->loginBtn);
    d->loginBtn->setFixedWidth(200);
    d->loginBtn->setText(tr("login"));
    vLayout->addStretch(1);

    hLayout->addStretch(1);
    hLayout->addLayout(vLayout);
    hLayout->addStretch(1);
}
