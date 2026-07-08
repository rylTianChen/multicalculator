QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += -O2          # 添加 O2 优化
QMAKE_CXXFLAGS_RELEASE += -O2  # Release 模式也加上
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    back/calc_func.h \
    back/expr_func.h\
    back/tools/init_func.h \
    mainwindow.h\
    back/tools/convert_func.h\
    back/tools/err.h\
    back/tools/hpcalc.h

FORMS += \
    mainwindow.ui

RC_FILE += \
    resources.rc

TARGET += \
    multicalculator.exe

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
