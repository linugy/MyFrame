﻿#include "sysmainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QPushButton>
#include <QFrame>
#include <QDebug>
#include <QApplication>
#include <QToolBar>
#include <QPalette>
#include <QToolButton>
#include <QStyle>
#include <QIcon>
#include <QStackedWidget>
#include <QTabBar>
#include <QWidget>
#include <QSplitter>
#include <QTreeWidget>
#include <mycore/mycore.h>
#include "windowdragger.h"
#include "myquicktoolbar.h"
#include "myquickbutton.h"

// padding 略小于 margin,确保形状改变时,鼠标总是在window里
#define MARGIN 1
#define PADDING 1.5


SysMainWindow::SysMainWindow(const QString &iModuleName, QWidget *parent)
    : MyClassAbs(parent)
{
    initModule(iModuleName);
    this->setMinimumSize(800, 600);
    initUi();
    setStyleSheet(QString("SysMainWindow{border:solid; border-color:#697d91; border-width:1px;}"));
    setMouseTracking(true);
    QApplication::instance()->installEventFilter(this);
}

SysMainWindow::~SysMainWindow()
{

}

void SysMainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mMainwindowPressed = true;
        dragPosition = event->globalPos() - this->frameGeometry().topLeft();
    }
    QWidget::mousePressEvent(event);
}

void SysMainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        mMainwindowPressed = false;
    }
    QWidget::mouseReleaseEvent(event);
}

bool SysMainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent *pMouse = dynamic_cast<QMouseEvent *>(event);
        if (pMouse) {
            QPoint gloPoint = pMouse->globalPos();
            if(!mMainwindowPressed && !mWindowTitleBar->isMousePressed()) {
                // 如果没有按下，那么就只修改鼠标形状
                changeCursor(gloPoint);
            }
            if (mMainwindowPressed && !mWindowTitleBar->isMousePressed()) {
                // 如果按下了，那么修改geometry
                changeGeometry(gloPoint);
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}

void SysMainWindow::showEvent(QShowEvent *event)
{
    this->setAttribute(Qt::WA_Mapped);
    QMainWindow::showEvent(event);
}

void SysMainWindow::onCloseBtnClicked()
{
    this->close();
}

void SysMainWindow::onMinBtnClicked()
{
    setWindowState(Qt::WindowMinimized);
}

void SysMainWindow::onRestoreBtnClicked()
{
    setWindowState(Qt::WindowNoState);
    changeButtonState();
}

void SysMainWindow::onMaxBtnClicked()
{
    setWindowState(Qt::WindowMaximized);
    showMaximized();
    changeButtonState();
}

void SysMainWindow::onQuickButtonClicked()
{
    if (MyQuickButton *btn = qobject_cast<MyQuickButton *>(sender())) {
        QVariantMap config = btn->getData().toMap();
        if (config.value("type").toString() == "module") {
            routeModule(config);
        } else if (config.value("type").toString() == "menu") {
            bool isSameMenu = false;
            if (mCurMenuBtn == btn) {
                isSameMenu = true;
            }
            mCurMenuBtn = btn;

            if (isSameMenu) {
                if (mExpandFrame->isHidden()) {
                    mExpandFrame->show();
                } else {
                    mExpandFrame->hide();
                }
            } else {
                mExpandFrame->show();
                // 展示menu内容
                routeMenu(config);
            }
        }
    }
}

void SysMainWindow::onTabCloseRequested(int index)
{
    QWidget *curWidget = mStackedWidget->widget(index);
    if (MyClassAbs *w = qobject_cast<MyClassAbs *>(curWidget)) {
        APP->deleteClass(w);
        mStackedWidget->removeWidget(curWidget);
        mTabBar->removeTab(index);
        openedModuleUrlLst.removeAt(index);
        delete curWidget;
        curWidget = nullptr;
    }
}

void SysMainWindow::onTabCurrentChanged(int index)
{
    mStackedWidget->setCurrentIndex(index);
}

void SysMainWindow::initUi()
{
    mMainWidget = new QWidget(this);
    setCentralWidget(mMainWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout(mMainWidget);
    mainLayout->setMargin(MARGIN);
    mainLayout->setSpacing(0);

    // 左侧quickToolBar
    mQuickToolBar = new MyQuickToolBar(mMainWidget);
    mQuickToolBar->setStyleSheet(QString("MyQuickToolBar{border:solid; border-color:#054280;"
                                         " border-width:1px; border-right-width:0px;"
                                         " spacing:0px;padding:0px;background-color:#11477e;}"));
    mQuickToolBar->setOrientation(Qt::Vertical);
    mainLayout->addWidget(mQuickToolBar);
    // 添加间隔
    QWidget *spacingWget = new QWidget(this);
    spacingWget->setFixedHeight(56);
    mQuickToolBar->addWidget(spacingWget);
    // 添加多个quickBtn到quickToolBar
    addQuickButtons();

    // 右侧splitter
    mSplitter = new QSplitter();
    mainLayout->addWidget(mSplitter);

    // expand
    mExpandFrame = new QFrame(mSplitter);
    mSplitter->addWidget(mExpandFrame);
    mExpandFrame->setStyleSheet(QString("QFrame{background-color:#e6e6e6;}"));
    mExpandFrame->setWindowFlags(Qt::FramelessWindowHint);
    mExpandFrame->setMinimumWidth(200);
    mExpandFrame->setMaximumWidth(400);
    mExpandFrame->hide();

    // menu
    mExpandLayout = new QVBoxLayout(mExpandFrame);
    mExpandLayout->setMargin(0);
    mExpandLayout->setSpacing(0);
    mMenuTree = new QTreeWidget(mExpandFrame);
    mMenuTree->setColumnCount(1);
    mMenuTree->setHeaderHidden(true);
    connect(mMenuTree, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(onMenuTreeItemClicked(QTreeWidgetItem*,int)));
    mExpandLayout->addWidget(mMenuTree);

    // 右侧主界面
    QWidget *bodyWidget = new QWidget(mSplitter);
    mSplitter->addWidget(bodyWidget);
    mSplitter->setCollapsible(0, false);
    QVBoxLayout *bodyLayout = new QVBoxLayout(bodyWidget);
    bodyLayout->setMargin(MARGIN);
    bodyLayout->setSpacing(0);

    mSplitter->setStretchFactor(0, 1);
    mSplitter->setStretchFactor(1, 10);

    // windowBar
    mWindowTitleBar = new WindowDragger(bodyWidget);
    bodyLayout->addWidget(mWindowTitleBar);
    mWindowTitleBar->setFixedHeight(50);
    mWindowTitleLayout = new QHBoxLayout(mWindowTitleBar);
    mWindowTitleLayout->setMargin(0);
    mWindowTitleLayout->setSpacing(0);
    mWindowTitleLayout->addStretch();
    // 添加多个系统按钮到windowBar
    addSysButtons();

    // 添加QTabBar
    QVBoxLayout *tabBarLayout = new QVBoxLayout();
    tabBarLayout->addStretch(1);
    mTabBar = new QTabBar();
    connect(mTabBar, SIGNAL(tabCloseRequested(int)), this, SLOT(onTabCloseRequested(int)));
    connect(mTabBar, SIGNAL(currentChanged(int)), this, SLOT(onTabCurrentChanged(int)));
    tabBarLayout->addWidget(mTabBar);
    mWindowTitleLayout->insertLayout(0, tabBarLayout);
    mTabBar->setTabsClosable(true);

    mStackedWidget = new QStackedWidget(bodyWidget);
    bodyLayout->addWidget(mStackedWidget);
    bodyLayout->addStretch();
}

void SysMainWindow::addQuickButtons()
{
    QToolButton *iconBtn = new QToolButton(this);
    iconBtn->setStyleSheet(QString("QToolButton{background-color:#0c3864; border:none; margin:0px;border-image:url(:/my/icon/erp.svg)}"));
    iconBtn->setFixedHeight(50);
    iconBtn->setFixedWidth(50);
    iconBtn->move(2, 2);

    QVariantList desktopLst = config("desktop").toList();
    for (QVariant var: desktopLst) {
        QVariantMap m = var.toMap();
        if (m.value("type").toString() == "module" || m.value("type").toString() == "menu") {
            MyQuickButton *btn = mQuickToolBar->addQuickButton(var.toMap());
            connect(btn, SIGNAL(clicked(bool)), this, SLOT(onQuickButtonClicked()));
        } else if (m.value("type").toString() == "strech") {
            QWidget *stretcher = new QWidget;
            stretcher->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
            mQuickToolBar->addWidget(stretcher);
        }
    }
}

void SysMainWindow::addSysButtons()
{
    // 最小化
    QPushButton *minBtn = new QPushButton(mWindowTitleBar);
    minBtn->setStyleSheet(QString("QPushButton{border:none;width:30px;height:30px;border-radius:5px;}"
                                  "QPushButton:hover{background-color:palette(alternate-base)}"));
    minBtn->setIcon(QApplication::style()->standardIcon((QStyle::SP_TitleBarMinButton)));
    mWindowTitleLayout->addWidget(minBtn);
    connect(minBtn, SIGNAL(clicked(bool)), this, SLOT(onMinBtnClicked()));

    // 还原
    restoreBtn = new QPushButton(mWindowTitleBar);
    restoreBtn->hide();
    restoreBtn->setStyleSheet(QString("QPushButton{border:none;width:30px;height:30px;border-radius:5px;}"
                                      "QPushButton:hover{background-color:palette(alternate-base)}"));
    restoreBtn->setIcon(QApplication::style()->standardIcon((QStyle::SP_TitleBarNormalButton)));
    mWindowTitleLayout->addWidget(restoreBtn);
    connect(restoreBtn, SIGNAL(clicked(bool)), this, SLOT(onRestoreBtnClicked()));

    // 最大化
    maxBtn = new QPushButton(mWindowTitleBar);
    maxBtn->setStyleSheet(QString("QPushButton{border:none;width:30px;height:30px;border-radius:5px;}"
                                  "QPushButton:hover{background-color:palette(alternate-base)}"));
    maxBtn->setIcon(QApplication::style()->standardIcon((QStyle::SP_TitleBarMaxButton)));
    mWindowTitleLayout->addWidget(maxBtn);
    connect(maxBtn, SIGNAL(clicked(bool)), this, SLOT(onMaxBtnClicked()));

    // 关闭按钮
    QPushButton *closeBtn = new QPushButton(mWindowTitleBar);
    closeBtn->setStyleSheet(QString("QPushButton{border:none;width:30px;height:30px;border-radius:5px;}"
                                    "QPushButton:hover{background-color:palette(alternate-base)}"));
    closeBtn->setIcon(QApplication::style()->standardIcon((QStyle::SP_TitleBarCloseButton)));
    mWindowTitleLayout->addWidget(closeBtn);
    connect(closeBtn, SIGNAL(clicked(bool)), this, SLOT(onCloseBtnClicked()));

}

void SysMainWindow::changeCursor(const QPoint &cursorGlobalPoint)
{
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());
    int x = cursorGlobalPoint.x();
    int y = cursorGlobalPoint.y();

    if(tl.x() + PADDING >= x && tl.x() <= x && tl.y() + PADDING >= y && tl.y() <= y) {
        // 左上角
        direction = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    } else if(x >= rb.x() - PADDING && x <= rb.x() && y >= rb.y() - PADDING && y <= rb.y()) {
        // 右下角
        direction = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    } else if(x <= tl.x() + PADDING && x >= tl.x() && y >= rb.y() - PADDING && y <= rb.y()) {
        //左下角
        direction = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= rb.x() && x >= rb.x() - PADDING && y >= tl.y() && y <= tl.y() + PADDING) {
        // 右上角
        direction = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= tl.x() + PADDING && x >= tl.x()) {
        // 左边
        direction = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    } else if( x <= rb.x() && x >= rb.x() - PADDING) {
        // 右边
        direction = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }else if(y >= tl.y() && y <= tl.y() + PADDING){
        // 上边
        direction = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    } else if(y <= rb.y() && y >= rb.y() - PADDING) {
        // 下边
        direction = DOWN;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    } else {
        // 默认
        direction = NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}

void SysMainWindow::changeGeometry(const QPoint &gloPoint)
{
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    if(direction != NONE) {
        QRect rMove(tl, rb);

        switch(direction) {
        case LEFT:
            if(rb.x() - gloPoint.x() <= this->minimumWidth())
                rMove.setX(tl.x());
            else
                rMove.setX(gloPoint.x());
            break;
        case RIGHT:
            rMove.setWidth(gloPoint.x() - tl.x());
            break;
        case UP:
            if(rb.y() - gloPoint.y() <= this->minimumHeight())
                rMove.setY(tl.y());
            else
                rMove.setY(gloPoint.y());
            break;
        case DOWN:
            rMove.setHeight(gloPoint.y() - tl.y());
            break;
        case LEFTTOP:
            if(rb.x() - gloPoint.x() <= this->minimumWidth())
                rMove.setX(tl.x());
            else
                rMove.setX(gloPoint.x());
            if(rb.y() - gloPoint.y() <= this->minimumHeight())
                rMove.setY(tl.y());
            else
                rMove.setY(gloPoint.y());
            break;
        case RIGHTTOP:
            rMove.setWidth(gloPoint.x() - tl.x());
            rMove.setY(gloPoint.y());
            break;
        case LEFTBOTTOM:
            rMove.setX(gloPoint.x());
            rMove.setHeight(gloPoint.y() - tl.y());
            break;
        case RIGHTBOTTOM:
            rMove.setWidth(gloPoint.x() - tl.x());
            rMove.setHeight(gloPoint.y() - tl.y());
            break;
        default:

            break;
        }
        this->setGeometry(rMove);
    }
}

void SysMainWindow::changeButtonState()
{
    if (this->isMaximized()) {
        restoreBtn->show();
        maxBtn->hide();
    } else {
        restoreBtn->hide();
        maxBtn->show();
    }
}

void SysMainWindow::routeModule(const QVariantMap &iMap)
{
    QString moduleUrl = iMap.value("url").toString();
    if (!moduleUrl.isEmpty()) {
        // 如果是同一个url，那么转到该模块；一个C++模块可以多次打开，例如德demo1和demo2
        if (openedModuleUrlLst.contains(moduleUrl)) {
            int index = openedModuleUrlLst.indexOf(moduleUrl);
            mStackedWidget->setCurrentIndex(index);
            mTabBar->setCurrentIndex(index);
        } else {
            openedModuleUrlLst.append(moduleUrl);
            QWidget *w = APP->openModuleUrl(moduleUrl);
            mStackedWidget->addWidget(w);
            int index = mTabBar->addTab(iMap.value("text").toString());
            mTabBar->setCurrentIndex(index);
        }
    }
}

void SysMainWindow::routeMenu(const QVariantMap &iMap)
{
    QString title = iMap.value("text").toString();
    QVariantList itemLst = iMap.value("item").toList();

    mMenuTree->clear();
    QTreeWidgetItem *rootItem = new QTreeWidgetItem();
    rootItem->setText(0, title);
    rootItem->setData(0, Qt::UserRole, iMap);
    for (int i = 0; i < itemLst.length(); i++) {
        QVariantMap m = itemLst.at(i).toMap();
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, m.value("text").toString());
        item->setData(0, Qt::UserRole, m);
        rootItem->addChild(item);
    }
    mMenuTree->addTopLevelItem(rootItem);
    mMenuTree->expandAll();
}

void SysMainWindow::onMenuTreeItemClicked(QTreeWidgetItem *iItem, int iColumn)
{
    Q_UNUSED(iColumn);
    QVariantMap m = iItem->data(0, Qt::UserRole).toMap();
    if (m.value("type").toString() == "module") {
        routeModule(m);
    }
}
