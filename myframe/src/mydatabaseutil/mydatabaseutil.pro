#-------------------------------------------------
#
# Project created by QtCreator 2020-03-23T21:25:13
#
#-------------------------------------------------

QT       += sql

QT       -= gui

TARGET = mydatabaseutil

DESTDIR = $$PWD/../../../dist/qt5.6.3-win32-msvc2015/bin_dbg

TEMPLATE = lib

DEFINES += MYDATABASEUTIL_LIBRARY

SOURCES += mydatabaseutil.cpp

HEADERS += mydatabaseutil.h\
        mydatabaseutil_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
