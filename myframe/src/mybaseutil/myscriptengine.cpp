#include "myscriptengine.h"
#include <QStringList>
#include <QScriptValue>
#include <QScriptEngine>

class MyScriptEnginePrivate
{
    Q_DECLARE_PUBLIC(MyScriptEngine)
public:
    explicit MyScriptEnginePrivate(MyScriptEngine *iPtr);

protected:
    MyScriptEngine * const q_ptr;
};
MyScriptEnginePrivate::MyScriptEnginePrivate(MyScriptEngine *iPtr) :
    q_ptr(iPtr)
{

}

//-----------end-----------


MyScriptEngine::MyScriptEngine(QObject *iParent)
    : QScriptEngine(iParent), d_ptr(new MyScriptEnginePrivate(this))
{
    regFunction(importPackage, "importPackage");
    regFunction(availablePackages, "availablePackages");
}

MyScriptEngine::~MyScriptEngine()
{

}

QScriptValue MyScriptEngine::importPackage(QScriptContext *iContext, QScriptEngine *iEngine)
{
    for (int i = 0; i < iContext->argumentCount(); ++i) {
        QString pkg = iContext->argument(i).toString();
        if (iEngine->availableExtensions().contains(pkg)
                && !iEngine->importedExtensions().contains(pkg))
        {
            iEngine->importExtension(pkg);
        }
    }
    return QScriptValue();
}

QScriptValue MyScriptEngine::availablePackages(QScriptContext *iContext, QScriptEngine *iEngine)
{
    Q_UNUSED(iContext);
    QStringList pkgList = iEngine->availableExtensions();
    return iEngine->newVariant(QVariant(pkgList));
}

void MyScriptEngine::regFunction(QScriptEngine::FunctionSignature iFunc, const QString &iNameStr)
{
    globalObject().setProperty(iNameStr, newFunction(iFunc));
}
