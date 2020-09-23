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

/**
* \brief main
*/
int MyMain::appExec(int argc, char *argv[])
{
    QApplication a(argc, argv);
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
* \brief 解析传入的参数,例如模块名称,账号,密码等
*/
QVariantMap MyMain::parseArgs(const QCoreApplication &app)
{
    Q_UNUSED(app);
    return QVariantMap();
}

/**
* \brief 执行软件初始化操作,同时弹出登录界面
*/
int MyMain::run(const QVariantMap &iArgsMap)
{
    Q_UNUSED(iArgsMap);

    // 加载模块插件到内存
    QDir plugdir(QApplication::applicationDirPath());
    plugdir.cd("plugins");
    APP->setPluginPath(plugdir.absolutePath());
    APP->addPlugin();

    // 加载module到内存（需要读取config文件）
    APP->setModulePath(APP->readConfig());
    APP->addModule();

    // 解析传入参数，显示登陆界面
    QString productUrl = iArgsMap.value("product").toString();
    productUrl = "my-main";// 测试

    // 加载框架脚本
    APP->scriptEngine()->importExtension("widgets");

    MyLogin login;
    login.setModuleUrl(productUrl);
    login.setModuleTitle("Test");
    return login.exec();
}
