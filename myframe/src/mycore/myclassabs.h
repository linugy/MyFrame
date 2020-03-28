#ifndef MYCLASSABS_H
#define MYCLASSABS_H

#include <QMainWindow>
#include "mycore_global.h"

class MYCORESHARED_EXPORT MyClassAbs : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyClassAbs(QWidget *parent = 0);
    ~MyClassAbs();

signals:

public slots:

};

#endif // MYCLASSABS_H
