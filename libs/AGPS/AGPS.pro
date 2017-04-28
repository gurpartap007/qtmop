#-------------------------------------------------
#
# Project created by QtCreator 2016-11-14T18:36:14
#
#-------------------------------------------------

QT       += network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = AGPS
TEMPLATE = lib
CONFIG += staticlib

DEFINES += AGPS_LIBRARY

SOURCES += \
    lgps.cpp

HEADERS += \
    lgps.h \
    lgps_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
