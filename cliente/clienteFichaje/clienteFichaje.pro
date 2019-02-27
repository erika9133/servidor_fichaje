#-------------------------------------------------
#
# Project created by Erika
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cliente_fichaje
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11
QT += websockets
SOURCES += \
        main.cpp \
        mainwindow.cpp \
    ws.cpp \
    json.cpp

HEADERS += \
        mainwindow.h \
    ws.h \
    json.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
