#include "plugin.h"
#include "sysusermgt/sysusermgt.h"
#include <QDebug>

QStringList Plugin::getClassList()
{
    return QStringList() << "aa" << "bb";
}

MyClassAbs *Plugin::newClass(const QString &iClassName, const QString &iModuleName, const QVariantMap &iUrlPars)
{
    if (iClassName == "SysUserMgt") {
        return new SysUserMgt();
    }
}
