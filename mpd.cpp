#include "mpd.h"
#include "ui_mpd.h"
QTimer *selection_timer;
mpd::mpd(QApplication *app_ptr ,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mpd)
{
    qDebug() << "ADDRESS of App in mpd()" << app_ptr;

    ui->setupUi(this);
    WebServer = new  webserver() ;
    select_route = new route_selection();
    emergency_talkback = new etu;
    system_settings = new settings;
    selection_timer = new QTimer;
    timer_fade_in = new QTimer;
    timer_fade_out = new QTimer;
    timer_fade_in->setInterval(3000);
    timer_fade_out->setInterval(1000);
    announcement = new public_announcement;
 //   xmlWriter = new xml_writer ;
    connect(WebServer->requestHandler,SIGNAL(write_train_routes(QString)),select_route,SLOT(write_route_data_to_xml(QString)));
    connect(timer_fade_in,SIGNAL(timeout()),this,SLOT(fade_in()));
    selection_timer->setInterval(1000);
    selection_timer->start();
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->addWidget(select_route);
    connect(WebServer->requestHandler,SIGNAL(route_selection_menu()),this,SLOT(on_select_route_clicked()));
    connect(emergency_talkback,SIGNAL(new_incoming_call()),this,SLOT(incoming_call_notification()));
    connect(emergency_talkback,SIGNAL(back_clicked()),this,SLOT(close_etu_popup()));
    connect(system_settings,SIGNAL(back_clicked()),this,SLOT(close_settings_popup()));
    connect(selection_timer,SIGNAL(timeout()),this,SLOT(show_train_route_selection()));
    connect(announcement,SIGNAL(back_clicked()),this,SLOT(close_announcement_popup()));
    connect(ui->volume_control,SIGNAL(clicked()),this,SLOT(volume_control_slot()));
    volume_muted = false;
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
    //incoming_call_notification();
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
    timer_fade_in->stop();
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
    ui->etu->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(150, 150, 150, 255), stop:1 rgba(255, 255, 255, 255));"
                           "");
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

void mpd::incoming_call_notification()
{
    volume_muted = false;
    ui->etu->setStyleSheet("background-color: rgba(79,141,176,100);");
    /*
timer_fade_in->start();
fade_in();*/
}

void mpd::fade_in()
{
    /* QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    ui->etu->setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(1000);
    a->setStartValue(0);
    a->setEndValue(1);
    a->setEasingCurve(QEasingCurve::InCirc);
    a->start(QPropertyAnimation::DeleteWhenStopped);*/

}

void mpd::fade_out()
{
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    ui->etu->setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(1000);
    a->setStartValue(1);
    a->setEndValue(0);
    a->setEasingCurve(QEasingCurve::OutBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);

}

void mpd::volume_control_slot()
{
    if(!volume_muted)
    {
        emit emergency_talkback->mute_mic(true);
        QPixmap pix_unmute_button(":/images/vol_control_black.png");
        QIcon unmute_button_icon(pix_unmute_button);
        ui->volume_control->setIcon(unmute_button_icon);
    }
    else
    {
        emit emergency_talkback->mute_mic(false);
        QPixmap pix_mute_button(":/images/mute_call.png");
        QIcon mute_button_icon(pix_mute_button);
        ui->volume_control->setIcon(mute_button_icon);
    }
    volume_muted = !volume_muted;

}
