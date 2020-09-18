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
