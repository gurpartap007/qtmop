#-------------------------------------------------
#
# Project created by QtCreator 2015-12-21T15:12:57
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mpd_api
TEMPLATE = app
CONFIG += link_pkgconfig
PKGCONFIG = libmpdclient



SOURCES += main.cpp\
        mpd.cpp \
    database.cpp \
    music_streamer.cpp \
    keyboard.cpp \
    route_selection.cpp \
    train_route.cpp \
    etu.cpp \
    settings.cpp \
    public_announcement.cpp
    keyboard.cpp

HEADERS  += mpd.h \
    header.h \
    database.h \
    music_streamer.h \
    sql_enums.h \
    keyboard.h \
    route_selection.h \
    train_route.h \
    etu.h \
    settings.h \
    public_announcement.h

FORMS    += mpd.ui \
    music_streamer.ui \
    keyboard.ui \
    route_selection.ui \
    train_route.ui \
    etu.ui \
    settings.ui \
    public_announcement.ui

RESOURCES += \
    icons.qrc