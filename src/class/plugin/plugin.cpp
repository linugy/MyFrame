#include "plugin.h"
#include "sysusermgt/sysusermgt.h"
#include "sysmainwindow/sysmainwindow.h"
#include <QDebug>

QStringList Plugin::getClassList()
{
    return QStringList() << "SysUserMgt" << "SysMainWindow";
}

MyClassAbs *Plugin::newClass(const QString &iClassName, const QString &iModuleName, const QVariantMap &iUrlPars)
{
    if (iClassName == "SysUserMgt") {
        return new SysUserMgt(iModuleName);
    } else if (iClassName == "SysMainWindow") {
        return new SysMainWindow(iModuleName);
    }
}
