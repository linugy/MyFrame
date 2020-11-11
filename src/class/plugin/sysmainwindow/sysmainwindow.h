#ifndef SYSMAINWINDOW_H
#define SYSMAINWINDOW_H

#include "mycore/myclassabs.h"
#include <QMouseEvent>

class QWidget;
class QHBoxLayout;
class WindowDragger;
class MyQuickToolBar;
class MyQuickButton;
class QPushButton;
class QStackedWidget;
class QTabBar;
class QFrame;

class SysMainWindow : public MyClassAbs
{
    Q_OBJECT
    enum Direction{
        UP = 0,
        DOWN=1,
        LEFT,
        RIGHT,
        LEFTTOP,
        LEFTBOTTOM,
        RIGHTBOTTOM,
        RIGHTTOP,
        NONE
    };
public:
    explicit SysMainWindow(const QString &iModuleName, QWidget *parent = nullptr);
    ~SysMainWindow();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    virtual bool eventFilter(QObject *obj, QEvent *event);
    void showEvent(QShowEvent *event);

private slots:
    void onCloseBtnClicked();
    void onMinBtnClicked();
    void onRestoreBtnClicked();
    void onMaxBtnClicked();
    void onQuickButtonClicked();
    void onTabCloseRequested(int index);
    void onTabCurrentChanged(int index);

private:
    void initUi();
    void addQuickButtons();
    void addSysButtons();
    void changeCursor(const QPoint &cursorGlobalPoint);
    void changeGeometry(const QPoint &gloPoint);
    void changeButtonState();
    void routeModule(const QVariantMap &iMap);

private:
    QWidget *mMainWidget = nullptr;
    MyQuickToolBar *mQuickToolBar = nullptr;
    WindowDragger *mWindowTitleBar = nullptr;
    QHBoxLayout *mWindowTitleLayout = nullptr;
    bool mMainwindowPressed= false;
    QPoint dragPosition;
    Direction direction = NONE;
    QPushButton *restoreBtn = nullptr;
    QPushButton *maxBtn = nullptr;
    QTabBar *mTabBar = nullptr;
    QStackedWidget *mStackedWidget = nullptr;
    QStringList openedModuleUrlLst;
};

#endif // SYSMAINWINDOW_H
