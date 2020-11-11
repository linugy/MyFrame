#ifndef MYWIDGET_H
#define MYWIDGET_H

#include "mywidget_global.h"
#include <QWidget>

class MyWidgetPrivate;

class MYWIDGETSHARED_EXPORT MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

public slots:
    void setSize(int width, int height);

protected:
    const QScopedPointer<MyWidgetPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MyWidget)
    Q_DECLARE_PRIVATE(MyWidget)
};

#endif // MYWIDGET_H
