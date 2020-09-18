#ifndef MYLOGINDIALOG_H
#define MYLOGINDIALOG_H

#include "mywidget_global.h"
#include <QWidget>
#include <QPushButton>

class MyLoginDialogPrivate;

class MYWIDGETSHARED_EXPORT MyLoginDialog : public QWidget
{
    Q_OBJECT
public:
    explicit MyLoginDialog(QWidget *parent = nullptr);
    ~MyLoginDialog();

public slots:
    QPushButton *loginBtn();

protected:
    const QScopedPointer<MyLoginDialogPrivate> d_ptr;

private:
    void initUi();

private:
    Q_DISABLE_COPY(MyLoginDialog)
    Q_DECLARE_PRIVATE(MyLoginDialog)
};

#endif // MYLOGINDIALOG_H
