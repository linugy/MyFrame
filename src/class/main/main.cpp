#include <QApplication>
#include <QWidget>
#include <QDir>
#include <QPluginLoader>
#include <QDebug>
#include <QFile>
#include <QJsonParseError>
#include <QJsonDocument>
#include "mycore/mycore.h"
//#include "myutil/myutil.h"
#include "myutil/mymain.h"
//#include "mybaseutil/myscriptengine.h"
#include <QScriptEngine>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
    qDebug() << "-----------------------------start";
    return MyMain::appExec(argc, argv);
}
