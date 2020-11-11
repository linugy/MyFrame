#-------------------------------------------------
#
# Project created by QtCreator 2020-03-23T21:20:52
#
#-------------------------------------------------

QT       += core  sql script xml network gui widgets

TARGET = $$qtLibraryTarget(mybaseutil)

DESTDIR = $$PWD/../../../dist/qt5.6.3-win32-msvc2015/bin_dbg

TEMPLATE = lib

DEFINES += MYBASEUTIL_LIBRARY

SOURCES += mybaseutil.cpp \
    myscriptengine.cpp

HEADERS += mybaseutil.h\
        mybaseutil_global.h \
    myscriptengine.h

# 查看SDK头文件目标路径是否存在，不存在则创建
SDK_HEADER_PATH = $$system_path($$PWD/../../../dist/qt5.6.3-win32-msvc2015/include/mybaseutil)
!exists($${SDK_HEADER_PATH}) {
    mkpath($${SDK_HEADER_PATH})
}

# 拷贝头文件
system(copy *.h $${SDK_HEADER_PATH})
