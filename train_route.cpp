#include "train_route.h"
#include "skipbutton.h"
#include "ui_train_route.h"
extern QString master_train_no;
extern QString slave_train_no;
bool is_slave_train  = false;
route_struct current_route_data;

train_route::train_route(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::train_route)
{
    ui->setupUi(this);
    udp_connection           =  new display_communication();
    connect(this,SIGNAL(send_route_info()),udp_connection,SLOT(send_train_route_info()));

    connect(this,SIGNAL(add_stations()),this,SLOT(add_stations_for_current_train()));
    connect(&time_update,SIGNAL(timeout()),this,SLOT(update_date_time()));
    time_update.start(1000);
}

train_route::~train_route()
{
    delete ui;
    delete skip_button_font;
    delete station_name_font;
}

void train_route::add_stations_for_current_train()
{
    int loop_count;
    skip_button_font = new QFont;
    skip_button_font->setFamily("Garuda");
    skip_button_font->setPointSize(26);
    station_name_font = new QFont;
    station_name_font->setFamily("Sans Serif");
    station_name_font->setPointSize(30);
    station_name_font->setBold(true);

    /////////////////////////////// EXTRACTING STATION CODES FOR CURRENT TRAIN ///////////////////////////
    QSqlQuery get_station_codes_for_master_train("SELECT `stn_code` FROM `tbl_RouteMaster` WHERE `train_sno`='"+ master_train_no+"' order by `distance_frm_source`");
    while(get_station_codes_for_master_train.next())
    {
        station_codes.append(get_station_codes_for_master_train.value(0).toString());
    }
    //***************************************************************************************************//
    skipbutton *skip_button[station_codes.size()];
    QLabel *station_name[station_codes.size()];
    QListWidgetItem *item[station_codes.size()];
    QWidget *widget[station_codes.size()];
    QHBoxLayout *widgetLayout[station_codes.size()];
    QSpacerItem *spacer_item[station_codes.size()];
    /////////////////////// EXTRACTING AND FILLING STATION NAMES FOR PARTICULAR STATION CODE //////////////
    for(loop_count=0;loop_count<station_codes.size();loop_count++)
    {
        station_name[loop_count] = new QLabel ;
        widget[loop_count] = new QWidget(this);
        skip_button[loop_count] = new skipbutton("Skip",loop_count,station_name[loop_count],widget[loop_count],this);
        widgetLayout[loop_count] = new QHBoxLayout;
        item[loop_count] = new QListWidgetItem    ;
        spacer_item[loop_count] = new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed);
        skip_button[loop_count] -> setFont(*skip_button_font)   ;
        skip_button[loop_count] -> setMinimumSize(QSize(400,50));
        station_name[loop_count]-> setFont(*station_name_font) ;
        skip_button[loop_count] -> setStyleSheet("QPushButton{ background-color: rgb(179, 179, 179); }QPushButton:pressed{background-color: rgb(100, 100, 100); }");
        widgetLayout[loop_count]-> addWidget(skip_button[loop_count])    ;
        widgetLayout[loop_count]-> addWidget(station_name[loop_count])   ;
        widgetLayout[loop_count]-> addSpacerItem(spacer_item[loop_count]);
        widgetLayout[loop_count]-> setAlignment(skip_button[loop_count],Qt::AlignLeft);
        widgetLayout[loop_count]-> setAlignment(station_name[loop_count],Qt::AlignLeft);
        widget[loop_count]      -> setLayout(widgetLayout[loop_count]);
        widget[loop_count]      -> setStyleSheet("background-color: rgb(179,179,179);");
        ui->listWidget          -> addItem(item[loop_count]);
        item[loop_count]        -> setSizeHint(skip_button[loop_count]->minimumSizeHint());
        ui->listWidget          -> setItemWidget(item[loop_count],widget[loop_count]);
        QSqlQuery get_station_wait_time("SELECT `wait_time` FROM `tbl_RouteMaster` WHERE `train_sno`='"+ master_train_no +"' and `stn_code`= '"+station_codes.at(loop_count)+"' ");
        get_station_wait_time.first();
        if(!get_station_wait_time.value(0).toInt())
        {
            widget[loop_count]->setStyleSheet("background-color: rgb(200,200,200);");
            skip_button[loop_count]->setDisabled(true);
            station_name[loop_count]->setStyleSheet("color: rgb(150,0,0)");
            current_route_data.stn[loop_count].status.bits.station_skipped = true;
        }

        QSqlQuery get_station_names("SELECT `station_name` FROM `tbl_StationName` WHERE `station_code`='"+station_codes.at(loop_count)+"' and `stn_LangId`='english' ");
        while(get_station_names.next())
        {
            station_names.append(get_station_names.value(0).toString());
            station_name[loop_count]->setText(get_station_names.value(0).toString());
            item[loop_count]->setText(get_station_names.value(0).toString());
        }
        connect(skip_button[loop_count],SIGNAL(skip_clicked(int)),this,SLOT(on_skip_station_clicked(int)));
        widget[0]->setStyleSheet("background-color: rgb(255, 148, 124);");
    }
}

///////////////////// STRUCTURE FILLING FOR SELECTED ROUTE //////////////////////

void train_route::structure_filling(bool slave_train)
{
    fill_train_struct(slave_train);
    fill_stn_struct();
    show_train_info();
    emit add_stations();
}

void train_route::show_train_info()
{
    ui->coach_count->setText(QString::number(current_route_data.train.coach_count));
    ui->train_name->setText(master_train_no);
    ui->source_station_name->setText(QString::fromUtf8((const char *)current_route_data.train.src.name.eng));
    ui->via_name->setText(QString::fromUtf8((const char *)current_route_data.train.mid.name.eng));
    ui->destination_station_name->setText(QString::fromUtf8((const char *)current_route_data.train.des.name.eng));
    if(ladies_special)
        ui->ladies_special_type->setText("Yes");
    else
        ui->ladies_special_type->setText("No") ;
    if(fast)
        ui->slow_fast_type->setText("Fast")    ;
    if(slow)
        ui->slow_fast_type->setText("Slow")    ;
    show_handicap_coaches();
    qDebug() << "English name" << QString::fromUtf8((const char *)current_route_data.train.src.name.eng);
    qDebug() << "Hindi Name"   << QString::fromUtf8((const char *)current_route_data.train.src.name.hin);
    qDebug() << "Reg Name"    << QString::fromUtf8((const char *)current_route_data.train.src.name.reg1);
}

/********************************************************************************/

void train_route::on_skip_station_clicked(int id)
{
    QListWidgetItem *current_item;
    QWidget *current_widget;
    current_item = ui->listWidget->item(id);
    current_widget =  ui->listWidget->itemWidget(current_item);
    //current_widget->setStyleSheet("background-color: rgba(200,0,0,100);");
    current_item->setForeground(QBrush(QColor(200,0,0,100)));
    qDebug() << "Skipped Station" << current_item->text();
}

void train_route::update_date_time()
{
    date_time.clear();
    current_date = QDate::currentDate();
    date_time.append(current_date.toString(Qt::TextDate));
    date_time.append("  ");
    current_time = QTime::currentTime();
    date_time.append(current_time.toString(Qt::TextDate));
    ui->date_time->setText(date_time);
    ui->coach_count->adjustSize();
}


void train_route::src_mid_des_station_name_filling()
{
    /////////////////////////////////////   SOURCE STAION NAME   /////////////////////////////////
    QSqlQuery get_source_station_name_eng("SELECT * FROM `tbl_StationName` WHERE `station_code`='"+QString::fromUtf8((const char *)current_route_data.train.src_stn_code)+"' and `stn_LangId`='english' ");
    get_source_station_name_eng.first();
    memcpy(current_route_data.train.src.name.eng,get_source_station_name_eng.value(StationName::STATION_NAME).toString().toStdString().c_str(),get_source_station_name_eng.value(StationName::STATION_NAME).toString().size());
    QSqlQuery get_source_station_name_hin("SELECT * FROM `tbl_StationName` WHERE `station_code`='"+QString::fromUtf8((const char *)current_route_data.train.src_stn_code)+"' and `stn_LangId`='Hindi' ");
    get_source_station_name_hin.first();
    memcpy(current_route_data.train.src.name.hin,get_source_station_name_hin.value(StationName::STATION_NAME).toString().toStdString().c_str(),get_source_station_name_hin.value(StationName::STATION_NAME).toString().size());
    QSqlQuery get_source_station_name_reg("SELECT * FROM `tbl_StationName` WHERE `station_code`='"+QString::fromUtf8((const char *)current_route_data.train.src_stn_code)+"' and `stn_LangId`='Tamil'");
    get_source_station_name_reg.first();
    memcpy(current_route_data.train.src.name.reg1,get_source_station_name_reg.value(StationName::STATION_NAME).toString().toStdString().c_str(),get_source_station_name_reg.value(StationName::STATION_NAME).toString().size());
    ////////////////////////////////////    VIA STATION NAME    /////////////////////////
    QSqlQuery get_via_station_name("SELECT `station_name` FROM `tbl_StationName` WHERE `station_code`='"+QString::fromUtf8((const char *)current_route_data.train.mid_stn_code)+"' and `stn_LangId`='english' ");
    get_via_station_name.first();
    memcpy(current_route_data.train.mid.name.eng,get_via_station_name.value(0).toString().toStdString().c_str(),get_via_station_name.value(0).toString().size());
    ///////////////////////////////////  DESTINATION STATION NAME //////////////////
    QSqlQuery get_destination_station_name("SELECT `station_name` FROM `tbl_StationName` WHERE `station_code`='"+QString::fromUtf8((const char *)current_route_data.train.des_stn_code)+"' and `stn_LangId`='english' ");
    get_destination_station_name.first();
    memcpy(current_route_data.train.des.name.eng,get_destination_station_name.value(0).toString().toStdString().c_str(),get_destination_station_name.value(0).toString().size());

    /***********************************************************************************************/

}

void train_route::find_ladies_and_slow_fast_status(bool slave_train)
{
    //////////////////////////// FIND LADIES_SPECIAL_STATUS AND SLOW/FAST STATUS OF SLAVE TRAIN ///////////////////
    if (slave_train)
    {
        QSqlQuery query_ladies_train_status("SELECT `ladies_trn_status` FROM `tbl_slave_route` where `train_number`='"+ slave_train_no + "'");
        QSqlQuery query_slow_fast_status("SELECT `train_status` FROM `tbl_slave_route` where `train_number`='"+ slave_train_no + "'");
        query_ladies_train_status.next();
        query_slow_fast_status.next();
        if(query_ladies_train_status.value(0).toString().at(0) == 1)
        {
            ladies_special = true;
        }
        else
        {
            ladies_special = false;
            current_route_data.status.flags.bits.distance_processed = true ;
            current_route_data.stn[1].status.bits.station_skipped   = false;
        }
        if(query_slow_fast_status.value(0).toString() == "S")
        {
            current_route_data.train.slow_fast = 'S';
            slow=true;
        }
        else
        {
            current_route_data.train.slow_fast = 'F';
            fast=true;
        }
    }
    //**************************************************************************************************//

    //////////////////////////// FIND LADIES_SPECIAL_STATUS AND SLOW/FAST STATUS OF MASTER TRAIN ///////////////////

    else
    {
        QSqlQuery query_ladies_train_status("SELECT `ladies_train_status` FROM `tbl_TrainNumber` where `train_no`='"+ master_train_no + "'");
        QSqlQuery query_slow_fast_status_master("SELECT `slow_fast` FROM `tbl_TrainNumber` where `train_no`='"+ master_train_no + "'");
        query_ladies_train_status.next();
        query_slow_fast_status_master.next();
        if(query_ladies_train_status.value(0).toString().at(0) == 1)
        {
            ladies_special = true;
        }
        else
        {
            ladies_special = false;
        }
        if(query_slow_fast_status_master.value(0).toString() == "S")
        {
            slow=true;
        }
        else
        {
            fast=true;
        }
    }
    //**************************************************************************************************//
}

void train_route::show_handicap_coaches()
{
    ////////////////////////////////// FIND HANDICAP COACH NO'S OF CURRENT TRAIN  ////////////////////////////////
    QSqlQuery query_find_handicap_coaches("select `handicap_coach1`,`handicap_coach2` from `configuration`");
    query_find_handicap_coaches.next();
    handicap_coach_no=query_find_handicap_coaches.value(0).toString();
    handicap_coach_no.append("/");
    handicap_coach_no.append(query_find_handicap_coaches.value(1).toString());
    ui->handicap_coach->setText(handicap_coach_no);

    //**************************************************************************************************//
}

void train_route::fill_train_struct(bool slave_train)
{
    QStringList arr_time_master,dep_time_master,arr_time_slave,dep_time_slave;
    QTime arrival_time;
    QSqlQuery current_train_info("SELECT * FROM `tbl_TrainNumber` WHERE `train_no`='"+ master_train_no +"'");
    while(current_train_info.next())
    {
        memcpy(current_route_data.train.train_num,current_train_info.value(TrainNumber::TRAIN_NO).toString().toStdString().c_str(),current_train_info.value(TrainNumber::TRAIN_NO).toString().size());
        memcpy(current_route_data.train.src_stn_code,current_train_info.value(TrainNumber::SRC_STN_SNO).toString().toStdString().c_str(),current_train_info.value(TrainNumber::SRC_STN_SNO).toString().size());
        memcpy(current_route_data.train.mid_stn_code,current_train_info.value(TrainNumber::VIA_STN_SNO).toString().toStdString().c_str(),current_train_info.value(TrainNumber::VIA_STN_SNO).toString().size());
        memcpy(current_route_data.train.des_stn_code,current_train_info.value(TrainNumber::DEST_STN_SNO).toString().toStdString().c_str(),current_train_info.value(TrainNumber::DEST_STN_SNO).toString().size());
        current_route_data.train.coach_count = current_train_info.value(TrainNumber::NO_OF_COACHES).toInt();
        current_route_data.train.no_of_stns = current_train_info.value(TrainNumber::TOTAL_STATION_ROUTE).toInt();
        current_route_data.train.journ_dist = current_train_info.value(TrainNumber::JRNY_DISTANCE).toInt();
        arr_time_master = current_train_info.value((TrainNumber::ARR_TIME)).toString().split(":");
        dep_time_master = current_train_info.value(TrainNumber::DEP_TIME).toString().split(":");
    }
    if(!slave_train)
    {
        current_route_data.train.arr_time_hrs = arr_time_master.at(Time::HOURS).toInt();
        current_route_data.train.arr_time_min = arr_time_master.at(Time::MINUTES).toInt();
        current_route_data.train.dep_time_hrs = dep_time_master.at(Time::HOURS).toInt();
        current_route_data.train.dep_time_min = dep_time_master.at(Time::MINUTES).toInt();
    }
    else
    {
        if(TrainNumber::DEP_TIME == TrainNumber::DEP_TIME)
            qDebug() << "Train Arrived at the Station" ;
        QSqlQuery slave_train_arr_dep_time("SELECT * FROM `tbl_slave_route` WHERE `train_number`='"+slave_train_no+"'");
        slave_train_arr_dep_time.first();
        arr_time_slave = slave_train_arr_dep_time.value((SlaveRoute::ARRIVAL_TIME)).toString().split(":");
        dep_time_slave = slave_train_arr_dep_time.value(SlaveRoute::DEPARTURE_TIME).toString().split(":");
        current_route_data.train.arr_time_hrs = arr_time_slave.at(Time::HOURS).toInt();
        current_route_data.train.arr_time_min = arr_time_slave.at(Time::MINUTES).toInt();
        current_route_data.train.dep_time_hrs = dep_time_slave.at(Time::HOURS).toInt();
        current_route_data.train.dep_time_min = dep_time_slave.at(Time::MINUTES).toInt();
    }
    arrival_time.fromString(QString("15.20.2"),QString("hhmmss"));
    ///////////////// CONVERTING UNSIGNED CHAR * TO CONST CHAR * FOR CONVERSION TO QSTRING   ////////////////////
    qDebug() << "train Number" << QString::fromUtf8((const char *)current_route_data.train.train_num);
    qDebug() << "src station code" << QString::fromUtf8((const char *)current_route_data.train.src_stn_code);
    qDebug() << "mid station code" << QString::fromUtf8((const char *)current_route_data.train.mid_stn_code);
    qDebug() << "des station code" << QString::fromUtf8((const char *)current_route_data.train.des_stn_code);
    qDebug() << "coach count " << QString::number(current_route_data.train.coach_count);
    qDebug() << "No. of Stations " << QString::number(current_route_data.train.no_of_stns);
    qDebug() << "Journey Distance" << QString::number(current_route_data.train.journ_dist);
    qDebug() << "Arr Time" << arr_time_slave;
    qDebug() << "Arr Time hrs" << QString::number(current_route_data.train.arr_time_hrs);
    qDebug() << "Arr Time minutes" << QString::number(current_route_data.train.arr_time_min);
    qDebug() << "Departure Time" << dep_time_slave;
    qDebug() << "Arr Time HOURS " << QString::number(current_route_data.train.arr_time_hrs);
    qDebug() << "Dep Time hrs" << QString::number(current_route_data.train.dep_time_hrs);
    qDebug() << "Dep Time minutes" << QString::number(current_route_data.train.dep_time_min);
    qDebug() << "Dep Time MINUTES" << QString::number(current_route_data.train.dep_time_min);
    /***********************************************************************************************************/
    src_mid_des_station_name_filling();

    find_ladies_and_slow_fast_status(slave_train);
}

void train_route::fill_stn_struct()
{
    int total_no_of_stations,loop_count;
    float previous_distance;
    previous_distance = 0;
    total_no_of_stations = current_route_data.train.no_of_stns;

    /////////////////////////////// EXTRACTING STATION CODES FOR CURRENT TRAIN ///////////////////////////
    QSqlQuery get_station_codes_for_master_train("SELECT `stn_code` FROM `tbl_RouteMaster` WHERE `train_sno`='"+ master_train_no+"' order by `distance_frm_source`");
    while(get_station_codes_for_master_train.next())
    {
        station_codes.append(get_station_codes_for_master_train.value(0).toString());
    }
    qDebug() << "Station codes " << station_codes;
    qDebug() << "Station names " << station_names;
    qDebug() << "Total No of Stations" << total_no_of_stations;
    for(loop_count=0;loop_count<station_codes.size();loop_count++)
        // for(loop_count=0;loop_count<total_no_of_stations;loop_count++)
    {
        current_route_data.stn[loop_count].wait_time = '\0';
        QSqlQuery get_each_station_info("SELECT * FROM `tbl_RouteMaster` WHERE `stn_code`='"+ station_codes.at(loop_count) +"' and `train_sno`= '"+master_train_no+"'");
        get_each_station_info.first();
        memcpy(current_route_data.stn[loop_count].stn_code,get_each_station_info.value(RouteMaster::STN_CODE).toString().toStdString().c_str(),get_each_station_info.value(RouteMaster::STN_CODE).toString().size());
        if(get_each_station_info.value(RouteMaster::PLATFORM_DIRECTION).toString() == "L")
            current_route_data.stn[loop_count].bits.pf_left = true;
        else
            current_route_data.stn[loop_count].bits.pf_left = false;
        if(fast)
            current_route_data.stn[loop_count].bits.fast_train = true;
        else
            current_route_data.stn[loop_count].bits.fast_train = false;
        current_route_data.stn[loop_count].distance_from_previous_station = (unsigned long) get_each_station_info.value(RouteMaster::DISTANCE_FRM_SOURCE).toFloat() - previous_distance;
        current_route_data.stn[loop_count].wait_time                      = get_each_station_info.value(RouteMaster::WAIT_TIME).toInt();
        previous_distance                                                 = get_each_station_info.value(RouteMaster::DISTANCE_FRM_SOURCE).toFloat();
        current_route_data.stn[loop_count].status.bits.station_skipped    = false;
        current_route_data.stn[loop_count].arrival_peri                   = get_each_station_info.value(RouteMaster::ARR_TRIGGERING).toInt();
        current_route_data.stn[loop_count].approaching_peri               = get_each_station_info.value(RouteMaster::APP_TRIGGERING).toInt();
        current_route_data.stn[loop_count].departure_peri                 = get_each_station_info.value(RouteMaster::DEP_TRIGGERING).toInt();
        QSqlQuery get_long_latt_for_each_station("SELECT * FROM `tbl_StationCode` WHERE `station_code`='"+station_codes.at(loop_count)+"'");
        get_long_latt_for_each_station.first();
        current_route_data.stn[loop_count].loc.coordintes.longitude       = get_long_latt_for_each_station.value(StationCode::LONGITUDE).toFloat();
        current_route_data.stn[loop_count].loc.coordintes.latitude        = get_long_latt_for_each_station.value(StationCode::LATITUDE).toFloat();
        //current_route_data.stn[loop_count].wait_time = wait_time1;
        qDebug() << "Distance from previous " << QString::number(current_route_data.stn[loop_count].distance_from_previous_station);
        qDebug() << "Wait Time ...." << QString::number(current_route_data.stn[loop_count].wait_time);
    }
    station_codes.clear();
}


int train_route::on_next_station_clicked()
{
    static int current_station=0;
    qDebug() << "Longitude--->" << current_route_data.stn[current_station].loc.coordintes.longitude;
    qDebug() << "Lattitude--->" << current_route_data.stn[current_station].loc.coordintes.latitude;
check_again:

    //if(current_station == current_route_data.train.no_of_stns)
        if(current_station == station_codes.size())

    {
        ui->next_station->setDisabled(true);
        ui->next_station->setStyleSheet(" color: rgb(150,150,150);");
        return 0;
    }
    if(current_route_data.stn[current_station].status.bits.station_skipped)
    {
        if(current_station!=0)
        {
        QListWidgetItem *prev_item;
        QWidget *prev_widget;
        prev_item = ui->listWidget->item(current_station-1);
        // prev_item->setBackgroundColor(QColor(150,150,150,100));
        prev_widget =  ui->listWidget->itemWidget(prev_item);
        //prev_widget->setAutoFillBackground(true);
        prev_widget->setStyleSheet("background-color: rgb(150,150,150);");
        }
        current_station ++ ;
        goto check_again;
    }
    else
    {
        if(current_station!=0)
        {
        QListWidgetItem *prev_item;
        QWidget *prev_widget;
        prev_item = ui->listWidget->item(current_station-1);
        // prev_item->setBackgroundColor(QColor(150,150,150,100));
        prev_widget =  ui->listWidget->itemWidget(prev_item);
        //prev_widget->setAutoFillBackground(true);
        prev_widget->setStyleSheet("background-color: rgb(150,150,150);");
        }
        QListWidgetItem *current_item;
        QWidget *current_widget;
        current_item = ui->listWidget->item(current_station);
        current_widget =  ui->listWidget->itemWidget(current_item);
        current_widget->setStyleSheet("background-color: rgb(0, 150,0);");
       // memcpy(current_route_data.train.current_station.name.eng,QString("AMBALA").toStdString().c_str(),6);
       qDebug() << station_names.at(current_station);
       memset(current_route_data.train.current_station.name.eng,'\0',50);
        memcpy(current_route_data.train.current_station.name.eng,station_names.at(current_station).toStdString().c_str(),station_names.at(current_station).size());
        emit send_route_info();
        ///////////////////////// SET AUTO SCROLLING OF VIEW //////////////////////
        ui->listWidget->setAutoScroll(true);
        ui->listWidget->setCurrentItem(ui->listWidget->item(current_station));
        ///////////////////////////////////////////////////////////////////////////
        if(current_route_data.stn[current_station].bits.pf_left)
        {
            ui->platform_left->setStyleSheet("background-color: qlineargradient(spread:pad, x1:1, y1:0.8, x2:1, y2:1, stop:0.3 rgba(80, 80, 80, 255), stop:1 rgba(100, 100, 100, 255)); color: rgb(0,200,0);");
            ui->platform_right->setStyleSheet("background-color: qlineargradient(spread:pad, x1:1, y1:0.8, x2:1, y2:1, stop:0.3 rgba(80, 80, 80, 255), stop:1 rgba(100, 100, 100, 255)); color: rgb(179,179,179);");
            ui->platform_right->setDisabled(true);
            ui->platform_left->setDisabled(false);
        }
        else
        {
            ui->platform_left->setStyleSheet("background-color: qlineargradient(spread:pad, x1:1, y1:0.8, x2:1, y2:1, stop:0.3 rgba(80, 80, 80, 255), stop:1 rgba(100, 100, 100, 255)); color: rgb(179,179,179);");
            ui->platform_right->setStyleSheet("background-color: qlineargradient(spread:pad, x1:1, y1:0.8, x2:1, y2:1, stop:0.3 rgba(80, 80, 80, 255), stop:1 rgba(100, 100, 100, 255)); color: rgb(0,200,0);");
            ui->platform_left->setDisabled(true);
            ui->platform_right->setDisabled(false);
        }
        current_station ++;

    }
    return 0;
}

