#ifndef MYLOGIN_H
#define MYLOGIN_H

#include "myutil_global.h"
#include <QDialog>
#include <QScopedPointer>

class MyLoginPrivate;
class MYUTILSHARED_EXPORT MyLogin : public QDialog
{
    Q_OBJECT
public:
    explicit MyLogin(QWidget *parent = 0);
    ~MyLogin();
public slots:
    bool loginVerify();
    void setModuleTitle(const QString &iTitle);

    void setModuleUrl(const QString &iUrl);
    QString getModuleUrl();

private slots:
    void initUi();

protected:
    const QScopedPointer<MyLoginPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MyLogin)
    Q_DECLARE_PRIVATE(MyLogin)
};

#endif // MYLOGIN_H
