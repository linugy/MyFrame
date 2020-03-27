#include "mycore.h"
#include <QMap>
#include <QVariantMap>
#include <QPluginLoader>
#include <QString>

class MyCorePrivate
{
    Q_DECLARE_PUBLIC(MyCore)
public:
    MyCorePrivate(MyCore *qPtr);
    ~MyCorePrivate();
public:
    QString mPluginPath;
    QMap<QString, QObject> mPluginMap;// dll名称对应插件
    QString mModuleCfgPath;
    QMap<QString, QVariantMap> mModuleCfgMap;// module名称对应内容

protected:
    MyCore * const q_ptr;
};

MyCorePrivate::MyCorePrivate(MyCore *qPtr)
    : q_ptr(qPtr)
{
}

MyCorePrivate::~MyCorePrivate()
{
}

MyCore::MyCore()
{
}

MyCore::~MyCore()
{

}

MyCore *MyCore::instance()
{
    static MyCore instance;
    return &instance;
}

void MyCore::setPluginPath(const QString &iPluginPath)
{
    Q_D(MyCore);
    d->mPluginPath = iPluginPath;
}

void MyCore::addPlugin()
{
    Q_D(MyCore);
    foreach (QString fileName, pluginsDir.entryList(d->mPluginPath)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            d->mPluginMap.insert(getDllName(fileName), plugin);
        }
    }
}

void MyCore::setModulePath(const QString &iModuleCfgPath)
{
    Q_D(MyCore);
    d->mModuleCfgPath = iModuleCfgPath;
}

void MyCore::addModule()
{

}

QString MyCore::readConfig()
{

}

QString MyCore::getDllName(const QStirng &iDllStr)
{
    QString dllStr = iDllStr;
    return dllStr.left(dllStr.length() - 5);
}
