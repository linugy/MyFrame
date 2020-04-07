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

unix {
    target.path = /usr/lib
    INSTALLS += target
}

### 查看SDK头文件目标路径是否存在，不存在则创建
SDK_HEADER_PATH = $$system_path($$PWD/../../../dist/qt5.6.3-win32-msvc2015/include/mycore)
!exists($${SDK_HEADER_PATH}) {
    mkpath($${SDK_HEADER_PATH})
}

### 
system(copy *.h $${SDK_HEADER_PATH})


# sdk path
SDKPATH = $$PWD/../../../dist/qt5.6.3-win32-msvc2015

# include headers
INCLUDEPATH += $${SDKPATH}/include

# debug suffix
win32 {
    DEBUG_SUFFIX = d
}

LIB_LIST = mybaseutil

#
des_dir = $$PWD/../../../dist/qt5.6.3-win32-msvc2015/bin_dbg

# libs
LIBS = -L$$des_dir
for (lib, LIB_LIST) {
    LIBS += -l$${lib}$${DEBUG_SUFFIX}
}
