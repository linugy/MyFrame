#include "mycore.h"
#include <QApplication>
#include <QMap>
#include <QVariantMap>
#include <QPluginLoader>
#include <QString>
#include <QDir>
#include <QJsonParseError>
#include <QJsonDocument>

class MyCorePrivate
{
    Q_DECLARE_PUBLIC(MyCore)
public:
    MyCorePrivate(MyCore *qPtr);
    ~MyCorePrivate();
public:
    QString mPluginPath;
    QMap<QString, QObject*> mPluginMap;// dll名称对应插件
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
    QDir pluginsDir(d->mPluginPath);
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
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
    Q_D(MyCore);
    QDir moduleDir(d->mModuleCfgPath);
    foreach (QString fileName, moduleDir.entryList(QDir::Files)) {
        QFile file(fileName);
        if ( !file.open( QIODevice::ReadWrite ) ) {
            return;
        }

        QJsonParseError jsonParserError;
        QJsonDocument jsonDocument = QJsonDocument::fromJson( file.readAll(), &jsonParserError );

        if ( !jsonDocument.isNull() && jsonParserError.error == QJsonParseError::NoError ) {
            QVariantMap m = jsonDocument.toVariant().toMap();
            d->mModuleCfgMap.insert(fileName, m);
        }
    }
}

QString MyCore::readConfig()
{
    QFile file("../../config/my.cfg");
    if ( !file.open( QIODevice::ReadWrite ) ) {
        return "";
    }

    QJsonParseError jsonParserError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson( file.readAll(), &jsonParserError );

    if ( !jsonDocument.isNull() && jsonParserError.error == QJsonParseError::NoError ) {
        QVariantMap m = jsonDocument.toVariant().toMap();
        return m.value("module_url").toString();
    }
    return "";
}

QString MyCore::getDllName(const QString &iDllStr)
{
    QString dllStr = iDllStr;
    return dllStr.left(dllStr.length() - 5);
}
