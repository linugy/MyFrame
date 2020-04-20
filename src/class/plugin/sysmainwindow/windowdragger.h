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

#ifndef WINDOWDRAGGER_H
#define WINDOWDRAGGER_H

#include <QMouseEvent>
#include <QWidget>

class WindowDragger : public QWidget {
  Q_OBJECT

 public:
  explicit WindowDragger(QWidget *parent = Q_NULLPTR);
  virtual ~WindowDragger() {}

public slots:
    bool isMousePressed();

 signals:
  void doubleClicked();

 protected:
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseDoubleClickEvent(QMouseEvent *event);
  void showEvent(QShowEvent *event);

 protected:
  QPoint mousePos;
  QPoint wndPos;
  bool mousePressed;
};

#endif  // WINDOWDRAGGER_H
