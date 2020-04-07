#include "mywidgetecmabinding.h"
#include <QScriptContext>
#include <QScriptEngine>
#include <QMetaObject>
#include <QDebug>
#include <mywidget/mywidget.h>


QScriptValue constructMyWidget(QScriptContext *iContext, QScriptEngine *iEngine)
{
    Q_UNUSED(iEngine);

    if (iContext->argumentCount() == 0)
    {
        return iContext->engine()->newQObject(iContext->thisObject(), new MyWidget(), QScriptEngine::AutoOwnership);
    }
    return QScriptValue();
}

QStringList MyWidgetEcmabinding::keys() const
{
     return QStringList() << "widgets";
}

void MyWidgetEcmabinding::initialize(const QString &key, QScriptEngine *engine)
{
    if (key == "widgets") {
        QScriptValue proto = engine->newObject();
        QScriptValue ctor = engine->newFunction(constructMyWidget, proto);
        engine->globalObject().setProperty("MyWidget", ctor, QScriptValue::SkipInEnumeration);
    }
}
