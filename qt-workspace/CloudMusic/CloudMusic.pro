QT       += core gui
QT       += network
QT       += multimedia
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    musicconfig.cpp \
    musicdatabase.cpp \
    musicdownload.cpp \
    musichttp.cpp \
    musichttpurl.cpp \
    musicinformation.cpp \
    musicitem.cpp \
    musicplayer.cpp \
    musicscene.cpp \
    tablemenu.cpp

HEADERS += \
    mainwindow.h \
    musicconfig.h \
    musicdatabase.h \
    musicdownload.h \
    musichttp.h \
    musichttpurl.h \
    musicinformation.h \
    musicitem.h \
    musicplayer.h \
    musicscene.h \
    tablemenu.h

FORMS += \
    mainwindow.ui

# 包含pri工程
include(MusicHandle/MusicHandle.pri)
include(MusicSet/MusicSet.pri)
# 添加pri工程头文件路径
INCLUDEPATH += MusicHandle
INCLUDEPATH += MusicSet

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
