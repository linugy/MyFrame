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
#include <QAction>

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
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint );
    setMinimumSize(400, 300);
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
    return d->mToolBarMap.value(iToolBarName);
}

QVariant MyClassAbs::config(const QString &iStr)
{
    Q_D(MyClassAbs);
    for (QString var : d->mModuleMap.keys()) {
        return d->mModuleMap.value(var).toMap().value(iStr);
    }
    return QVariant();
}

/**
* \brief
* 当按钮点击后，取出data，然后获取APP.engine，
* 然后执行run函数，并传入当前模块的指针作为this对象
*/
void MyClassAbs::onBtnClicked()
{
    if (QAction *action = qobject_cast<QAction *>(sender())) {
        QString funcStr = action->data().toString();
        // 获取当前打开模块的指针，从而可以在脚本中使用共有槽函数
        QWidget *curModule = getCurModuleClassPoint(action);
        QString runStr = QString("function run(){") + funcStr + "}";
        QScriptContext *content = APP->scriptEngine()->pushContext();
        content->engine()->evaluate(runStr);
        QScriptValue object = content->activationObject();
        QScriptValue func = object.property("run");
        // 执行action的内容时，将当前当前模块指针传入
        func.call(content->engine()->newQObject(curModule));
        APP->scriptEngine()->popContext();
    }
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
    QString uimPath = moduleUrl.absolutePath() + "/" + iModuleName + "/uim.conf";
    QFile file(uimPath);
    if (!file.open( QIODevice::ReadWrite)) {
        return;
    }

    QJsonParseError jsonParserError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson( file.readAll(), &jsonParserError );

    if (!jsonDocument.isNull() && jsonParserError.error == QJsonParseError::NoError) {
        QVariantMap m = jsonDocument.toVariant().toMap();
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
    QDir actionsDir(actionsPath);
    foreach (QFileInfo fileName, actionsDir.entryInfoList(QDir::Files)) {
        if (!fileName.fileName().endsWith("_conf.conf")) {
            continue;
        }
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
}

/**
* \brief
* 初始化所有的按钮，按钮的text和data由uim里的配置决定，且会对按钮关联点击信号
*/
void MyClassAbs::initButtons()
{
    Q_D(MyClassAbs);
    for (QString key : d->mUimMap.keys()) {
        if (key.toUpper().contains("TOOLBAR")) {
            QToolBar *toolBar = new QToolBar();
            QVariantList confLst = d->mUimMap.value(key).toList();
            for (QVariant var : confLst) {
                QVariantMap m = var.toMap();
                if (m.value("type").toString().toLower().contains("toolitem")) {
                    QString actionName = m.value("action").toString();
                    // 根据actionName获取配置
                    QVariantMap actionConfMap = d->mActionConfMap.value(actionName).toMap();
                    // 通过配置获取到按钮的label
                    QAction *action = new QAction(actionConfMap.value("label").toString(), toolBar);
                    // 按钮中存放执行内容
                    action->setData(d->mAciontFunctionMap.value(actionName).toString());
                    // 关联信号
                    connect(action, SIGNAL(triggered(bool)), this, SLOT(onBtnClicked()));
                    toolBar->addAction(action);
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
QWidget *MyClassAbs::getCurModuleClassPoint(const QAction *action)
{
    QWidget *obj = action->parentWidget();
    QWidget *objParent = obj->parentWidget();
    while(objParent != nullptr && !isModuleClass(objParent)) {
        obj = objParent;
        objParent = objParent->parentWidget();
    }
    return objParent;
}

/**
* \brief 所有打开的模块中，是否有当前传入的widget
*/
bool MyClassAbs::isModuleClass(const QWidget *w)
{
    QList<MyClassAbs *>classLst = APP->getAllClass();
    for (MyClassAbs *curClass : classLst) {
        if (curClass->metaObject()->className() == w->metaObject()->className()) {
            return true;
        }
    }
    return false;
}
