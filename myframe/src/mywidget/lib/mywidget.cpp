#include "mywidget.h"

class MyWidgetPrivate
{
    Q_DECLARE_PUBLIC(MyWidget)
public:
    explicit MyWidgetPrivate(MyWidget *qptr);
    ~MyWidgetPrivate();

protected:
    MyWidget * const q_ptr;

};

MyWidgetPrivate::MyWidgetPrivate(MyWidget *qptr) :
    q_ptr(qptr)
{
}

MyWidgetPrivate::~MyWidgetPrivate()
{
}

//------end----------

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent), d_ptr(new MyWidgetPrivate(this))
{
}

MyWidget::~MyWidget()
{

}
