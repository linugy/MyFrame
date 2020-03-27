#-------------------------------------------------
#
# Project created by QtCreator 2020-03-23T21:21:55
#
#-------------------------------------------------

QT       -= gui

TARGET = mychart

DESTDIR = $$PWD/../../../dist/qt5.6.3-win32-msvc2015/bin_dbg

TEMPLATE = lib

DEFINES += MYCHART_LIBRARY

SOURCES += mychart.cpp

HEADERS += mychart.h\
        mychart_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
