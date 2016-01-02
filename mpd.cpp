#include "mpd.h"
#include "ui_mpd.h"
#include "header.h"
mpd::mpd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mpd)
{
    ui->setupUi(this);


    /*Music Streamer based on mpdclient API which stream through ICECAST server on LOCALHOST on 6600 port no.
     *
     * */
    //announcement_streamer = new music_streamer;
    select_route = new route_selection;
    //select_route->setWindowFlags(Qt::FramelessWindowHint);

   // select_route->setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    ui->stackedWidget->setCurrentIndex(0);
    //ui->stackedWidget->addWidget(announcement_streamer);

}

mpd::~mpd()
{
    delete ui;
}


void mpd::on_menu_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void mpd::on_select_route_clicked()
{
    select_route->setParent(this);

    select_route->show();
    //ui->stackedWidget->setCurrentIndex(2);
   // ui->stackedWidget->addWidget(select_route);
   // ui->stackedWidget->setCurrentWidget(select_route);
}
