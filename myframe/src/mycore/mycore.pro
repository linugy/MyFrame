#-------------------------------------------------
#
# Project created by QtCreator 2020-03-23T21:22:41
#
#-------------------------------------------------

QT       -= gui

TARGET = $$qtLibraryTarget(mycore)

DESTDIR = $$PWD/../../../dist/qt5.6.3-win32-msvc2015/bin_dbg

TEMPLATE = lib

DEFINES += MYCORE_LIBRARY

SOURCES += mycore.cpp

HEADERS += mycore.h\
        mycore_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

### 查看SDK头文件目标路径是否存在，不存在则创建
SDK_HEADER_PATH = $$system_path($$PWD/../../../dist/qt5.6.3-win32-msvc2015/include/mycore)
!exists($${SDK_HEADER_PATH}) {
    mkpath($${SDK_HEADER_PATH})
}

### 拷贝头文件
system(copy *.h $${SDK_HEADER_PATH})
