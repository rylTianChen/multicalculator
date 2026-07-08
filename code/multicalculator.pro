QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h\
    back\calc_func.h\
    back\expr_func.h\
    back\tools\convert_func.h\
    back\tools\err.h\
    back\tools\hpcalc.h\
    back\tools\init_func.h\
    back\tools\numch_func.h

FORMS += \
    mainwindow.ui

RC_FILE += \
    resources.rc

# ========== 国际化配置 ==========
TRANSLATIONS += \
    translations/calculator_zh_CN.ts \
    translations/calculator_en.ts

# 自动生成 .qm 文件（编译时自动运行 lrelease）
CONFIG += lrelease
# 自动将 .qm 嵌入到可执行文件中
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target