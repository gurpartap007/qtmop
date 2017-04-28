#-------------------------------------------------
#
# Project created by QtCreator 2015-12-21T15:12:57
#
#-------------------------------------------------

QT       += core gui network sql serialport xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mpd_api
TEMPLATE = app

SOURCES += main.cpp\
        mpd.cpp \
    database.cpp \
    music_streamer.cpp \
    keyboard.cpp \
    route_selection.cpp \
    train_route.cpp \
    etu.cpp \
    settings.cpp \
    public_announcement.cpp \
    skipbutton.cpp \
    numeric_keypad.cpp \
    display_communication.cpp \
    etubutton.cpp \
    requesthandler.cpp \
    webserver.cpp \
    xml_writer.cpp \
    libs/AGPS/lgps.cpp \
    intercom.cpp


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
    public_announcement.h \
    route_struct.h \
    skipbutton.h \
    numeric_keypad.h \
    display_communication.h \
    etubutton.h \
    logging/filelogger.h \
    requesthandler.h \
    webserver.h \
    xml_writer.h \
    libs/AGPS/lgps.h \
    intercom.h

FORMS    += mpd.ui \
    music_streamer.ui \
    keyboard.ui \
    route_selection.ui \
    train_route.ui \
    etu.ui \
    settings.ui \
    numeric_keypad.ui
   # intercom.ui
OTHER_FILES += etc/*  logs/* etc/docroot/*
RESOURCES += \
    icons.qrc
CONFIG(debug, debug|release) {
    unix:!mac:  LIBS += -L$$PWD/libs/QtWebApp -lQtWebApp
    unix:!macx: LIBS += -L/usr/local/lib -llinphone -lmediastreamer_voip -lmediastreamer_base -lortp
    unix:!macx: LIBS += -L/usr/lib -lmpdclient
}


INCLUDEPATH += /usr/local/include /usr/include $$PWD/headers/*
DEPENDPATH += /usr/local/include ./logging/*     $$PWD/headers/*

INCLUDEPATH += /usr/include
DEPENDPATH += /usr/include
INCLUDEPATH += $$PWD/libs/AGPS
DEPENDPATH += $$PWD/libs/AGPS

