//checking tags
#include "mpd.h"
#include "ui_mpd.h"
mpd::mpd(QApplication *app_ptr ,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mpd)
{
    qDebug() << "ADDRESS of App in mpd()" << app_ptr;

    ui->setupUi(this);
    WebServer = new  webserver() ;
    select_route = new route_selection();
   // emergency_talkback = new etu;
    system_settings = new settings;
    selection_timer = new QTimer;
    timer_fade_in = new QTimer;
    timer_fade_out = new QTimer;
    gps =new LGPS();
    timer_fade_in->setInterval(3000);
    timer_fade_out->setInterval(1000);
    announcement = new public_announcement;
    interCom = new intercom;
    connect(select_route->current_route,SIGNAL(simulate(QString)),gps,SLOT(simulateFromFile(QString)));
    //xmlWriter = new xml_writer ;
    connect(gps,SIGNAL(gps_available(qint64,void*)),select_route->current_route,SLOT(gps_packet_handler(qint64,void*)));
    connect(WebServer->requestHandler,SIGNAL(write_train_routes(QString)),select_route,SLOT(write_route_data_to_xml(QString)));
    connect(WebServer->requestHandler,SIGNAL(accept_selected_call(QString)),emergency_talkback,SLOT(accept_call_by_ip_address(QString)));
    connect(WebServer->requestHandler,SIGNAL(disconnect_selected_call(QString)),emergency_talkback,SLOT(terminate_call_by_ip_address(QString)));
    connect(WebServer->requestHandler,SIGNAL(hold_selected_call(QString)),emergency_talkback,SLOT(hold_resume_call_by_ip_address(QString)));
    connect(WebServer->requestHandler,SIGNAL(resume_selected_call(QString)),emergency_talkback,SLOT(hold_resume_call_by_ip_address(QString)));
    connect(WebServer->requestHandler,SIGNAL(intercom_clicked()),this,SLOT(on_intercom_clicked()));
    connect(WebServer->requestHandler,SIGNAL(announcement_clicked()),this,SLOT(on_pa_clicked()));
    connect(timer_fade_in,SIGNAL(timeout()),this,SLOT(fade_in()));
    selection_timer->setInterval(1000);
    selection_timer->start();
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->addWidget(select_route);
    connect(WebServer->requestHandler,SIGNAL(route_selection_menu()),this,SLOT(on_select_route_clicked()));
    connect(WebServer->requestHandler,SIGNAL(skip_stop(QByteArray)),select_route,SLOT(skip_station(QByteArray)));
    connect(WebServer->requestHandler,SIGNAL(change_next_stop(QByteArray,QByteArray)),select_route,SLOT(select_next(QByteArray,QByteArray)));
    connect(WebServer->requestHandler,SIGNAL(change_pf_direction(QChar)),select_route,SLOT(change_pf(QChar)));
    //connect(emergency_talkback,SIGNAL(new_incoming_call()),this,SLOT(incoming_call_notification()));
    //connect(emergency_talkback,SIGNAL(back_clicked()),this,SLOT(close_etu_popup()));
    connect(system_settings,SIGNAL(back_clicked()),this,SLOT(close_settings_popup()));
    connect(selection_timer,SIGNAL(timeout()),this,SLOT(show_train_route_selection()));
        connect(interCom,SIGNAL(CallEnded()),this,SLOT(call_ended_from_guard()));
        connect(interCom,SIGNAL(talking_with_driver()),this,SLOT(show_active_call()));
    connect(ui->volume_control,SIGNAL(clicked()),this,SLOT(volume_control_slot()));
    volume_muted = false;
    intercom_running = false ;
    announcement_running = false ;
}
mpd::~mpd()
{
    delete ui;
    delete select_route;
    delete emergency_talkback;
    delete system_settings;
    delete selection_timer;
    delete announcement;
    delete interCom;
    delete gps;
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
 ui->pa->setStyleSheet("background-color: rgb(30,144,255);");
 if(!announcement_running)
 {
  announcement->on_start_announcement_clicked();
    announcement_running = true ;
    update_xml("PA");
 }
 else
 {
     announcement->on_end_announcement_clicked();
     ui->pa->setStyleSheet("QPushButton{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(150, 150, 150, 255), stop:1 rgba(255, 255, 255, 255));}");
     announcement_running = false ;
     update_xml("IDLE");
 }
}

void mpd::on_intercom_clicked()
{
    ui->intercom->setStyleSheet("background-color: rgb(30,144,255);");
    if(!intercom_running)
    {
 //    interCom->qlinphone_init();
    interCom->talk_to_guard();
    intercom_running = true ;
    update_xml("CC");
    }
    else
    {
        interCom->end_intercom_call();
        ui->intercom->setStyleSheet("QPushButton{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(150, 150, 150, 255), stop:1 rgba(255, 255, 255, 255));}");
        intercom_running = false ;
        update_xml("IDLE");
    }

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

void mpd::update_xml(QString mode)
{
    etu_updating_file = new QFile("/home/apaul/apaul_projects/qtmop/etc/docroot/mcu_stat.xml");
    if (!etu_updating_file->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "unable to open xml file";
        return;
    }
    QByteArray xmlData(etu_updating_file->readAll());
    QDomDocument doc("mcu_stat");
    doc.setContent(xmlData);
    QDomElement root = doc.firstChildElement("CATALOG");
    QDomElement statheader = root.firstChildElement("STATHEADER");
    statheader.setAttribute("Mode",mode);
    etu_updating_file->resize(0);
    QTextStream stream(etu_updating_file);
    stream.setDevice(etu_updating_file);
    doc.save(stream, 4);
    etu_updating_file->close();
}

void mpd::call_ended_from_guard()
{
    ui->intercom->setStyleSheet("QPushButton{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(150, 150, 150, 255), stop:1 rgba(255, 255, 255, 255));}");
    intercom_running = false ;
    update_xml("IDLE");
}

void mpd::show_active_call()
{
     ui->intercom->setStyleSheet("background-color: rgb(30,144,255);");
       update_xml("CC");
       intercom_running = true ;
}
