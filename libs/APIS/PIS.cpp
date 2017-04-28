
#include "PIS.h"

/*extern values*/
struct  path_struct route_path;
QString selRouteDBVersion;

int TranmsittedRecord = 0;
PIS_VIEW::PIS_VIEW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PIS_VIEW)
{
    route_sel = new route_selection(this);
    run_route =   new running_route(this);
    gps = new LGPS();
    gps->initialiseUSBPort(); /*Do it only once*/
    prerecord = new PreRecorded();
    pis_settings = new PIS_SETTINGS();
    curr_log_timer = new QTimer;
    ui->setupUi(this);
    ui->stackedWidget->addWidget(route_sel);
    ui->stackedWidget->addWidget(run_route);
//     ui->stackedWidget->addWidget(prerecord);
 //   ui->stackedWidget->addWidget(pis_settings);
    connect(route_sel,SIGNAL(route_selected(qint64,void *)),this,SLOT(pis_event_handler(qint64,void *)));
  //  connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(on_pushButton_3_clicked()));
  //  connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(on_pushButton_2_clicked()));
    connect(pis_settings,SIGNAL(StartSimulation(QString)),gps,SLOT(simulateFromFile(QString)));
    connect(pis_settings,SIGNAL(changeLogFreq(int)),gps,SLOT(changeLoggingFreq(int)));
    connect(pis_settings,SIGNAL(selectRoute(QString)),this,SLOT(selectPISRoute(QString)));


    connect(run_route,SIGNAL(log_event()),this,SLOT(save_current_log()));
    connect(gps,SIGNAL(gps_available(qint64,void*)),run_route,SLOT(gps_data_collector(qint64,void *)));
    connect(gps,SIGNAL(gps_available(qint64,void*)),this,SLOT(kilometrage_Calculator(qint64,void *)));
    connect(curr_log_timer,SIGNAL(timeout()),this,SLOT(save_current_log()));
    connect(prerecord,SIGNAL(playclicked(int *)),run_route,SLOT(play_message(int *)));
    curr_log_timer->start(pis_settings->loggingFrequencyTime*1000*60);
    if(route_path.status.bits.route_info_avail)
        pis_event_handler(ROUTE_SELECTED,NULL);
    else
        ui->stackedWidget->setCurrentWidget(route_sel);
    QSettings settings("A_Paul_Instruments","PIS");
    route_path.params.kilometrage = settings.value("Kilometerage").toDouble();
    QStringList data = get_event_data();
    server_acknowledge();    
}

PIS_VIEW::~PIS_VIEW()
{
    delete route_sel;
    delete run_route;
    delete ui;
}

void PIS_VIEW::changeLoggingFreq(int i)
{
    curr_log_timer->stop();
    curr_log_timer->start(i*1000*60);
}

QString PIS_VIEW::getPISLibVersion()
{
    return QString(LIB_VERSION);
}

void PIS_VIEW::selectPISRoute(QString train)
{
    if(!route_sel->selectCurrentRoute(train))
        qDebug()<<"Route selected from web server successfully.";
}

int PIS_VIEW::restoreKilometerage()
{
    route_path.params.kilometrage=0;
    return 0;
}

void PIS_VIEW::kilometrage_Calculator(qint64 event,void *data)
{
    gps_union gps_pkt = *(gps_union *)data;
    route_path.params.kilometrage += ((gps_pkt.data.cpu.speed/100)/3600);
    QSettings settings("A_Paul_Instruments","PIS");
    settings.setValue("Kilometerage",(int)route_path.params.kilometrage);
    settings.sync();
}

QStringList PIS_VIEW::getKilometerData()
{
    m_mutex.lock();
    QStringList logFields;
    logFields.clear();

    logFields.append(pis_settings->UnitID);
    logFields.append(pis_settings->CoachID);
    logFields.append(pis_settings->CoachID);
    logFields.append(QString::fromLatin1(route_path.Header.Route));
    logFields.append(QDate::currentDate().toString("dd-MM-yyyy"));
    logFields.append(QTime::currentTime().toString("hh:mm:ss"));
    logFields.append(QString::number((int)route_path.params.kilometrage));
    m_mutex.unlock();
    return logFields;

}

QStringList PIS_VIEW::getKilometerFields()
{
    m_mutex.lock();
    QStringList logFields;           //7 fields total
    logFields.clear();               //clear if any
    logFields.append("Unit_Id");
    logFields.append("Device_Id");
    logFields.append("Coach_Id");
    logFields.append("Train_Id");
    logFields.append("Date");
    logFields.append("Time");
    logFields.append("Kilometer");
    m_mutex.unlock();
    return logFields;

}

QStringList PIS_VIEW::getEventFields()
{
    m_mutex.lock();
    QStringList logFields;           //22 fields total
    logFields.clear();               //clear if any
    logFields.append("Unit_Id");
    logFields.append("Device_Id");
    logFields.append("Coach_Id");
    logFields.append("Train_Id");
    logFields.append("Date");
    logFields.append("Time");
    logFields.append("latitude");
    logFields.append("longitude");
    logFields.append("Speed");
    logFields.append("Last_Station");
    logFields.append("Next_Station");
    logFields.append("Distance_From_Source");
    logFields.append("Audio_Enable");
    logFields.append("Data_Type");
    logFields.append("Nature_Of_Fault");
    logFields.append("Regional_Language");
    logFields.append("Alarm_Status");
    logFields.append("Late_Hours");
    logFields.append("Type_Of_Data");
    logFields.append("Start_Time");
    logFields.append("End_Time");
    logFields.append("Kilometerage");
    m_mutex.unlock();
    return logFields;

}


void PIS_VIEW::save_current_log(void)
{
    QSqlQuery query1(QSqlDatabase::database("Connection1"));

    /*************** updating fields ************/
    query1.exec("INSERT INTO `pis_log_data` (`unit_id`, `device_id`,\
             `coach_id`, `train_id`, `data_date`, `data_time`, `latitude`,\
             `longitude`, `speed`, `last_stn_name`, `next_stn_name`,\
             `remaining_distance_stn`, `audio_enabled`, `data_type`,\
             `fault_string`, `regional_language`, `alarm`, `late_run_status`,\
             `type_data`, `trn_start_data`, `trn_start_time`, `kilometerage`,\
             `transmitted`) VALUES ( '" + QString(pis_settings->UnitID)\
             + "','" + QString(pis_settings->CoachID)\
             + "','" + QString(pis_settings->CoachID)\
             + "','" + QString::fromLatin1(route_path.Header.Route).rightJustified(6,'0')\
             + "','" + QDate::currentDate().toString("yyyy-MM-dd")\
             + "','" + QTime::currentTime().toString("hh:mm:ss")\
             + "','" + gps->getLatitude()\
             + "','" + gps->getLongitude()\
             + "','" + gps->getSpeed()\
             + "','" + QString::fromLatin1(route_path.Stops[route_path.Curr_stop].info.station_name[0])\
             + "','" + QString::fromLatin1(route_path.Stops[route_path.Curr_stop].info.station_name[0])\
             + "','" + QString::number(route_path.Stops[route_path.Curr_stop].info.distance_from_curr_loc)\
             +"','"+ QString(route_path.params.audio)\
             +"','"+ QString(route_path.params.event)\
             +"','"+ QString(route_path.params.fault)\
             +"','"+ QString::number(route_path.Stops[route_path.Curr_stop].info.regional_lngugage)\
             +"','"+ QString(route_path.params.alarm)\
             +"','"+ route_path.params.late_run\
             +"','"+ QString("Events") \
             +"','"+ QString("20")+QString::number(route_path.params.start_date.yrs).rightJustified(2,'0')+"-"+QString::number(route_path.params.start_date.mon).rightJustified(2,'0')+"-"+QString::number(route_path.params.start_date.day).rightJustified(2,'0')\
             +"','"+ QString::number(route_path.params.start_time.hrs).rightJustified(2,'0')+":"+QString::number(route_path.params.start_time.min).rightJustified(2,'0')+":"+QString::number(route_path.params.start_time.sec).rightJustified(2,'0')\
             +"','"+ QString::number((int)route_path.params.kilometrage)\
             +"','"+ QString("N") + "')");   
    qDebug()<<query1.lastQuery();
}

QStringList PIS_VIEW::get_event_data(void)
{
    m_mutex.lock();
    int i = 0;
    QStringList RecordString;
    RecordString.clear();

    QSqlQuery query1(QSqlDatabase::database("Connection1"));
    query1.exec("Select *from `pis_log_data` where `transmitted` = 'N' order by `id`  DESC");
    if(query1.next())
    {
        while(i < (query1.record().count()-2))
            RecordString.append(query1.record().value(i++).toString());
        RecordString.append(query1.record().value(i++).toString());
        TranmsittedRecord = query1.record().value(i).toInt();
    }
    m_mutex.unlock();
    return RecordString;

}

void PIS_VIEW::server_acknowledge(void)
{
    m_mutex.lock();
    QSqlQuery query1(QSqlDatabase::database("Connection1"));
    query1.exec("UPDATE `pis_log_data` SET `transmitted` = 'Y' where `id` = '" + QString::number(TranmsittedRecord) + "'");
    m_mutex.unlock();
}

QStringList PIS_VIEW::get_fault_data(void)
{
    m_mutex.lock();
    int i = 0;
    QStringList RecordString;
    RecordString.clear();

    QSqlQuery query1(QSqlDatabase::database("Connection1"));
    query1.exec("Select *from `pis_log_data` where `type_data` = 'Faults' AND `transmitted` = 'N' order by `id`  DESC");
    if(query1.next())
    {
        while(i < (query1.record().count()-2))
            RecordString.append(query1.record().value(i++).toString());
        RecordString.append(query1.record().value(i++).toString());
        TranmsittedRecord = query1.record().value(i).toInt();
    }
    m_mutex.unlock();
    return RecordString;

}

void PIS_VIEW::pis_event_handler(qint64 event,void *data)
{
    QSettings Settings("A_Paul_Instruments","PIS");
    switch(event)
    {
        case ROUTE_SELECTED:
            Settings.setValue("ROUTE",route_path.Header.Route);
            Settings.setValue("LINKROUTE",route_path.Header.LinkRoute);
            Settings.sync();
            run_route->calculate_multiplying_factor();
            run_route->display_timer_id = run_route->startTimer(100);
            run_route->route_tasks_timer_id = run_route->startTimer(1000);
            ui->stackedWidget->setCurrentWidget(run_route);
            break;
    }
}

void PIS_VIEW::on_setts_clicked()
{
   //pis_settings->setWindowOpacity(0.95);
   pis_settings->ui->Settings->setCurrentIndex(0);
   pis_settings->show();
}

void PIS_VIEW::on_prerecord_clicked()
{
    prerecord->show();
}

void PIS_VIEW::on_routesel_clicked()
{
    qDebug("Changing Route...");
    //run_route->close_timer();
    ui->stackedWidget->setCurrentWidget(route_sel);
}

void PIS_VIEW::mouseReleaseEvent(QMouseEvent *e)
{
    if(prerecord->isVisible())
        prerecord->hide();
    if(pis_settings->isVisible())
        pis_settings->hide();
}
