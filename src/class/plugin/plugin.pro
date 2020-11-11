-------------------------------------------------
#
# Project created by QtCreator 2020-03-21T18:46:32
#
#-------------------------------------------------

QT       += widgets

TARGET = $$qtLibraryTarget(sysplugin)

QT += core  sql widgets script network xml scripttools

TEMPLATE = lib

CONFIG += plugin

SOURCES += plugin.cpp

HEADERS += plugin.h

include (./sysusermgt/sysusermgt.pri)
include (./sysmainwindow/sysmainwindow.pri)
include (./sysrolemgt/sysrolemgt.pri)

SDKPATH = $$PWD/../../../dist/qt5.6.3-win32-msvc2015

DESTDIR = $${SDKPATH}/bin_dbg/plugins

# 包含头文件
INCLUDEPATH += $${SDKPATH}/include

dest_dir = $${SDKPATH}/bin_dbg

win32 {
    DEBUG_SUFFIX = d
}

LIB_LIST = mycore mywidget mybaseutil

LIBS = -L$$dest_dir
for (lib, LIB_LIST) {
    LIBS += -l$${lib}$${DEBUG_SUFFIX}
}

