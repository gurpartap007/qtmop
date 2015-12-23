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
    music_streamer.cpp

HEADERS  += mpd.h \
    header.h \
    database.h \
    music_streamer.h \
    sql_enums.h

FORMS    += mpd.ui \
    music_streamer.ui
