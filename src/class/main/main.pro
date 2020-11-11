#-------------------------------------------------
#
# Project created by QtCreator 2020-03-21T14:36:09
#
#-------------------------------------------------

QT       += core widgets script

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyProject

DESTDIR = $$PWD/../../../dist/qt5.6.3-win32-msvc2015/bin_dbg

TEMPLATE = app

SOURCES += main.cpp\

SDKPATH = $$PWD/../../../dist/qt5.6.3-win32-msvc2015

# 包含头文件
INCLUDEPATH += $${SDKPATH}/include

dest_dir = $${SDKPATH}/bin_dbg

LIB_LIST = mycore myutil

win32 {
    DEBUG_SUFFIX = d
}

LIBS = -L$$dest_dir

for (lib, LIB_LIST) {
    LIBS += -l$${lib}$${DEBUG_SUFFIX}
}
