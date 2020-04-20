#include "myquickbutton.h"
#include <QPalette>

MyQuickButton::MyQuickButton(QWidget *parent)
    : QToolButton(parent)
{
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
