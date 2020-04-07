#ifndef MYCLASSABS_H
#define MYCLASSABS_H

#include <QMainWindow>
#include "mycore_global.h"

class MyClassAbsPrivate;
class MYCORESHARED_EXPORT MyClassAbs : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyClassAbs(QWidget *parent = 0);
    ~MyClassAbs();

signals:

public slots:
    void initModule(const QString &iModuleName);
    QWidget *getWidgetByName(const QString &iToolBarName);

private slots:
    void onBtnClicked();

private:
    void initModuleMap(const QString &iModuleName);
    void initUimMap(const QString &iModuleName);
    void initActionMap(const QString &iModuleName);
    void initActionConfMap(const QString &iModuleName);
    void initActionFunctionMap(const QString &iModuleName);
    void initButtons();
    MyClassAbs *getCurModuleClassPoint();

protected:
    const QScopedPointer<MyClassAbsPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MyClassAbs)
    Q_DECLARE_PRIVATE(MyClassAbs)
};

#endif // MYCLASSABS_H
