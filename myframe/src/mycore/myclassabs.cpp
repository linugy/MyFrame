#include "myclassabs.h"
#include <QDir>
#include <QFile>
#include <mycore/mycore.h>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QPushButton>
#include <QToolBar>
#include <QDebug>
#include <QWidget>
#include <QHBoxLayout>

class MyClassAbsPrivate
{
    Q_DECLARE_PUBLIC(MyClassAbs)
public:
    MyClassAbsPrivate(MyClassAbs *qPtr);
    ~MyClassAbsPrivate();

public:
    QVariantMap mModuleMap;// module名称对应module内容
    QVariantMap mUimMap;// toolbar名称对应list
    QVariantMap mActionConfMap;// 配置对应内容
    QVariantMap mAciontFunctionMap;// 名称对应函数内容
    QMap<QString, QWidget*> mToolBarMap;// toolbar名称对应widget

protected:
    MyClassAbs * const q_ptr;
};

MyClassAbsPrivate::MyClassAbsPrivate(MyClassAbs *qPtr)
    : q_ptr(qPtr)
{
}

MyClassAbsPrivate::~MyClassAbsPrivate()
{
}


//------------end----------


MyClassAbs::MyClassAbs(QWidget *parent)
    : QMainWindow(parent), d_ptr(new MyClassAbsPrivate(this))
{

}

MyClassAbs::~MyClassAbs()
{

}

/**
* \brief
* 根据模块名称去读取配置：
* 结构：
* module一个map：名称对内容
* uim一个map：名称对内容(如果是toolbar，那么名称包含toolbar；如果是menu，那么名称包含menu)
* action一个map：名称对scriptValue()
*
* 首先根据titile判断是toolbar还是menu，
* 然后根据uim里面的值，如果type是toolitem，那么生成一个button，名称由内容决定，按钮的内容为脚本内容，
* 此时按工具栏名称-toolbar的方式，构成一个map，当用户调用getWidgetByName时，返回对应的toolbar或者menu
*/
void MyClassAbs::initModule(const QString &iModuleName)
{
    initModuleMap(iModuleName);
    initUimMap(iModuleName);
    initActionMap(iModuleName);
    initButtons();
}

/**
* \brief
* 当用户调用时，会传入一个toolbar的名称，然后根据名称返回widget，当然widget上有按钮，且关联了点击信号
* widget返回之后，由用户决定toolbar放的位置
*/
QWidget* MyClassAbs::getWidgetByName(const QString &iToolBarName)
{
    Q_D(MyClassAbs);
    qDebug() << d->mToolBarMap;
    return d->mToolBarMap.value(iToolBarName);
}

/**
* \brief
* 当按钮点击后，取出data，然后获取APP.engine，
* 然后执行run函数，并传入当前模块的指针作为this对象
*/
void MyClassAbs::onBtnClicked()
{
    getCurModuleClassPoint();
}

void MyClassAbs::initModuleMap(const QString &iModuleName)
{
    Q_D(MyClassAbs);
    QDir moduleUrl(APP->getModulePath());// "../../../src/module/DEMO/"
    QString modulePath = moduleUrl.absolutePath() + "/" + iModuleName + "/module.conf";
    QFile file(modulePath);
    if (!file.open( QIODevice::ReadWrite)) {
        return;
    }

    QJsonParseError jsonParserError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson( file.readAll(), &jsonParserError );

    if (!jsonDocument.isNull() && jsonParserError.error == QJsonParseError::NoError) {
        QVariantMap m = jsonDocument.toVariant().toMap();
        d->mModuleMap.insert(iModuleName, m);
    }
}

void MyClassAbs::initUimMap(const QString &iModuleName)
{
    Q_D(MyClassAbs);
    QDir moduleUrl(APP->getModulePath());// "../../../src/module/DEMO/"
    qDebug() << "=====" << APP->getModulePath();
    QString uimPath = moduleUrl.absolutePath() + "/" + iModuleName + "/uim.conf";
    qDebug() << "-------uimPath----" << uimPath;
    QFile file(uimPath);
    if (!file.open( QIODevice::ReadWrite)) {
        return;
    }

    QJsonParseError jsonParserError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson( file.readAll(), &jsonParserError );

    if (!jsonDocument.isNull() && jsonParserError.error == QJsonParseError::NoError) {
        QVariantMap m = jsonDocument.toVariant().toMap();
        qDebug() << "-----jsonDocument-----" << m;
        d->mUimMap = m;
    }
}

void MyClassAbs::initActionMap(const QString &iModuleName)
{
    initActionConfMap(iModuleName);
    initActionFunctionMap(iModuleName);
}

void MyClassAbs::initActionConfMap(const QString &iModuleName)
{
    Q_D(MyClassAbs);
    QDir moduleUrl(APP->getModulePath());// "../../../src/module/DEMO/"
    QString actionsPath = moduleUrl.absolutePath() + "/" + iModuleName + "/actions/";
    qDebug() << "------initActionConfMap-------" << actionsPath;
    QDir actionsDir(actionsPath);
    foreach (QFileInfo fileName, actionsDir.entryInfoList(QDir::Files)) {
        qDebug() << "------fileName--" << fileName.fileName() << fileName.absolutePath();
        if (!fileName.fileName().endsWith("_conf.conf")) {
            continue;
        }
        qDebug() <<"11111111" << fileName.filePath();
        QFile file(fileName.filePath());
        if (!file.open( QIODevice::ReadWrite)) {
            return;
        }
        QJsonParseError jsonParserError;
        QJsonDocument jsonDocument = QJsonDocument::fromJson( file.readAll(), &jsonParserError );

        if (!jsonDocument.isNull() && jsonParserError.error == QJsonParseError::NoError) {
            QVariantMap m = jsonDocument.toVariant().toMap();
            QString tmpName = fileName.fileName();
            // 去掉后缀
            d->mActionConfMap.insert(tmpName.left(tmpName.length() - 10), m);
        }
    }
    qDebug() << "--------mActionConfMap------" << d->mActionConfMap;
}

void MyClassAbs::initActionFunctionMap(const QString &iModuleName)
{
    Q_D(MyClassAbs);
    QDir moduleUrl(APP->getModulePath());// "../../../src/module/DEMO/"
    QString actionsPath = moduleUrl.absolutePath() + "/" + iModuleName + "/actions/";
    QDir actionsDir(actionsPath);
    foreach (QFileInfo fileName, actionsDir.entryInfoList(QDir::Files)) {
        if (fileName.fileName().endsWith("_conf.conf")) {
            continue;
        }
        QFile file(fileName.filePath());
        if (!file.open( QIODevice::ReadWrite)) {
            return;
        }
        QString functionStr = QString(file.readAll());
        QString tmpName = fileName.fileName();
        // 去掉后缀
        d->mAciontFunctionMap.insert(tmpName.left(tmpName.length() - 3), functionStr);
    }
    qDebug() << "--------mAciontFunctionMap------" << d->mAciontFunctionMap;
}

/**
* \brief
* 初始化所有的按钮，按钮的text和data由uim里的配置决定，且会对按钮关联点击信号
*/
void MyClassAbs::initButtons()
{
    Q_D(MyClassAbs);
    qDebug() << "-------initButtons-------";
    qDebug() << "d->mUimMap" << d->mUimMap;
    qDebug() << "-------" << d->mUimMap.keys();
    for (QString key : d->mUimMap.keys()) {
        if (key.toUpper().contains("TOOLBAR")) {
            QWidget *toolBar = new QWidget();
            QHBoxLayout *layout = new QHBoxLayout(toolBar);
            toolBar->setLayout(layout);
            QVariantList confLst = d->mUimMap.value(key).toList();
            for (QVariant var : confLst) {
                QVariantMap m = var.toMap();
                if (m.value("type").toString().toLower().contains("toolitem")) {
                    QString actionName = m.value("action").toString();
                    // 根据actionName获取配置
                    QVariantMap actionConfMap = d->mActionConfMap.value(actionName + "_conf").toMap();
                    QPushButton *pushButton = new QPushButton(actionConfMap.value("label").toString(), toolBar);
                    pushButton->setText(actionConfMap.value("label").toString());
//                    pushButton->setUserData(1, d->mAciontFunctionMap.value(actionName).toString());
                    layout->addWidget(pushButton);
                }
            }
            d->mToolBarMap.insert(key, toolBar);
        }
    }
}

/**
* \brief
* 首先获取点击的按钮，因为点击按钮的时候，模块肯定已经创建完成了。
* 此时一直获取父类，如果parent是继承自 MyClassAbs，那么表示获取到了当前模块的指针
*/
MyClassAbs *MyClassAbs::getCurModuleClassPoint()
{
    return nullptr;
}
