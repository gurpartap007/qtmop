#-------------------------------------------------
#
# Project created by QtCreator 2015-12-21T15:12:57
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mpd_api
TEMPLATE = app
CONFIG += link_pkgconfig
PKGCONFIG = libmpdclient



SOURCES += main.cpp\
        mpd.cpp

HEADERS  += mpd.h \
    header.h

FORMS    += mpd.ui
