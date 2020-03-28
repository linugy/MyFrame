#include <QApplication>
#include <QWidget>
#include <QDir>
#include <QPluginLoader>
#include <QDebug>
#include "mycore/mycore.h"
#include <QFile>
#include <QJsonParseError>
#include <QJsonDocument>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "-----------------------------start";
    return a.exec();
}
