#include "mymain.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QMessageBox>
#include <QDir>
#include <QDebug>
#include "mycore/mycore.h"
#include "mylogin.h"

/**
* \brief main
*/
int MyMain::appExec(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QVariantMap argsMap = parseArgs(a);
    int ret = run(argsMap);
    if (ret == 0){
        return a.exec();
    } else {
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
    productUrl = "my-demo";// 测试

    MyLogin login;
    login.setModuleUrl(productUrl);
    login.setModuleTitle("Test");
    login.exec();

    return 0;
}
