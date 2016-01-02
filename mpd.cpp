#include "mpd.h"
#include "ui_mpd.h"
#include "header.h"
mpd::mpd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mpd)
{
    ui->setupUi(this);

   // gps_timer1 = new QTimer(this);
   // gps_timer1->setInterval(300);
   // gps_timer2 = new QTimer(this);
   // gps_timer2->setInterval(150);
   // gps_timer1->start();
   // set_indicators();
   // connect(gps_timer1,SIGNAL(timeout()),this,SLOT(gps_indication_on()));
    //connect(gps_timer2,SIGNAL(timeout()),this,SLOT(gps_indication_off()));
    /*Music Streamer based on mpdclient API which stream through ICECAST server on LOCALHOST on 6600 port no.
     *
     * */
    //announcement_streamer = new music_streamer;
    select_route = new route_selection;

    //ui->stackedWidget->setCurrentIndex(0);
    //ui->stackedWidget->addWidget(announcement_streamer);

}

mpd::~mpd()
{
    delete ui;
}

void mpd::set_indicators()
{
    QRegion* region = new QRegion(*(new QRect(ui->gps->x(),ui->gps->y(),20,20)),QRegion::Ellipse);
    QRegion* region_mode = new QRegion(*(new QRect(ui->mode->x()+4,ui->mode->y()+2,95,95)),QRegion::Ellipse);
    //  ui->mode->setMask(*region_mode);
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
    ui->gps->setStyleSheet("QPushButton{ background-color: rgb(100,100,100); }");
}

void mpd::on_menu_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void mpd::on_select_route_clicked()
{
    select_route->show();
    //ui->stackedWidget->setCurrentIndex(2);
    //ui->stackedWidget->addWidget(select_route);
    //ui->stackedWidget->setCurrentWidget(select_route);
}

void mpd::on_settings_clicked()
{

}
