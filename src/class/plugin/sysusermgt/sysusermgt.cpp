#include "sysusermgt.h"
#include <mywidget/mywidget.h>
#include <QDebug>
#include <QHBoxLayout>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QToolBar>
#include <mycore/mycore.h>
#include <QTableView>

SysUserMgt::SysUserMgt(const QString &iModuleName, QWidget *parent)
    : MyClassAbs(parent)
{
    initModule(iModuleName);

    mWidget = new MyWidget(this);
    this->setCentralWidget(mWidget);
    QVBoxLayout *mLayout = new QVBoxLayout(mWidget);
    mLayout->setMargin(0);
    mLayout->setSpacing(0);
    if (QToolBar *toolbar = qobject_cast<QToolBar*>(getWidgetByName("TOOLBAR"))) {
        mLayout->addWidget(toolbar);
    }
    mWidget->setLayout(mLayout);

    QTableView *mView = new QTableView(this);
    mLayout->addWidget(mView);
}

SysUserMgt::~SysUserMgt()
{

}

QString SysUserMgt::getCurText()
{
    return "Test Title";
}

