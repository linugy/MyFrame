#ifndef MYMAIN_H
#define MYMAIN_H

#include <QCoreApplication>
#include <QVariantMap>
#include "myutil_global.h"

class MYUTILSHARED_EXPORT MyMain
{
public:
    static int appExec(int argc, char* argv[]);

private:
    explicit MyMain();
    static QVariantMap parseArgs(const QCoreApplication &app);
    static int run(const QVariantMap &iArgsMap);
};

#endif // MYMAIN_H
