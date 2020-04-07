#ifndef MYWIDGETECMABINDING_H
#define MYWIDGETECMABINDING_H

#include <QScriptExtensionPlugin>

class MyWidgetEcmabinding : public QScriptExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "net.my.ecmalugin")
public:
    QStringList keys() const;
    void initialize(const QString &key, QScriptEngine *engine);
};

#endif // MYWIDGETECMABINDING_H
