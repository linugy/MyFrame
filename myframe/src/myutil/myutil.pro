#-------------------------------------------------
#
# Project created by QtCreator 2020-03-23T21:33:08
#
#-------------------------------------------------

QT       += core gui script xml network sql serialport scripttools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myutil
TEMPLATE = lib

DEFINES += MYUTIL_LIBRARY

SOURCES += myutil.cpp \
    mymain.cpp \
    mylogin.cpp

HEADERS += myutil.h\
        myutil_global.h \
    mymain.h \
    mylogin.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

