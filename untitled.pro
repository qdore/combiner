#-------------------------------------------------
#
# Project created by QtCreator 2014-10-08T15:57:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp \
    systemtrayicon.cpp \
    menu.cpp

HEADERS  += \
    systemtrayicon.h \
    config.h \
    menu.h

RESOURCES += \
    icon.qrc

FORMS += \
    form.ui

ICON = icon.icns
