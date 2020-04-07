#include "sysusermgt.h"
#include <mywidget/mywidget.h>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <mycore/mycore.h>
//#include <mybaseutil/myscriptengine.h>

SysUserMgt::SysUserMgt()
{
    qDebug() << "=====SysUserMgt======";

    mWidget = new MyWidget(this);
    mWidget->setStyleSheet("QWidget{background: gray}");
    QHBoxLayout *myLayout = new QHBoxLayout(mWidget);
    QLabel *label = new QLabel("myLabel");
    myLayout->addWidget(label);
    mWidget->setLayout(myLayout);
    this->setCentralWidget(mWidget);

    APP->scriptEngine()->evaluate("print('---111---'); var widget = new MyWidget; widget.setWindowTitle('testMyWidget');widget.show()");
}

SysUserMgt::~SysUserMgt()
{

}

