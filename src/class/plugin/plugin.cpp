#include "plugin.h"
#include "sysusermgt/sysusermgt.h"
#include "sysmainwindow/sysmainwindow.h"
#include "sysrolemgt/sysrolemgt.h"
#include <QDebug>

QStringList Plugin::getClassList()
{
    return QStringList() << "SysUserMgt" << "SysMainWindow" << "SysRoleMgt";
}

MyClassAbs *Plugin::newClass(const QString &iClassName, const QString &iModuleName, const QVariantMap &iUrlPars)
{
    Q_UNUSED(iUrlPars);
    if (iClassName == "SysUserMgt") {
        return new SysUserMgt(iModuleName);
    } else if (iClassName == "SysMainWindow") {
        return new SysMainWindow(iModuleName);
    } else if (iClassName == "SysRoleMgt") {
        return new SysRoleMgt(iModuleName);
    } else {
        return new MyClassAbs();
    }
}
