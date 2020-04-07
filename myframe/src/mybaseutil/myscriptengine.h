#ifndef MYSCRIPTENGINE_H
#define MYSCRIPTENGINE_H

#include "mybaseutil_global.h"
#include <QWidget>
#include <QScriptEngine>

class MyScriptEnginePrivate;
class MYBASEUTILSHARED_EXPORT MyScriptEngine : public QScriptEngine
{
    Q_OBJECT
public:
    explicit MyScriptEngine(QObject *iParent = 0);
    ~MyScriptEngine();

    static QScriptValue importPackage(QScriptContext *iContext, QScriptEngine *iEngine);
    static QScriptValue availablePackages(QScriptContext *iContext, QScriptEngine *iEngine);

public slots:
    void regFunction(QScriptEngine::FunctionSignature iFunc, const QString &iNameStr);

protected:
    const QScopedPointer<MyScriptEnginePrivate> d_ptr;

private:
    Q_DISABLE_COPY(MyScriptEngine)
    Q_DECLARE_PRIVATE(MyScriptEngine)
};

#endif // MYSCRIPTENGINE_H
