#ifndef SYSUSERMGT_H
#define SYSUSERMGT_H

#include "mycore/myclassabs.h"

class MyWidget;
class SysUserMgt : public MyClassAbs
{
    Q_OBJECT
public:
    explicit SysUserMgt(const QString &iModuleName);
    ~SysUserMgt();

public slots:

private:
    MyWidget *mWidget = nullptr;
};

#endif // SYSUSERMGT_H
