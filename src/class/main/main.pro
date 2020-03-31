#-------------------------------------------------
#
# Project created by QtCreator 2020-03-21T14:36:09
#
#-------------------------------------------------

QT       += core widgets

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyProject

DESTDIR = $$PWD/../../../dist/qt5.6.3-win32-msvc2015/bin_dbg

TEMPLATE = app

SOURCES += main.cpp\

# sdk path
SDKPATH = $$PWD/../../../dist/qt5.6.3-win32-msvc2015

# include headers
INCLUDEPATH += $${SDKPATH}/include

# debug suffix
win32 {
    DEBUG_SUFFIX = d
}

LIB_LIST = mycore myutil

# libs
LIBS += -L$$DESTDIR
for (lib, LIB_LIST) {
    LIBS += -l$${lib}$${DEBUG_SUFFIX}
}
