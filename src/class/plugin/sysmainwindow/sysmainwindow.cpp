#include "sysmainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <mycore/mycore.h>
#include <QDebug>
#include <QApplication>
#include <QToolBar>
#include <QPalette>
#include <QToolButton>
#include <QStyle>
#include <QIcon>
#include "windowdragger.h"
#include "myquicktoolbar.h"
#include "myquickbutton.h"

#define MARGIN 1
#define PADDING 1

SysMainWindow::SysMainWindow(const QString &iModuleName, QWidget *parent)
    : MyClassAbs(parent)
{
    initModule(iModuleName);
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
            if(!mMainwindowPressed) {
                // 如果没有按下，那么就只修改鼠标形状
                changeCursor(gloPoint);
            } else {
                // 如果按下了，那么修改geometry
                changeGeometry(gloPoint);
            }
            QWidget::mouseMoveEvent(pMouse);
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

void SysMainWindow::initUi()
{
    mMainWidget = new QWidget(this);
    setCentralWidget(mMainWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout(mMainWidget);
    mainLayout->setMargin(MARGIN);
    mainLayout->setSpacing(0);

    // 左侧quickToolBar
    mQuickToolBar = new MyQuickToolBar(mMainWidget);
    mQuickToolBar->setStyleSheet(QString("QToolBar{border:solid; border-color:#D5D5D5; border-width:0px; border-right-width:0px; spacing:0px;padding:0px;background-color:#367fc9;}"));
    mQuickToolBar->setOrientation(Qt::Vertical);
    mainLayout->addWidget(mQuickToolBar);
    // 添加间隔
    QWidget *spacingWget = new QWidget(this);
    spacingWget->setFixedHeight(56);
    mQuickToolBar->addWidget(spacingWget);
    // 添加多个quickBtn到quickToolBar
    addQuickButtons();

    // 右侧主界面
    QWidget *bodyWidget = new QWidget(mMainWidget);
    mainLayout->addWidget(bodyWidget);
    QVBoxLayout *bodyLayout = new QVBoxLayout(bodyWidget);
    bodyLayout->setMargin(0);
    bodyLayout->setSpacing(0);

    // windowBar
    mWindowTitleBar = new WindowDragger(mMainWidget);
    bodyLayout->addWidget(mWindowTitleBar);
    mWindowTitleBar->setFixedHeight(50);
    mWindowTitleLayout = new QHBoxLayout(mWindowTitleBar);
    mWindowTitleLayout->setMargin(0);
    mWindowTitleLayout->setSpacing(0);
    mWindowTitleLayout->addStretch();
    // 添加多个系统按钮到windowBar
    addSysButtons();

    bodyLayout->addStretch();
}

void SysMainWindow::addQuickButtons()
{
    QToolButton *iconBtn = new QToolButton(this);
    iconBtn->setStyleSheet(QString("QToolButton{background-color: #2f69a2; border:none; margin:0px;}"));
    iconBtn->setIcon(QApplication::style()->standardIcon((QStyle::SP_TitleBarMenuButton)));
    iconBtn->setFixedHeight(50);
    iconBtn->setFixedWidth(50);
    iconBtn->move(1, 1);

    QVariantList lst;
    QVariantMap m;
    m.insert("title", "A");
    lst.append(m);
    m.insert("title", "B");
    lst.append(m);
    mQuickToolBar->loadQuickButtons(lst);

    // 添加间隔
    QWidget *stretcher = new QWidget;
    stretcher->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    mQuickToolBar->addWidget(stretcher);

    QToolButton *sysBtn = new QToolButton(mWindowTitleBar);
    sysBtn->setFixedHeight(50);
    sysBtn->setFixedWidth(50);
    sysBtn->setText("SYS");
    mQuickToolBar->addAction(mQuickToolBar->addWidget(sysBtn));
}

void SysMainWindow::addSysButtons()
{
    // 关闭按钮
    QPushButton *closeBtn = new QPushButton(mWindowTitleBar);
    closeBtn->setFixedHeight(40);
    closeBtn->setFixedWidth(40);
    closeBtn->setText("X");
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
    }else {
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
