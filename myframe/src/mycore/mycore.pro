#-------------------------------------------------
#
# Project created by QtCreator 2020-03-23T21:22:41
#
#-------------------------------------------------

QT       -= gui

TARGET = mycore
TEMPLATE = lib

DEFINES += MYCORE_LIBRARY

SOURCES += mycore.cpp

HEADERS += mycore.h\
        mycore_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
