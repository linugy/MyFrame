#include "mypanelmenu.h"
#include <QVBoxLayout>
#include <QVariant>
#include <QWidget>
#include "mypanelitem.h"

class MyPanelMenuPrivate
{
    Q_DECLARE_PUBLIC(MyPanelMenu)
public:
    explicit MyPanelMenuPrivate(MyPanelMenu *qptr);
    ~MyPanelMenuPrivate();

protected:
    MyPanelMenu * const q_ptr;
    QList<MyPanelItem *> childList;
    QVariant itemList;
    QVBoxLayout *layout = nullptr;
};

MyPanelMenuPrivate::MyPanelMenuPrivate(MyPanelMenu *qptr) :
    q_ptr(qptr)
{
}

MyPanelMenuPrivate::~MyPanelMenuPrivate()
{
}

// ========end=========

MyPanelMenu::MyPanelMenu(QWidget *parent)
    : QScrollArea(parent),d_ptr(new MyPanelMenuPrivate(this))
{
    Q_D(MyPanelMenu);
    QWidget *mainWidget = new QWidget(this);
    setWidget(mainWidget);
    d->layout = new QVBoxLayout(mainWidget);
    d->layout->setMargin(0);
    d->layout->setSpacing(0);
    mainWidget->setStyleSheet("background-color:#F1F1F1;");
    setWidgetResizable(true);
}

MyPanelMenu::~MyPanelMenu()
{

}

/**
* \brief 设置所有的桌面模块配置信息
*/
void MyPanelMenu::setItemList(const QVariant &data)
{
    Q_D(MyPanelMenu);
    QLayoutItem* child;
    while((child = d->layout->takeAt(0)) != 0) {
        if(child->widget() != 0) {
            delete child->widget();
        }
        delete child;
    }

    if (data.type() == QVariant::Type::List) {
        for (QVariant var : data.toList()) {
            QVariantMap m = var.toMap();
            MyPanelItem *item = new MyPanelItem(this);
            item->setData(m);
            d->layout->addWidget(item);
            connect(item, SIGNAL(clicked(QVariant)), this, SLOT(onClicked(QVariant)));
        }
    }
}

void MyPanelMenu::onClicked(const QVariant &data)
{
    emit clicked(data);
}
