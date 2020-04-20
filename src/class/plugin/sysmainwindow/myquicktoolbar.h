#ifndef MYQUICKTOOLBAR_H
#define MYQUICKTOOLBAR_H

#include <QVariant>
#include <QVariantList>
#include <QToolBar>

class QActionGroup;
class QToolBar;
class QWidget;
class MyQuickButton;

class MyQuickToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit MyQuickToolBar(QWidget *parent = nullptr);
    ~MyQuickToolBar();

public slots:
    void loadQuickButtons(const QVariantList &iVarLst);
    MyQuickButton *addQuickButton(const QVariantMap &iParamMap);
    void clearAllButtons();

protected:
    void showEvent(QShowEvent *event);

private:
    MyQuickButton *createQuickBtn(const QVariantMap &iParamMap);

private:
    QActionGroup *mToolBarActions;
};

#endif // MYQUICKTOOLBAR_H
