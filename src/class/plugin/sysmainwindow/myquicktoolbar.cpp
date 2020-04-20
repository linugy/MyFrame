#include "myquicktoolbar.h"
#include <QActionGroup>
#include "myquickbutton.h"
#include <QPalette>
#include <QPainter>
#include <QColor>

MyQuickToolBar::MyQuickToolBar(QWidget *parent)
    : QToolBar(parent)
{
    mToolBarActions = new QActionGroup(this);
    // 设值背景色
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, QColor("#1E90FF"));
    setAutoFillBackground(true);
    setPalette(pal);
}

MyQuickToolBar::~MyQuickToolBar()
{

}

void MyQuickToolBar::loadQuickButtons(const QVariantList &iVarLst)
{
    for (QVariant var: iVarLst) {
        addQuickButton(var.toMap());
    }
}

MyQuickButton *MyQuickToolBar::addQuickButton(const QVariantMap &iParamMap)
{
    MyQuickButton *btn = createQuickBtn(iParamMap);
    btn->setToolButtonStyle(Qt::ToolButtonIconOnly);
    mToolBarActions->addAction(addWidget(btn));
    return btn;
}

void MyQuickToolBar::clearAllButtons()
{
    QList<QAction *> listAction = mToolBarActions->actions();
    for (QAction *act: listAction) {
        mToolBarActions->removeAction(act);
        this->removeAction(act);
        act->deleteLater();
    }
}

void MyQuickToolBar::showEvent(QShowEvent *event)
{
    this->setAttribute(Qt::WA_Mapped);
    QToolBar::showEvent(event);
}

MyQuickButton *MyQuickToolBar::createQuickBtn(const QVariantMap &iParamMap)
{
    MyQuickButton *btn = new MyQuickButton();
    btn->setText(iParamMap.value("title").toString());
    return btn;
}
