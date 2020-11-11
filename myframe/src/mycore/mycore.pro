#-------------------------------------------------
#
# Project created by QtCreator 2020-03-23T21:22:41
#
#-------------------------------------------------

QT       += core script widgets

TARGET = $$qtLibraryTarget(mycore)

DESTDIR = $$PWD/../../../dist/qt5.6.3-win32-msvc2015/bin_dbg

TEMPLATE = lib

DEFINES += MYCORE_LIBRARY

SOURCES += mycore.cpp \
    myclassabs.cpp

HEADERS += mycore.h\
        mycore_global.h \
    myclassabs.h \
    myclasspluginabs.h

SDKPATH = $$PWD/../../../dist/qt5.6.3-win32-msvc2015

# 查看SDK头文件目标路径是否存在，不存在则创建
SDK_HEADER_PATH = $$system_path($${SDKPATH}/include/mycore)
!exists($${SDK_HEADER_PATH}) {
    mkpath($${SDK_HEADER_PATH})
}

# 拷贝头文件
system(copy *.h $${SDK_HEADER_PATH})

# 包含头文件
INCLUDEPATH += $${SDKPATH}/include

dest_dir = $${SDKPATH}/bin_dbg

LIB_LIST = mybaseutil

win32 {
    DEBUG_SUFFIX = d
}

LIBS = -L$$dest_dir

for (lib, LIB_LIST) {
    LIBS += -l$${lib}$${DEBUG_SUFFIX}
}
