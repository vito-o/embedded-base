QT       += core gui
QT       += network
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    musichttp.cpp \
    musichttpurl.cpp \
    musicinformation.cpp \
    musicplayer.cpp

HEADERS += \
    mainwindow.h \
    musichttp.h \
    musichttpurl.h \
    musicinformation.h \
    musicplayer.h

FORMS += \
    mainwindow.ui

# 包含pri工程
include(MusicHandle/MusicHandle.pri)
# 添加pri工程头文件路径
INCLUDEPATH += MusicHandle

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
