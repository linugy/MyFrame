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

SDKPATH = $$PWD/../../../dist/qt5.6.3-win32-msvc2015

# 查看SDK头文件目标路径是否存在，不存在则创建
SDK_HEADER_PATH = $$system_path($${SDKPATH}/include/myutil)
!exists($${SDK_HEADER_PATH}) {
    mkpath($${SDK_HEADER_PATH})
}

# 拷贝头文件
system(copy *.h $${SDK_HEADER_PATH})

# 包含头文件
INCLUDEPATH += $${SDKPATH}/include

dest_dir = $${SDKPATH}/bin_dbg

LIB_LIST = mycore mybaseutil mywidget

win32 {
    DEBUG_SUFFIX = d
}

LIBS = -L$$dest_dir

for (lib, LIB_LIST) {
    LIBS += -l$${lib}$${DEBUG_SUFFIX}
}
