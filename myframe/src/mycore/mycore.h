#ifndef MYCORE_H
#define MYCORE_H

#include "mycore_global.h"
#include <QScopedPointer>
#include <QObject>
#include <mybaseutil/myscriptengine.h>

#if defined(APP)
#undef APP
#endif
#define APP MyCore::instance()

class MyScriptEngine;
class MyCorePrivate;
class MYCORESHARED_EXPORT MyCore : public QObject
{
    Q_OBJECT
public:
    static MyCore *instance();

public slots:
    void setPluginPath(const QString &iPluginPath);
    void addPlugin();
    void setModulePath(const QString &iModuleCfgPath);
    void addModule();
    QString readConfig();
    void setModuleUrl(const QString &iModuleUrl);
    QString getModuleUrl();
    void openModuleUrl(const QString &iModuleUrl);

    MyScriptEngine *scriptEngine();

private slots:
    QString getDllName(const QString &iDllStr);

private:
    void openModule(const QString &iPluginName, const QString &iClassName);

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
