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

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DESTDIR = $$PWD/../../../../dist/qt5.6.3-win32-msvc2015/bin_dbg

# sdk path
SDKPATH = $$PWD/../../../../dist/qt5.6.3-win32-msvc2015

# include headers
INCLUDEPATH += $${SDKPATH}/include

# debug suffix
win32 {
    DEBUG_SUFFIX = d
}

LIB_LIST = mybaseutil mywidget

#
des_dir = $$PWD/../../../../dist/qt5.6.3-win32-msvc2015/bin_dbg

# libs
LIBS = -L$$des_dir
for (lib, LIB_LIST) {
    LIBS += -l$${lib}$${DEBUG_SUFFIX}
}

DESTDIR = $${DESTDIR}/script
