#include "mycore.h"
#include <QApplication>
#include <QMap>
#include <QVariantMap>
#include <QPluginLoader>
#include <QString>
#include <QDir>
#include <QJsonParseError>
#include <QJsonDocument>
#include "myclasspluginabs.h"
#include "myclassabs.h"
#include <QDebug>
#include <QMainWindow>
#include <mybaseutil/myscriptengine.h>

class MyCorePrivate
{
    Q_DECLARE_PUBLIC(MyCore)
public:
    MyCorePrivate(MyCore *qPtr);
    ~MyCorePrivate();
public:
    QString mPluginPath;
    QMap<QString, QObject*> mPluginMap;// 插件名称对应内容
    QString mModuleCfgPath;
    QMap<QString, QVariantMap> mModuleCfgMap;// module名称对应内容
    QString curModuleUrl;
    MyScriptEngine *mEngine = nullptr;
    QList<MyClassAbs *> mAllClassLst;// 存放软件中所有打开的模块，为了能够在执行脚本的时候找到this类

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

//------end---------

MyCore::MyCore()
    : d_ptr(new MyCorePrivate(this))
{
    Q_D(MyCore);
    d->mEngine = new MyScriptEngine();
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
    QDir dir(iModuleCfgPath);
    d->mModuleCfgPath = dir.absolutePath();
}

QString MyCore::getModulePath()
{
    Q_D(MyCore);
    return d->mModuleCfgPath;
}

void MyCore::addModule()
{
    Q_D(MyCore);
    QDir moduleDir(d->mModuleCfgPath);
    foreach (QFileInfo path, moduleDir.entryInfoList(QDir::Dirs)) {
        if (path.fileName() == "." || path.fileName() == "..") {
            continue;
        }
        QFile file(path.absoluteFilePath() + "/module.conf");
        if (!file.open( QIODevice::ReadWrite)) {
            return;
        }

        QJsonParseError jsonParserError;
        QJsonDocument jsonDocument = QJsonDocument::fromJson( file.readAll(), &jsonParserError );

        if (!jsonDocument.isNull() && jsonParserError.error == QJsonParseError::NoError) {
            QVariantMap m = jsonDocument.toVariant().toMap();
            d->mModuleCfgMap.insert(path.fileName(), m);
        }
    }
}

QString MyCore::readConfig()
{
    QFile file("../../config/my.cfg");
    if (!file.open( QIODevice::ReadWrite )) {
        return "";
    }

    QJsonParseError jsonParserError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson( file.readAll(), &jsonParserError);

    if (!jsonDocument.isNull() && jsonParserError.error == QJsonParseError::NoError) {
        QVariantMap m = jsonDocument.toVariant().toMap();
        return m.value("module_url").toString();
    }
    return "";
}

void MyCore::setModuleUrl(const QString &iModuleUrl)
{
    Q_D(MyCore);
    d->curModuleUrl = iModuleUrl;
}

QString MyCore::getModuleUrl()
{
    Q_D(MyCore);
    return d->curModuleUrl;
}

MyClassAbs *MyCore::openModuleUrl(const QString &iModuleUrl)
{
    // 根据rul或者module对应的配置
    Q_D(MyCore);
    QVariantMap cfgMap = d->mModuleCfgMap.value(iModuleUrl);

    // 获取plugin名称和class名称，调用插件的newclass
    return openModule(cfgMap.value("plugin").toString(), cfgMap.value("class").toString(), iModuleUrl);
}

MyScriptEngine *MyCore::scriptEngine()
{
    Q_D(MyCore);
    return d->mEngine;
}

QList<MyClassAbs *> MyCore::getAllClass()
{
    Q_D(MyCore);
    return d->mAllClassLst;
}

/**
* \brief 主界面关闭模块时，将该模块从mAllClassLst中移除
*/
void MyCore::deleteClass(MyClassAbs *iClass)
{
    Q_D(MyCore);
    if (d->mAllClassLst.contains(iClass)) {
        int index = d->mAllClassLst.indexOf(iClass);
        d->mAllClassLst.removeAt(index);
    }
}

QString MyCore::getDllName(const QString &iDllStr)
{
    QString dllStr = iDllStr;
    return dllStr.left(dllStr.length() - 5);
}

MyClassAbs *MyCore::openModule(const QString &iPluginName, const QString &iClassName, const QString &iModuleName)
{
    // 获取插件
    Q_D(MyCore);
    MyClassAbs *resObj = nullptr;
    QObject * obj = d->mPluginMap.value(iPluginName);
    if (MyClassPluginAbs *interface = qobject_cast<MyClassPluginAbs *>(obj)) {
        resObj = interface->newClass(iClassName, iModuleName, QVariantMap());
        // 存放所有的模块，用于执行js脚本时找到当前的模块指针，然后传到js脚本里
        d->mAllClassLst.append(resObj);
        return resObj;
    }
    return resObj;
}
