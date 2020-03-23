#-------------------------------------------------
#
# Project created by QtCreator 2020-03-23T21:33:47
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = mywidget
TEMPLATE = lib

DEFINES += MYWIDGET_LIBRARY

SOURCES += mywidget.cpp

HEADERS += mywidget.h\
        mywidget_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
