#-------------------------------------------------
#
# Project created by QtCreator 2020-03-23T21:25:54
#
#-------------------------------------------------

QT       -= gui

TARGET = myexcel
TEMPLATE = lib

DEFINES += MYEXCEL_LIBRARY

SOURCES += myexcel.cpp

HEADERS += myexcel.h\
        myexcel_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
