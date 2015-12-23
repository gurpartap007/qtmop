#include "mpd.h"
#include "ui_mpd.h"
#include "header.h"
mpd::mpd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mpd)
{
    ui->setupUi(this);
    /* New Sql database which hold the all details about Routes,Devices,Events and announcements.
     *
     * */
    bus_database = new database;
    /*Music Streamer based on mpdclient API which stream through ICECAST server on LOCALHOST on 6600 port no.
     *
     * */
    announcement_streamer = new music_streamer;
    ui->stackedWidget->addWidget(announcement_streamer);
    ui->stackedWidget->setCurrentWidget(announcement_streamer);
}

mpd::~mpd()
{
    delete ui;
}





