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
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->addWidget(select_route);
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
    ui->stackedWidget->setCurrentWidget(select_route);
}
