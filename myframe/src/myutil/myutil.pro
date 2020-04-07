#-------------------------------------------------
#
# Project created by QtCreator 2020-03-23T21:33:08
#
#-------------------------------------------------

QT       += core script widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = $$qtLibraryTarget(myutil)

DESTDIR = $$PWD/../../../dist/qt5.6.3-win32-msvc2015/bin_dbg

TEMPLATE = lib

DEFINES += MYUTIL_LIBRARY

SOURCES += myutil.cpp \
    mymain.cpp \
    mylogin.cpp

HEADERS += myutil.h\
        myutil_global.h \
    mymain.h \
    mylogin.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


### 查看SDK头文件目标路径是否存在，不存在则创建
SDK_HEADER_PATH = $$system_path($$PWD/../../../dist/qt5.6.3-win32-msvc2015/include/myutil)
!exists($${SDK_HEADER_PATH}) {
    mkpath($${SDK_HEADER_PATH})
}

### 拷贝头文件
system(copy *.h $${SDK_HEADER_PATH})

### 包含头文件
SDKPATH = $$PWD/../../../dist/qt5.6.3-win32-msvc2015
message($$SDKPATH)
INCLUDEPATH += $${SDKPATH}/include

### 包含dll
win32 {
    DEBUG_SUFFIX = d
}
LIB_LIST = mycore mybaseutil mywidget
LIBS += -L$$DESTDIR
for (lib, LIB_LIST) {
    LIBS += -l$${lib}$${DEBUG_SUFFIX}
}
