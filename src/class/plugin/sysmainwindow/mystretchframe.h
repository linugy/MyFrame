#ifndef MYSTRETCHFRAME_H
#define MYSTRETCHFRAME_H

#include <QFrame>

class QHBoxLayout;
class QWidget;

class MyStretchFrame: public QFrame {
    Q_OBJECT
public:
    MyStretchFrame(QWidget* iParent = nullptr);
    ~MyStretchFrame();
    void setWidget(QWidget *iWidget);
    void setStretchWidgetVisible(bool iVisible);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    bool event(QEvent *event);
    void showEvent(QShowEvent *event);

private:
    bool mLeftButtonPressed = false;
    QPoint mDragPosition;
    qreal mStretchWidgetWidth = 1;
    bool mMouseAnchor = false;
    QWidget *mWidget = nullptr;
    QFrame *mStretchWidget = nullptr;
    QHBoxLayout *mLayout = nullptr;
};

#endif // MYSTRETCHFRAME_H
