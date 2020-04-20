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
#include "windowdragger.h"

#define MARGIN 5
#define PADDING 5

SysMainWindow::SysMainWindow(const QString &iModuleName, QWidget *parent)
    : MyClassAbs(parent)
{
    initModule(iModuleName);
    initUi();
    // 设值背景色
//    QPalette pal(this->palette());
//    pal.setColor(QPalette::Background, QColor("#1E90FF"));
//    setAutoFillBackground(true);
//    setPalette(pal);

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
    mQuickToolBar = new QToolBar(mMainWidget);
    mQuickToolBar->setOrientation(Qt::Vertical);
    mainLayout->addWidget(mQuickToolBar);
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
    QPushButton *iconBtn = new QPushButton(mQuickToolBar);
    iconBtn->setFixedHeight(40);
    iconBtn->setFixedWidth(40);
    iconBtn->setText("A");
    mQuickToolBar->addWidget(iconBtn);
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
