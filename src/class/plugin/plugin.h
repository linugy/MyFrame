#ifndef PLUGIN_H
#define PLUGIN_H

#include <QObject>
#include <QtPlugin>
#include "mycore/myclasspluginabs.h"

class Plugin : public QObject, public MyClassPluginAbs
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "net.My.MyClassAbsPlugin")
    Q_INTERFACES(MyClassPluginAbs)

public:
    QStringList getClassList() override;
    MyClassAbs *newClass(const QString &iClassName,
                          const QString &iModuleName,
                          const QVariantMap &iUrlPars = QVariantMap()) override;
};

#endif // PLUGIN_H
