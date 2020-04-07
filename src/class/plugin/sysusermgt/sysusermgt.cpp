#include "sysusermgt.h"
#include <mywidget/mywidget.h>
#include <QDebug>
#include <QHBoxLayout>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QToolBar>
#include <mycore/mycore.h>
//#include <mybaseutil/myscriptengine.h>

SysUserMgt::SysUserMgt(const QString &iModuleName)
{
    initModule(iModuleName);
    qDebug() << "=====SysUserMgt======";
    mWidget = new MyWidget(this);
    QVBoxLayout *mLayout = new QVBoxLayout(mWidget);
    qDebug() << qobject_cast<QWidget*>(getWidgetByName("MainToolBar"));
    QWidget *toolbar;
    if (toolbar = qobject_cast<QWidget*>(getWidgetByName("MainToolBar"))) {
        qDebug() << "-----------ok";
        toolbar->show();
//        mLayout->addWidget(toolbar, 0);
    }
    mWidget->setLayout(mLayout);


//    mWidget = new MyWidget(this);
//    mWidget->setStyleSheet("QWidget{background: gray}");
//    QHBoxLayout *myLayout = new QHBoxLayout(mWidget);
//    QLabel *label = new QLabel("myLabel");
//    myLayout->addWidget(label);
//    mWidget->setLayout(myLayout);
//    this->setCentralWidget(mWidget);

//    APP->scriptEngine()->evaluate("print('---111---'); var widget = new MyWidget; widget.setWindowTitle('testMyWidget');widget.show()");
}

SysUserMgt::~SysUserMgt()
{

}

