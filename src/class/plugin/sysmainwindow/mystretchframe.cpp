#include "mystretchframe.h"
#include <QEvent>

MyStretchFrame::MyStretchFrame(QWidget *iParent)
    : QFrame(iParent)
{

}

MyStretchFrame::~MyStretchFrame()
{

}

void MyStretchFrame::setWidget(QWidget *iWidget)
{

}

void MyStretchFrame::setStretchWidgetVisible(bool iVisible)
{

}

void MyStretchFrame::mousePressEvent(QMouseEvent *event)
{

}

void MyStretchFrame::mouseReleaseEvent(QMouseEvent *)
{

}

bool MyStretchFrame::event(QEvent *event)
{
//    if (event->type() == QEvent::HoverMove) {
//        QHoverEvent *hoverEvent = static_cast<QHoverEvent *>(event);
//        QPoint pos = hoverEvent->pos();
//        QPoint gp = mapToGlobal(pos);
//        if (hoverEvent && !mLeftButtonPressed && (windowFlags() & Qt::Popup)) {
//            QPoint br = QPoint(this->width(), this->height());
//            int x = pos.x();
//            bool widthReizable = (this->minimumWidth() != this->maximumWidth());
//            if (x < br.x() && x >= br.x() - mStretchWidgetWidth && widthReizable) {
//                if (cursor().shape() != Qt::SizeHorCursor) {
//                    QApplication::setOverrideCursor(QCursor(Qt::SizeHorCursor));
//                    setCursor(QCursor(Qt::SizeHorCursor));
//                }
//            } else if (cursor().shape() != Qt::ArrowCursor) {
//                QApplication::restoreOverrideCursor();
//                setCursor(QCursor(Qt::ArrowCursor));
//            }
//        } else if (mLeftButtonPressed && (cursor().shape() == Qt::SizeHorCursor)) {
//            QRect rect = this->rect();
//            QPoint tl = mapToGlobal(rect.topLeft()); //top left
//            QPoint br = mapToGlobal(rect.bottomRight()); //bottom right
//            QRect rectMove(tl, br);
//            if (gp.x() - tl.x() > minimumWidth()){
//                rectMove.setWidth(gp.x() - tl.x());
//            }
//            this->setGeometry(rectMove);
//        }
//    } else if (event->type() == QEvent::Resize) {
//        if (mWidget != nullptr) {
//            qreal width = size().width();
//            qreal height = size().height();
//            mWidget->resize(width, height);
//        }
//        const QRect rect = geometry();
//        mStretchWidget->setGeometry((rect.width() - mStretchWidgetWidth),
//                                    0, mStretchWidgetWidth, rect.height());
//        mStretchWidget->raise();
//    } else if (event->type() == QEvent::Hide) {
//        mLeftButtonPressed = false;
//        QApplication::restoreOverrideCursor();
//    } else if (event->type() == QEvent::Show) {
//        setFocus();
//    }

    return QFrame::event(event);
}

void MyStretchFrame::showEvent(QShowEvent *event)
{

}
