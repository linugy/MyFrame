#include "myquickbutton.h"
#include <QPalette>

MyQuickButton::MyQuickButton(QWidget *parent)
    : QToolButton(parent)
{
    setStyleSheet(QString("MyQuickButton{margin:%1px; border:none; background:#265BC9; border-radius:%2px;color:#FFFFFF;}\n" \
                          "MyQuickButton:hover{border-radius:%3px}\n" \
                          "QToolButton::menu-indicator{image:None;}")
                  .arg(6).arg(10).arg(16));
    setFixedSize(50, 50);
}

MyQuickButton::~MyQuickButton()
{

}

void MyQuickButton::setData(const QVariant &iDataVar)
{
    mData = iDataVar;
}

QVariant MyQuickButton::getData()
{
    return mData;
}
