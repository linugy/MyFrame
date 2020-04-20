#ifndef MYQUICKBUTTON_H
#define MYQUICKBUTTON_H

#include <QToolButton>
#include <QVariant>
#include <QWidget>

class MyQuickButton : public QToolButton
{
    Q_OBJECT
public:
    explicit MyQuickButton(QWidget *parent = nullptr);
    ~MyQuickButton();

public slots:
    void setData(const QVariant &iDataVar);
    QVariant getData();

private:
    QVariant mData;
};

#endif // MYQUICKBUTTON_H
