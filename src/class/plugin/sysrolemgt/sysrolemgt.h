#ifndef SYSROLEMGT_H
#define SYSROLEMGT_H

#include "mycore/myclassabs.h"

class MyWidget;

class SysRoleMgt : public MyClassAbs
{
    Q_OBJECT
public:
    explicit SysRoleMgt(const QString &iModuleName, QWidget *parent = nullptr);
    ~SysRoleMgt();

public slots:
    QString getCurText();

private:
    MyWidget *mWidget = nullptr;
};

#endif // SYSROLEMGT_H
