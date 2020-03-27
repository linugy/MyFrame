#-------------------------------------------------
#
# Project created by QtCreator 2020-03-23T21:33:47
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = mywidget

DESTDIR = $$PWD/../../../dist/qt5.6.3-win32-msvc2015/bin_dbg

TEMPLATE = lib

DEFINES += MYWIDGET_LIBRARY

SOURCES += mywidget.cpp

HEADERS += mywidget.h\
        mywidget_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
