#-------------------------------------------------
#
# Project created by QtCreator 2020-03-23T21:25:13
#
#-------------------------------------------------

QT       += sql

QT       -= gui

TARGET = mydatabaseutil
TEMPLATE = lib

DEFINES += MYDATABASEUTIL_LIBRARY

SOURCES += mydatabaseutil.cpp

HEADERS += mydatabaseutil.h\
        mydatabaseutil_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
