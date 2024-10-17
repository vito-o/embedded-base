# 指定要在工程中用到qt的哪些模块
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
# 工程中c++的支持版本
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    pushbutton.cpp \
    signalslot.cpp

HEADERS += \
    mainwindow.h \
    pushbutton.h \
    signalslot.h
# 工程用的控件
FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
