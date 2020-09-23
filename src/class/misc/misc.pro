TEMPLATE = aux

DISTFILES += \
    my.cfg

DIST_DIR = $$PWD/../../../dist

# 复制cfg
!exists($$system_path($${DIST_DIR}/config)) {
    mkpath($$system_path($${DIST_DIR}/config))
}
!exists($$system_path($${DIST_DIR}/config/my.cfg)) {
    system(copy my.cfg $$system_path($${DIST_DIR}/config/))
}

SDKPATH = $$PWD/../../../dist/qt5.6.3-win32-msvc2015

# 编译rcc到目标目录
!exists($$system_path($${SDKPATH}\resource\res)) {
    mkpath($$system_path($${SDKPATH}\resource\res))
}
system($$[QT_HOST_BINS]/rcc -binary res.qrc -o $${SDKPATH}/resource/res/my.rcc)


RESOURCES += \
    res.qrc

