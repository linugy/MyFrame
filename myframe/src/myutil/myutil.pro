#-------------------------------------------------
#
# Project created by QtCreator 2020-03-23T21:33:08
#
#-------------------------------------------------

QT       -= gui

TARGET = myutil
TEMPLATE = lib

DEFINES += MYUTIL_LIBRARY

SOURCES += myutil.cpp

HEADERS += myutil.h\
        myutil_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
