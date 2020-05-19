#include "mypanelitem.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>

MyPanelItem::MyPanelItem(QWidget *parent, int hierarchy)
    : QWidget(parent)
{
    mHierarchy = hierarchy;
    initWidget();
}

void MyPanelItem::setData(const QVariantMap &iDataMap)
{
//    mLabel->setText(iDataMap.value("title").toString());
//    QVariantList childList = iDataMap[mDataKeyHash["child_list_key"]].toList();
//    if (childList.count() > 0) {
//        mRightButton->setIcon(TRES->colorIcon("angle-down.#777777"));
//        for (QVariant value : childList) {
//            QVariantMap dataMap = value.toMap();
//            if (dataMap[mDataKeyHash["status_key"]].toString() == "hide") {
//                continue;
//            }
//            TPanelItem *child = new TPanelItem(this, mHierarchy + 1);
//            mChildList.append(child);
//            mLayout->addWidget(child);
//            child->setVisible(false);
//            connect(child, SIGNAL(activeChange(bool)), this, SLOT(onActiveChange(bool)));
//            connect(child, SIGNAL(selectChange(QVariant)), this, SLOT(selected(QVariant)));
//            connect(child, SIGNAL(clicked(QVariant)), this, SLOT(click(QVariant)));
//            child->setKeys(mDataKeyHash);
//            child->setData(dataMap);
//        }
//    } else {
//        mRightButton->setVisible(false);
//    }
//    mData = iDataMap;
//    QVariantMap data = iDataMap;
//    if (!data.contains(mDataKeyHash["tool_tip_key"])) {
//        data[mDataKeyHash["tool_tip_key"]] = iDataMap[mDataKeyHash["text_key"]].toString();
//    }
//    mTitleWidget->setToolTip(data[mDataKeyHash["tool_tip_key"]].toString());
//    if (iDataMap[mDataKeyHash["unfold_key"]].toBool()) {
//        setChildrenVisible(true);
//    }
//    if (iDataMap[mDataKeyHash["active_key"]].toBool()) {
//        setActive(true);
//    }
}

void MyPanelItem::initWidget()
{
    setStyleSheet("padding:0px;margin:0px");

    mLayout = new QVBoxLayout(this);
    mLayout->setMargin(0);
    mLayout->setSpacing(0);

    mTitleWidget = new QPushButton(this);
    mLayout->addWidget(mTitleWidget);
    mTitleWidget->setStyleSheet(".QPushButton:pressed{border-color:none;border-width:0px;border-style:solid;}\
                                 .QPushButton{background-color:#F1F1F1;padding:0px;border-radius:0px;}\
                                .QPushButton:hover{background-color:#E8E8E8}");
    connect(mTitleWidget, SIGNAL(clicked(bool)), this, SLOT(onClick()));

    QHBoxLayout *titleLayout = new QHBoxLayout(mTitleWidget);
    titleLayout->addSpacing(20 * mHierarchy);

    mLabel = new QLabel(this);
    mLabel->setStyleSheet("background-color:none");
    titleLayout->addWidget(mLabel);
    titleLayout->addStretch();

    mRightButton = new QToolButton(this);
    titleLayout->addWidget(mRightButton);
    QString styleSheet = QString(".QToolButton:pressed{border-color:none;border-width:0px;border-style:solid;}\
                          .QToolButton{background-color:none;icon-size:%1px;border:none;}").arg(18);
    mRightButton->setStyleSheet(styleSheet);
    connect(mRightButton, SIGNAL(clicked(bool)), this, SLOT(onClick()));
}
