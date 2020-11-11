#-------------------------------------------------
#
# Project created by QtCreator 2020-04-07T10:11:30
#
#-------------------------------------------------

QT       += core script widgets

TARGET = $$qtLibraryTarget(ecma_mywidget)

TEMPLATE = lib

SOURCES += mywidgetecmabinding.cpp

HEADERS += mywidgetecmabinding.h

SDKPATH = $$PWD/../../../../dist/qt5.6.3-win32-msvc2015

DESTDIR = $${SDKPATH}/bin_dbg/script

# 包含头文件
INCLUDEPATH += $${SDKPATH}/include

dest_dir = $${SDKPATH}/bin_dbg

LIB_LIST = mybaseutil mywidget

win32 {
    DEBUG_SUFFIX = d
}

LIBS = -L$$dest_dir

for (lib, LIB_LIST) {
    LIBS += -l$${lib}$${DEBUG_SUFFIX}
}
