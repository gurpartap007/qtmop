#include "mpd.h"
#include "ui_mpd.h"
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
    emergency_talkback = new etu;
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->addWidget(select_route);
    connect(emergency_talkback,SIGNAL(call_ended()),this,SLOT(on_menu_clicked()));
    //ui->stackedWidget->addWidget(announcement_streamer);
}
mpd::~mpd()
{
    delete ui;
}
void mpd::on_menu_clicked()
{
    emergency_talkback->setParent(0);
    //emergency_talkback->hide();
    ui->settings->show();
    ui->control_room->show();
    ui->intercom->show();
    ui->pa->show();
    ui->announcement_label->show();
    ui->settings_label->show();
    ui->control_room_label->show();
    ui->intercom_label->show();
    ui->stackedWidget->setCurrentIndex(1);
}

void mpd::on_select_route_clicked()
{
    ui->stackedWidget->setCurrentWidget(select_route);
}

void mpd::on_etu_clicked()
{
    emergency_talkback->setParent(ui->stackedWidget);
    emergency_talkback->setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->settings->hide();
    ui->control_room->hide();
    ui->intercom->hide();
    ui->pa->hide();
    ui->announcement_label->hide();
    ui->settings_label->hide();
    ui->control_room_label->hide();
    ui->intercom_label->hide();
    emergency_talkback->show();


}
