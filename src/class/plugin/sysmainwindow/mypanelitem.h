#ifndef MYPANELITEM_H
#define MYPANELITEM_H

#include <QWidget>
#include <QVariant>
#include <QPushButton>

class QLabel;
class QVBoxLayout;
class QToolButton;

class MyPanelItem : public QWidget
{
    Q_OBJECT
public:
    MyPanelItem(QWidget *parent = 0, int hierarchy = 0);

public slots:
    void setData(const QVariantMap &iDataMap);

private:
    void initWidget();
private:
    int mHierarchy = 0;
    QVBoxLayout *mLayout = nullptr;
    QPushButton *mTitleWidget = nullptr;
    QToolButton *mRightButton = nullptr;
    QLabel *mLabel = nullptr;
    QList<MyPanelItem*> mChildList;
};

#endif // MYPANELITEM_H
