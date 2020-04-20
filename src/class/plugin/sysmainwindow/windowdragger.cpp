/*
###############################################################################
#                                                                             #
# The MIT License                                                             #
#                                                                             #
# Copyright (C) 2017 by Juergen Skrotzky (JorgenVikingGod@gmail.com)          #
#               >> https://github.com/Jorgen-VikingGod                        #
#                                                                             #
# Sources: https://github.com/Jorgen-VikingGod/Qt-Frameless-Window-DarkStyle  #
#                                                                             #
###############################################################################
*/

#include "windowdragger.h"
#include <QPainter>
#include <QDebug>
#include <QPalette>

WindowDragger::WindowDragger(QWidget *parent)
    : QWidget(parent)
{
  mousePressed = false;
  this->setFixedHeight(30);
  QPalette pal(this->palette());

  //设置背景黑色
  pal.setColor(QPalette::Background, QColor("#1E90FF"));
  this->setAutoFillBackground(true);
  this->setPalette(pal);

}

void WindowDragger::mousePressEvent(QMouseEvent *event) {
  mousePressed = true;
  mousePos = event->globalPos();
  QWidget *parent = parentWidget();
  if (parent) parent = parent->parentWidget();
  if (parent) parent = parent->parentWidget();
  if (parent) {
      wndPos = parent->pos();
  }
}

void WindowDragger::mouseMoveEvent(QMouseEvent *event) {
  QWidget *parent = parentWidget();
  if (parent) parent = parent->parentWidget();
  if (parent) parent = parent->parentWidget();

//  this->setCursor(QCursor(Qt::ArrowCursor));
  if (parent && mousePressed)
    parent->move(wndPos + (event->globalPos() - mousePos));
}

void WindowDragger::mouseReleaseEvent(QMouseEvent *event) {
  Q_UNUSED(event);
  mousePressed = false;
}

void WindowDragger::mouseDoubleClickEvent(QMouseEvent *event) {
  Q_UNUSED(event);
  emit doubleClicked();
}
