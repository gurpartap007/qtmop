#include "mpd.h"
#include "ui_mpd.h"
QTimer *selection_timer;
mpd::mpd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mpd)
{
    ui->setupUi(this);
    select_route = new route_selection;
    emergency_talkback = new etu;
    system_settings = new settings;
    selection_timer = new QTimer;
    announcement = new public_announcement;
    selection_timer->setInterval(1000);
    selection_timer->start();
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->addWidget(select_route);
    connect(emergency_talkback,SIGNAL(new_incoming_call()),this,SLOT(on_etu_clicked()));
    connect(emergency_talkback,SIGNAL(back_clicked()),this,SLOT(close_etu_popup()));
    connect(system_settings,SIGNAL(back_clicked()),this,SLOT(close_settings_popup()));
    connect(selection_timer,SIGNAL(timeout()),this,SLOT(show_train_route_selection()));
    connect(announcement,SIGNAL(back_clicked()),this,SLOT(close_announcement_popup()));
}
mpd::~mpd()
{
    delete ui;
    delete select_route;
    delete emergency_talkback;
    delete system_settings;
    delete selection_timer;
    delete announcement;
}

void mpd::on_select_route_clicked()
{
    ui->stackedWidget->setCurrentWidget(select_route);
}

void mpd::on_etu_clicked()
{
    qDebug() << ui->stackedWidget->width();
    emergency_talkback->setParent(ui->stackedWidget);
    emergency_talkback->setGeometry(0,0,ui->stackedWidget->width(),ui->stackedWidget->height());
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

void mpd::show_train_route_selection()
{
    ui->stackedWidget->setCurrentIndex(1);
    selection_timer->stop();
    ui->etu->setEnabled(true);
    ui->settings->setEnabled(true);
    ui->control_room->setEnabled(true);
    ui->pa->setEnabled(true);
    ui->intercom->setEnabled(true);
}

void mpd::close_etu_popup()
{
    emergency_talkback->setParent(0);
    emergency_talkback->close();
    ui->settings->show();
    ui->control_room->show();
    ui->intercom->show();
    ui->pa->show();
    ui->announcement_label->show();
    ui->settings_label->show();
    ui->control_room_label->show();
    ui->intercom_label->show();
}

void mpd::on_settings_clicked()
{
    system_settings->setParent(ui->stackedWidget);
    system_settings->setGeometry(0,0,ui->stackedWidget->width(),ui->stackedWidget->height());
    system_settings->setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->etu->hide();
    ui->control_room->hide();
    ui->intercom->hide();
    ui->pa->hide();
    ui->announcement_label->hide();
    ui->etu_label->hide();
    ui->control_room_label->hide();
    ui->intercom_label->hide();
    system_settings->show();
}

void mpd::close_settings_popup()
{
    system_settings->setParent(0);
    system_settings->close();
    ui->etu->show();
    ui->control_room->show();
    ui->intercom->show();
    ui->pa->show();
    ui->announcement_label->show();
    ui->etu_label->show();
    ui->control_room_label->show();
    ui->intercom_label->show();
}

void mpd::on_pa_clicked()
{
    announcement->setParent(ui->stackedWidget);
    announcement->setGeometry(0,0,ui->stackedWidget->width(),ui->stackedWidget->height());
    announcement->setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->etu->hide();
    ui->etu_label->hide();
    ui->control_room->hide();
    ui->control_room_label->hide();
    ui->intercom->hide();
    ui->intercom_label->hide();
    ui->settings->hide();
    ui->settings_label->hide();
    announcement->show();
}

void mpd::close_announcement_popup()
{
    announcement->setParent(0);
    announcement->close();
    ui->etu->show();
    ui->control_room->show();
    ui->intercom->show();
    ui->settings->show();
    ui->settings_label->show();
    ui->etu_label->show();
    ui->control_room_label->show();
    ui->intercom_label->show();
}

void mpd::on_intercom_clicked()
{
    close();
}
