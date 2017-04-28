#-------------------------------------------------
#
# Project created by QtCreator 2016-11-14T18:43:28
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets network serialport concurrent widgets qml quick network opengl sql script scripttools svg xml xmlpatterns multimedia testlib dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = APIS
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += \
        /opt/app/CRC_LIB \
        /opt/app/AGPS \
        /opt/app/lineedit \
        /opt/app/virtualKeyboard \
        /opt/app/Includes\
        /opt/app/admin

DEFINES += APIS_LIBRARY

SOURCES += \
    pis_settings.cpp \
    PIS.cpp \
    prerecorded.cpp \
    running_route.cpp \
    route_selection.cpp \
    pis_module.cpp

HEADERS += \
    pis_settings.h \
    PIS.h \
    prerecorded.h \
    route_selection.h \
    running_route.h \
    /opt/app/Includes/PIS_Structs.h \
    PIS_global.h \
    pis_module.h \
    /opt/app/virtualKeyboard/virtualkeyboard.h \
    /opt/app/virtualKeyboard/keypad.h \
    /opt/app/lineedit/lineedit.h \
    /opt/app/lineedit/lineedit_global.h \
    /opt/app/admin/admin.h \
    externs.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    PIS.ui \
    prerecorded.ui \
    route_selection.ui \
    running_route.ui \
    pis_settings.ui

