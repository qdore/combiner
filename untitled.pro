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
    menu.cpp \
    configparse.cpp \
    server/connection.cpp \
    server/connection_manager.cpp \
    server/mime_types.cpp \
    server/reply.cpp \
    server/request_handler.cpp \
    server/request_parser.cpp \
    server/server.cpp

HEADERS  += \
    systemtrayicon.h \
    config.h \
    menu.h \
    configparse.h \
    server/connection.hpp \
    server/connection_manager.hpp \
    server/header.hpp \
    server/mime_types.hpp \
    server/reply.hpp \
    server/request.hpp \
    server/request_handler.hpp \
    server/request_parser.hpp \
    server/server.hpp \
    proxy.h

INCLUDEPATH += /usr/local/Cellar/boost/1.56.0/include

LIBS +=  -L/usr/local/Cellar/boost/1.56.0/lib -lboost_system

RESOURCES += \
    icon.qrc

FORMS += \
    form.ui

ICON = icon.icns

CONFIG += c++11

unix {
    DEFINES += UNIX
}
