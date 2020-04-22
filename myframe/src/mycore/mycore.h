#ifndef MYCORE_H
#define MYCORE_H

#include "mycore_global.h"
#include <QScopedPointer>
#include <QObject>
#include <mybaseutil/myscriptengine.h>
#include "myclassabs.h"

#if defined(APP)
#undef APP
#endif
#define APP MyCore::instance()

class MyScriptEngine;
class MyCorePrivate;
class MyClassAbs;
class MYCORESHARED_EXPORT MyCore : public QObject
{
    Q_OBJECT
public:
    static MyCore *instance();

public slots:
    void setPluginPath(const QString &iPluginPath);
    void addPlugin();
    void setModulePath(const QString &iModuleCfgPath);
    QString getModulePath();
    void addModule();
    QString readConfig();
    void setModuleUrl(const QString &iModuleUrl);
    QString getModuleUrl();
    MyClassAbs *openModuleUrl(const QString &iModuleUrl);

    MyScriptEngine *scriptEngine();
    QList<MyClassAbs *> getAllClass();
private slots:
    QString getDllName(const QString &iDllStr);

private:
    MyClassAbs *openModule(const QString &iPluginName, const QString &iClassName, const QString &iModuleName);

private:
    MyCore();
    ~MyCore();

protected:
    const QScopedPointer<MyCorePrivate> d_ptr;

private:
    Q_DISABLE_COPY(MyCore)
    Q_DECLARE_PRIVATE(MyCore)
};

#endif // MYCORE_H
