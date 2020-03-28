#ifndef MYCLASSPLUGINABS_H
#define MYCLASSPLUGINABS_H

#include <QMap>
#include <QStringList>
#include <QVariantMap>

class MyClassAbs;
class MyClassPluginAbs
{
public:
    virtual ~MyClassPluginAbs() {}
    virtual QStringList getClassList() = 0;

    virtual MyClassAbs *newClass(const QString &/*class_name*/,
                                  const QString &/*module_name*/,
                                  const QVariantMap &/*url_parameter*/) = 0;
};

Q_DECLARE_INTERFACE(MyClassPluginAbs, "net.My.MyClassPluginAbs")

#endif // MYCLASSPLUGINABS_H
