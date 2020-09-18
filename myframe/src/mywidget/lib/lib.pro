#-------------------------------------------------
#
# Project created by QtCreator 2020-03-23T21:33:47
#
#-------------------------------------------------

QT       += core script widgets

TARGET = $$qtLibraryTarget(mywidget)

DESTDIR = $$PWD/../../../../dist/qt5.6.3-win32-msvc2015/bin_dbg

TEMPLATE = lib

DEFINES += MYWIDGET_LIBRARY

SOURCES += mywidget.cpp \
    mylogindialog.cpp

HEADERS += mywidget.h\
        mywidget_global.h \
    mylogindialog.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

### 查看SDK头文件目标路径是否存在，不存在则创建
SDK_HEADER_PATH = $$system_path($$PWD/../../../../dist/qt5.6.3-win32-msvc2015/include/mywidget)
!exists($${SDK_HEADER_PATH}) {
    mkpath($${SDK_HEADER_PATH})
}

###
system(copy *.h $${SDK_HEADER_PATH})
