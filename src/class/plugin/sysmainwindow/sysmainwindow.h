#ifndef SYSMAINWINDOW_H
#define SYSMAINWINDOW_H

#include "mycore/myclassabs.h"

class SysMainWindow : public MyClassAbs
{
    Q_OBJECT
public:
    explicit SysMainWindow(const QString &iModuleName, QWidget *parent = nullptr);
    ~SysMainWindow();

public slots:
    QString getCurText();

};

#endif // SYSMAINWINDOW_H
