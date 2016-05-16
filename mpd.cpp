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
    qDebug() << "selection_timer started";
    ui->stackedWidget->setCurrentIndex(0);
    qDebug() << "Displaying the front page of ui";
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
    qDebug() << "Delete User Interface resources";
    delete select_route;
    qDebug() << "Route Selection algorithm is deleted";
    delete emergency_talkback;
    qDebug() << "Emergency Talkback is deleted";
    delete system_settings;
    qDebug() << "System Settings is deleted";
    delete selection_timer;
    qDebug() << "selection Timer is deleted";
    delete announcement;
    qDebug() << "Announcement is deleted";
}

void mpd::on_select_route_clicked()
{
    ui->stackedWidget->setCurrentWidget(select_route);
    qDebug() << "select route window";
}

void mpd::on_etu_clicked()
{
    emergency_talkback->setParent(ui->stackedWidget);
    qDebug() << "Emergency Talkback parent is changed";
    emergency_talkback->setGeometry(0,0,ui->stackedWidget->width(),ui->stackedWidget->height());
    qDebug() << "Geometry of Emergency Talkback is changed";
    emergency_talkback->setWindowFlags(Qt::WindowStaysOnTopHint);
    qDebug() << "Emergency Talkback window flags are set to WindowsStayOnTopHint";
    ui->settings->hide();
    qDebug() << "Settings menu is hiidden";
    ui->control_room->hide();
    qDebug() << "Control room is hidden";
    ui->intercom->hide();
    qDebug() << "Intercom is hidden";
    ui->pa->hide();
    qDebug() << "Public Announcement is hidden";
    ui->announcement_label->hide();
    qDebug() << "Announcement Label is hidden";
    ui->settings_label->hide();
    qDebug() << "Settings Label is hidden";
    ui->control_room_label->hide();
    qDebug() << "control room label is hidden";
    ui->intercom_label->hide();
    qDebug() << "intercom Label is hidden";
    emergency_talkback->show();
    qDebug() << "Emergency Talk Back is shown";
}

void mpd::show_train_route_selection()
{
    ui->stackedWidget->setCurrentIndex(1);
    qDebug() << "Stack Widget current index is 1";
    selection_timer->stop();
    qDebug() << "Selection Timer is stopped";
    ui->etu->setEnabled(true);
    qDebug() << "etu app is enabled";
    ui->settings->setEnabled(true);
    qDebug() << "settings app is enabled";
    ui->control_room->setEnabled(true);
    qDebug() << "control room is enabled";
    ui->pa->setEnabled(true);
    qDebug() << "Public Announcement is enabled";
    ui->intercom->setEnabled(true);
    qDebug() << "Intercom is enabled";
}

void mpd::close_etu_popup()
{
    emergency_talkback->setParent(0);
    qDebug() << "emergency talkback is moved to background";
    emergency_talkback->close();
    qDebug() << "emergency talkback is closed for current time being";
    ui->settings->show();
    qDebug() << "Showing Settings menu";
    ui->control_room->show();
    qDebug() << "Showing Control room menu";
    ui->intercom->show();
    qDebug() << "Showing Intercom menu";
    ui->pa->show();
    qDebug() << "Showing Public Announcement menu ";
    ui->announcement_label->show();
    qDebug() << "Showing Announcement Label menu";
    ui->settings_label->show();
    qDebug() << "Showing Settings Label menu";
    ui->control_room_label->show();
    qDebug() << "Showing Control Room Label menu";
    ui->intercom_label->show();
    qDebug() << "Showing Intercom Label menu";
}

void mpd::on_settings_clicked()
{
    system_settings->setParent(ui->stackedWidget);
    qDebug() << "stacked widget is parent of system settings";
    system_settings->setGeometry(0,0,ui->stackedWidget->width(),ui->stackedWidget->height());
    qDebug() << "Changed Geometry of system settings menu";
    system_settings->setWindowFlags(Qt::WindowStaysOnTopHint);
    qDebug() << "system settings flag changed to WindowStaysOnTopHint";
    ui->etu->hide();
    qDebug() << "Emergency Talk Unit is hidden now";
    ui->control_room->hide();
    qDebug() << "Control Room is hidden now";
    ui->intercom->hide();
    qDebug() << "Intercom is hidden";
    ui->pa->hide();
    qDebug() << "Public Announcement is hidden";
    ui->announcement_label->hide();
    qDebug() << "Announcement Label is hidden";
    ui->etu_label->hide();
    qDebug() << "Etu Label is hidden";
    ui->control_room_label->hide();
    qDebug() << "Control Label is hidden";
    ui->intercom_label->hide();
    qDebug() << "Intercom label is hidden";
    system_settings->show();
    qDebug() << "System Settings are now shown in current context";
}

void mpd::close_settings_popup()
{
    system_settings->setParent(0);
    qDebug() << "System settings parent is changed";
    system_settings->close();
    qDebug() << "System Settings are now closed";
    ui->etu->show();
    qDebug() << "Emergency Talk Unit is shown";
    ui->control_room->show();
    qDebug() << "Control Room is shown";
    ui->intercom->show();
    qDebug() << "Intercom is shown";
    ui->pa->show();
    qDebug() << "Public Announcement is currently running";
    ui->announcement_label->show();
    qDebug() << "Announcement Label is shown";
    ui->etu_label->show();
    qDebug() << "Emergency Talk Unit Label is showing Now";
    ui->control_room_label->show();
    qDebug() << "control Room Label is showing";
    ui->intercom_label->show();
    qDebug() << "Intercom label is showing";
}

void mpd::on_pa_clicked()
{
    announcement->setParent(ui->stackedWidget);
    qDebug() << "Announcement parent is changed";
    announcement->setGeometry(0,0,ui->stackedWidget->width(),ui->stackedWidget->height());
    qDebug() << "Geometry of Announcement is changed";
    announcement->setWindowFlags(Qt::WindowStaysOnTopHint);
    qDebug() << "Announcement flags are changed to WindowStaysOnTopHint";
    ui->etu->hide();
    qDebug() << "Emergency Talk Unit is hidden now";
    ui->etu_label->hide();
    qDebug() << "Emergency Talk Unit Label is hidden now";
    ui->control_room->hide();
    qDebug() << "Control Room is hidden";
    ui->control_room_label->hide();
    qDebug() << "Control Room label is hidden";
    ui->intercom->hide();
    qDebug() << "Intercom is hidden now";
    ui->intercom_label->hide();
    qDebug() << "Intercom Label is hidden";
    ui->settings->hide();
    qDebug() << "Settings are hidden";
    ui->settings_label->hide();
    qDebug() << "Settings Label is hidden";
    announcement->show();
    qDebug() << "Announcement is currently running";
}

void mpd::close_announcement_popup()
{
    announcement->setParent(0);
    qDebug() << "Announcement parent is changed";
    announcement->close();
    qDebug() << "Announcement is closed";
    ui->etu->show();
    qDebug() << "Emergency Talk Unit is showing currently";
    ui->control_room->show();
    qDebug() << "Control Room is showing currently";
    ui->intercom->show();
    qDebug() << "Intercom is showing currently";
    ui->settings->show();
    qDebug() << "Settings is showing currently";
    ui->settings_label->show();
    qDebug() << "Settings Label is showing currently";
    ui->etu_label->show();
    qDebug() << "Etu Label is showing currently ";
    ui->control_room_label->show();
    qDebug() << "Control Room Label is showing currently";
    ui->intercom_label->show();
    qDebug() << "Intercom Label is showing currently";
}

void mpd::on_intercom_clicked()
{
    close();
    qDebug() << "Application is closed";
}
