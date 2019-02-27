#-------------------------------------------------
#
# Project created by Erika
#
#-------------------------------------------------

QT -= gui

CONFIG += c++14 console
CONFIG -= app_bundle

LIBS += -lxml2
#INCLUDEPATH += libxml
TARGET = servidor_fichaje

DEFINES += QT_DEPRECATED_WARNINGS

QT += sql
QT += websockets

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
    app.cpp \
    ws.cpp \
    bbdd.cpp \
    json.cpp

HEADERS += \
    app.h \
    ws.h \
    bbdd.h \
    json.h
