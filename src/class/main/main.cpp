#include <QApplication>
#include <QWidget>
#include <QDir>
#include <QPluginLoader>
#include <QDebug>
#include "mycore/mycore.h"
#include <QFile>
#include <QJsonParseError>
#include <QJsonDocument>
#include "myutil/myutil.h"
#include "myutil/mymain.h"

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
    qDebug() << "-----------------------------start";
    return MyMain::appExec(argc, argv);
}
