#include "mymain.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QMessageBox>
#include <QScriptEngine>
#include <QDir>
#include <QDebug>
#include "mycore/mycore.h"
#include "mylogin.h"
#include <mywidget/mywidget.h>
#include <mybaseutil/myscriptengine.h>
#include <QResource>
#include <QTranslator>

/**
* \brief main
*/
int MyMain::appExec(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir qmDir(QApplication::applicationDirPath());
    qmDir.cdUp();
    qmDir.cd("language");
    foreach (QFileInfo file, qmDir.entryInfoList(QDir::Files)) {
        if (file.suffix() == "qm") {
            QTranslator *translator = new QTranslator;
            if (translator->load(file.absoluteFilePath())) {
                a.installTranslator(translator);
            }
        }
    }

    QResource::registerResource("../resource/res/my.rcc");
    QVariantMap argsMap = parseArgs(a);
    int ret = run(argsMap);
    if (ret == 1){
        return a.exec();
    } else {
        a.quit();
        return ret;
    }
}

MyMain::MyMain()
{

}

/**
* \brief 解析传入的默认参数,例如模块名称,账号,密码等
*/
QVariantMap MyMain::parseArgs(const QCoreApplication &app)
{
    Q_UNUSED(app);
    // 测试
    QVariantMap resMap;
    resMap.insert("module", "my-main");
    resMap.insert("username", "admin");
    resMap.insert("password", "admin");
    return resMap;
}

/**
* \brief 执行软件初始化操作,同时弹出登录界面
*/
int MyMain::run(const QVariantMap &iArgsMap)
{
    // 加载插件
    QDir plugdir(QApplication::applicationDirPath());
    plugdir.cd("plugins");
    APP->setPluginPath(plugdir.absolutePath());
    APP->addPlugin();

    // 加载module（需要读取config文件）
    APP->setModulePath(APP->readConfig());
    APP->addModule();

    // 加载框架脚本
    APP->scriptEngine()->importExtension("widgets");

    // 显示登陆界面
    MyLogin login;
    login.setUserName(iArgsMap.value("username").toString());
    login.setPassword(iArgsMap.value("password").toString());
    int res = login.exec();
    if (res == 1) {
        APP->openModuleUrl(iArgsMap.value("module").toString());
    }
    return res;
}
