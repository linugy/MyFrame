#-------------------------------------------------
#
# Project created by QtCreator 2020-03-23T21:20:52
#
#-------------------------------------------------

QT       -= gui

TARGET = mybaseutil
TEMPLATE = lib

DEFINES += MYBASEUTIL_LIBRARY

SOURCES += mybaseutil.cpp

HEADERS += mybaseutil.h\
        mybaseutil_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
