#ifndef MYPANELMENU_H
#define MYPANELMENU_H

#include <QScrollArea>
#include <QVariant>

class MyPanelItem;
class MyPanelMenuPrivate;

class MyPanelMenu : public QScrollArea
{
    Q_OBJECT
public:
    explicit MyPanelMenu(QWidget *parent = 0);
    ~MyPanelMenu();

public slots:
    void setItemList(const QVariant &data);

signals:
    void clicked(const QVariant &data);

private slots:
    void onClicked(const QVariant &data);

protected:
    const QScopedPointer<MyPanelMenuPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MyPanelMenu)
    Q_DECLARE_PRIVATE(MyPanelMenu)
};

#endif // MYPANELMENU_H
