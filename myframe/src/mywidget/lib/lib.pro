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

TRANSLATIONS += mywidget_zh_CN.ts

SOURCES += mywidget.cpp \
    mylogindialog.cpp

HEADERS += mywidget.h\
        mywidget_global.h \
    mylogindialog.h

# 查看SDK头文件目标路径是否存在，不存在则创建
SDK_HEADER_PATH = $$system_path($$PWD/../../../../dist/qt5.6.3-win32-msvc2015/include/mywidget)
!exists($${SDK_HEADER_PATH}) {
    mkpath($${SDK_HEADER_PATH})
}

# 拷贝头文件
system(copy *.h $${SDK_HEADER_PATH})

# 把本目录下的qm文件复制到language文件
QM_LIST = mywidget_zh_CN.qm
DEST_LANGUAGE_PATH = $$system_path($$PWD/../../../../dist/qt5.6.3-win32-msvc2015/language)
!exists($${DEST_LANGUAGE_PATH}) {
    mkpath($${DEST_LANGUAGE_PATH})
}
for(qm, QM_LIST) {
    system(copy $$system_path($${qm}) $${DEST_LANGUAGE_PATH})
}
