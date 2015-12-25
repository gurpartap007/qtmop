#include "mpd.h"
#include "ui_mpd.h"
#include "header.h"
mpd::mpd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mpd)
{
    ui->setupUi(this);
    gps_timer1 = new QTimer(this);
    gps_timer1->setInterval(1000);
    gps_timer2 = new QTimer(this);
    gps_timer2->setInterval(500);
    gps_timer1->start();
    set_indicators();
    connect(gps_timer1,SIGNAL(timeout()),this,SLOT(gps_indication_on()));
    connect(gps_timer2,SIGNAL(timeout()),this,SLOT(gps_indication_off()));
    /*Music Streamer based on mpdclient API which stream through ICECAST server on LOCALHOST on 6600 port no.
     *
     * */
    announcement_streamer = new music_streamer;
    mop_mode = new user_mode;
    ui->stackedWidget->addWidget(announcement_streamer);
    ui->stackedWidget->addWidget(mop_mode);

}

mpd::~mpd()
{
    delete ui;
}

void mpd::set_indicators()
{
    QRegion* region = new QRegion(*(new QRect(ui->gps->x(),ui->gps->y(),20,20)),QRegion::Ellipse);
    ui->gps->setMask(*region);
    ui->pwr->setMask(*region);
    ui->gsm->setMask(*region);
    ui->call->setMask(*region);
    ui->gps->setStyleSheet("QPushButton{ background-color: rgb(229,0,0); }");
    ui->pwr->setStyleSheet("QPushButton{ background-color: rgb(0,255,0); }");
    ui->gsm->setStyleSheet("QPushButton{ background-color: rgb(229,0,0); }");
    ui->call->setStyleSheet("QPushButton{ background-color: rgb(229,0,0); }");
}

void mpd::gps_indication_on()
{

    ui->gps->setStyleSheet("QPushButton{ background-color: rgb(0,255,0); }");
    gps_timer2->start();
}

void mpd::gps_indication_off()
{
    gps_timer2->stop();
    ui->gps->setStyleSheet("QPushButton{ background-color: rgb(0,0,0); }");
}

void mpd::user_mode_selected()
{
ui->stackedWidget->setCurrentWidget(mop_mode);
}

void mpd::on_menu_clicked()
{

}
