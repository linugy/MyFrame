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

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include (./sysusermgt/sysusermgt.pri)


# sdk path
SDKPATH = $$PWD/../../../dist/qt5.6.3-win32-msvc2015

# include headers
INCLUDEPATH += $${SDKPATH}/include

# debug suffix
win32 {
    DEBUG_SUFFIX = d
}

LIB_LIST = mycore mywidget mybaseutil

#
des_dir = $$PWD/../../../dist/qt5.6.3-win32-msvc2015/bin_dbg

# libs
LIBS = -L$$des_dir
for (lib, LIB_LIST) {
    LIBS += -l$${lib}$${DEBUG_SUFFIX}
}

DESTDIR = $$PWD/../../../dist/qt5.6.3-win32-msvc2015/bin_dbg/plugins
