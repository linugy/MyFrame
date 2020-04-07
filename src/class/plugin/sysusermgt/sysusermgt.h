#ifndef SYSUSERMGT_H
#define SYSUSERMGT_H

#include "mycore/myclassabs.h"

class MyWidget;
class SysUserMgt : public MyClassAbs
{
    Q_OBJECT
public:
    explicit SysUserMgt(const QString &iModuleName, QWidget *parent = nullptr);
    ~SysUserMgt();

public slots:
    QString getCurText();

private:
    MyWidget *mWidget = nullptr;
};

#endif // SYSUSERMGT_H
