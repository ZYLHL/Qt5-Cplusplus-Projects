QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11
PRECOMPILED_HEADER = src/pch.hpp

SOURCES += \
    src/core/demo.cpp \
    src/main.cpp \
    src/ui/mainwindow.cpp \
    src/ui/zoomarea.cpp

HEADERS += \
    src/core/demo.h \
    src/ui/mainwindow.h \
    src/ui/zoomarea.h

INCLUDEPATH += \
    src/

FORMS += \
    src/ui/mainwindow.ui

TRANSLATIONS += \
    res/translations/zh_CN.ts

RESOURCES += \
    res/res.qrc
