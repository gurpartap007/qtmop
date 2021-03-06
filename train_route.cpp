#include "train_route.h"

#include "ui_train_route.h"
#define FC_SDF "C"
#define FC_SAF "D"
#define FC_RSF "A"
#define FC_REF "B"
#define FC_SMF "E"
#define REGIONAL_LANGUAGE "Tamil"
extern QString master_train_no;
int current_station = 0;
extern QString slave_train_no;
bool is_slave_train  = false;
route_struct current_route_data;
static bool isRouteEnded = false;
sinteger mul_factor[MAX_STATIONS_PER_ROUTE];
float track_dist_bn_stns[MAX_STATIONS_PER_ROUTE];
train_route::train_route(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::train_route)
{
    ui->setupUi(this);
    udp_connection = new display_communication();
    xmlWriter = new  QXmlStreamWriter  ;
    file = new QFile("/home/apaul/apaul_projects/qtmop/etc/docroot/route_stat.xml");
    updating_file = new QFile("/home/apaul/apaul_projects/qtmop/etc/docroot/route_stat.xml");
    connect(this,SIGNAL(send_route_info(QString)),udp_connection,SLOT(send_train_route_info(QString)));
    connect(this,SIGNAL(add_stations()),this,SLOT(add_stations_for_current_train()));
    connect(this,SIGNAL(route_end()),this,SLOT(show_end_route()));
    connect(&time_update,SIGNAL(timeout()),this,SLOT(update_date_time()));
    time_update.start(1000);
    //udp_connection->device_reset();
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
    skip_button_font->setPointSize(12);
    station_name_font = new QFont;
    station_name_font->setFamily("Sans Serif");
    station_name_font->setPointSize(14);
    station_name_font->setBold(true);
    station_name_font->setCapitalization(QFont::SmallCaps);


    /////////////////////////////// EXTRACTING STATION CODES FOR CURRENT TRAIN ///////////////////////////
    QSqlQuery get_station_codes_for_master_train("SELECT `stn_code` FROM `tbl_RouteMaster` WHERE `train_sno`='"+ master_train_no+"' order by `distance_frm_source`");
    while(get_station_codes_for_master_train.next())
    {
        station_codes.append(get_station_codes_for_master_train.value(0).toString());
    }
    //***************************************************************************************************//

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
        widget[loop_count]->blockSignals(true);
        skip_button[loop_count] = new skipbutton("Skip",loop_count,station_name[loop_count],widget[loop_count],this);
        widgetLayout[loop_count] = new QHBoxLayout;
        widgetLayout[loop_count]->setMargin(3);

        item[loop_count] = new QListWidgetItem    ;
        spacer_item[loop_count] = new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed);
        skip_button[loop_count] -> setFont(*skip_button_font);
        skip_button[loop_count] -> setMinimumSize(QSize(100,30));
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
        station_name[loop_count]->setText(QString::fromUtf8((const char *)current_route_data.stn[loop_count].stn_name[0]));
        xmlWriter->writeStartElement("STOPS");
        xmlWriter->writeAttribute("STOP",QString::fromUtf8((const char *)current_route_data.stn[loop_count].stn_name[0]));
        if(current_route_data.stn[current_route_data.status.next_halting_stn].bits.pf_left)
            xmlWriter->writeAttribute("PFD","RIGHT");
        else
            xmlWriter->writeAttribute("PFD","LEFT");
        if(  current_route_data.stn[loop_count].status.bits.station_skipped)
            xmlWriter->writeAttribute("ADD","0");
        else
            xmlWriter->writeAttribute("ADD","1");
        xmlWriter->writeEndElement();
        // item[loop_count]->setText(QString::fromUtf8((const char *)current_route_data.stn[loop_count].stn_name[0]));
        connect(skip_button[loop_count],SIGNAL(skip_clicked(int)),this,SLOT(on_skip_station_clicked(int)));
        widget[0]->setStyleSheet("background-color: rgb(150,0,0);");
    }
    connect(this,SIGNAL(emulate_skip_click(int)),this,SLOT(emulate_skip(int)));
    xmlWriter->writeEndElement();
    xmlWriter->writeEndDocument();
    file->close();
}

///////////////////// STRUCTURE FILLING FOR SELECTED ROUTE //////////////////////
void train_route::gps_packet_handler(qint64 event,void *data)
{
    gps_packet = *(union gps_union *)data;
    gps_packet.data.status.bits.to_be_processed = 1;
    date_time.clear();
    date_time = QString::number(gps_packet.data.cpu.time.hrs) + ":" + QString::number(gps_packet.data.cpu.time.min) + ":" + QString::number(gps_packet.data.cpu.time.sec ) +"   ";
    date_time += QString::number(gps_packet.data.cpu.date.day) + "/" + QString::number(gps_packet.data.cpu.date.month) + "/20" + QString::number(gps_packet.data.cpu.date.yrs);
    // ui->date_time->setText(date_time);
}
void train_route::structure_filling(bool slave_train)
{
    fill_train_struct(slave_train);
    fill_stn_struct();
    show_train_info();
    emit add_stations();
    emit simulate("/home/apaul/apaul_projects/qtmop/etc/sim/MSB-VLC.TXT");
    calculate_multiplying_factor();
}
void train_route::emulate_skip(int id)
{
    emit skip_button[id]->click();
}
void train_route::show_train_info()
{
    //   QFile file("/home/apaul/Documents/running_route.xml");

    if (!file->open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(0, "Error!", "Error opening file");
    }
    xmlWriter->setDevice(file);
    xmlWriter->writeStartDocument();
    xmlWriter->setAutoFormatting(true);
    xmlWriter->writeStartElement("CATALOG");
    xmlWriter->writeStartElement("ROUTEtrain");
    ui->train_name->setText(master_train_no);
    xmlWriter->writeAttribute("ROUTE",master_train_no);
    ui->source_station_name->setText(QString::fromUtf8((const char *)current_route_data.train.src.name.eng));
    xmlWriter->writeAttribute("SOURCE",QString::fromUtf8((const char *)current_route_data.train.src.name.eng));
    ui->via_name->setText(QString::fromUtf8((const char *)current_route_data.train.mid.name.eng));
    xmlWriter->writeAttribute("VIA",QString::fromUtf8((const char *)current_route_data.train.mid.name.eng));
    ui->destination_station_name->setText(QString::fromUtf8((const char *)current_route_data.train.des.name.eng));
    xmlWriter->writeAttribute("DESTINATION",QString::fromUtf8((const char *)current_route_data.train.des.name.eng));
    ui->coach_count->setText(QString::number(current_route_data.train.coach_count));
    xmlWriter->writeAttribute("COACHCOUNT",QString::number(current_route_data.train.coach_count));
    if(ladies_special)
    {
        ui->ladies_special_type->setText("Yes");
        xmlWriter->writeAttribute("LS","YES");
    }
    else
    {
        ui->ladies_special_type->setText("No") ;
        xmlWriter->writeAttribute("LS","NO");
    }
    if(fast)
    {
        ui->slow_fast_type->setText("Fast")    ;
        xmlWriter->writeAttribute("TRAINTYPE","FAST");
    }
    if(slow)
    {
        ui->slow_fast_type->setText("Slow")    ;
        xmlWriter->writeAttribute("TRAINTYPE","SLOW");
    }
    show_handicap_coaches();
    xmlWriter->writeAttribute("DISTANCE",  QString::number(current_route_data.train.journ_dist));
    xmlWriter->writeAttribute("NEXT","0");
    xmlWriter->writeAttribute("GPSSTAT","NC");
    xmlWriter->writeAttribute("SPEED","NC");
    xmlWriter->writeAttribute("PERIPHERY","IN");
    emit send_route_info(FC_RSF);
    udp_connection->hcd_timer->start();
    xmlWriter->writeEndElement();
}

/********************************************************************************/

void train_route::on_skip_station_clicked(int id)
{
    QListWidgetItem *current_item;
    QWidget *current_widget;
    current_item = ui->listWidget->item(id);
    current_widget =  ui->listWidget->itemWidget(current_item);
    current_route_data.stn[id].status.bits.station_skipped = !current_route_data.stn[id].status.bits.station_skipped;
    //   current_item->setForeground(QBrush(QColor(200,0,0,100)));
}

void train_route::update_date_time()
{
    //date_time.clear();
    //current_date = QDate::currentDate();
    //date_time.append(current_date.toString(Qt::TextDate));
    //date_time.append("  ");
    //current_time = QTime::currentTime();
    //date_time.append(current_time.toString(Qt::TextDate));
    ui->date_time->setText(date_time);
    ui->coach_count->adjustSize();
    route_tasks();
    /*********************** Replacing XML CONTENT ********************************************************/
    if (!updating_file->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "unable to open xml file";
        return;
    }
    QByteArray xmlData(updating_file->readAll());
    QDomDocument doc("route_stat");
    QDomNodeList n;
    doc.setContent(xmlData);
    QDomElement root = doc.firstChildElement("CATALOG");
    QDomElement routetrain = root.firstChildElement("ROUTEtrain");
    routetrain.setAttribute("GPSSTAT",(date_time));
    if(!isRouteEnded)
    {
    routetrain.setAttribute("SPEED",QString::number(gps_packet.data.cpu.speed/100,'g',2));
    routetrain.setAttribute("DISTANCE",QString::number(current_route_data.stn[current_route_data.status.next_halting_stn].distance_from_curr_loc,'g',3));
    }
    else
    {
        routetrain.setAttribute("SPEED","0");
        routetrain.setAttribute("DISTANCE","0");
    }
    updating_file->resize(0);
    QTextStream stream(updating_file);
    stream.setDevice(updating_file);
    doc.save(stream, 4);
    updating_file->close();
}

void train_route::src_mid_des_station_name_filling()
{
    /////////////////////////////////////   SOURCE STAION NAME   /////////////////////////////////
    QSqlQuery get_source_station_name_eng("SELECT * FROM `tbl_StationName` WHERE `station_code`='"+QString::fromLatin1((const char *)current_route_data.train.src_stn_code)+"' and `stn_LangId`='english' ");
    get_source_station_name_eng.first();
    memcpy(current_route_data.train.src.name.eng,get_source_station_name_eng.value(StationName::STATION_NAME).toString().toLatin1(),get_source_station_name_eng.value(StationName::STATION_NAME).toString().size());
    QSqlQuery get_source_station_name_hin("SELECT * FROM `tbl_StationName` WHERE `station_code`='"+QString::fromUtf8((const char *)current_route_data.train.src_stn_code)+"' and `stn_LangId`='Hindi' ");
    get_source_station_name_hin.first();
    memcpy(current_route_data.train.src.name.hin,get_source_station_name_hin.value(StationName::STATION_NAME).toString().toLatin1(),get_source_station_name_hin.value(StationName::STATION_NAME).toString().size());
    QSqlQuery get_source_station_name_reg("SELECT * FROM `tbl_StationName` WHERE `station_code`='"+QString::fromUtf8((const char *)current_route_data.train.src_stn_code)+"' and `stn_LangId`='Tamil'");
    get_source_station_name_reg.first();
    memcpy(current_route_data.train.src.name.reg1,get_source_station_name_reg.value(StationName::STATION_NAME).toString().toLatin1(),get_source_station_name_reg.value(StationName::STATION_NAME).toString().size());
    ////////////////////////////////////    VIA STATION NAME    /////////////////////////
    QSqlQuery get_via_station_name("SELECT `station_name` FROM `tbl_StationName` WHERE `station_code`='"+QString::fromUtf8((const char *)current_route_data.train.mid_stn_code)+"' and `stn_LangId`='english' ");
    get_via_station_name.first();
    memcpy(current_route_data.train.mid.name.eng,get_via_station_name.value(0).toString().toLatin1(),get_via_station_name.value(0).toString().size());
    QSqlQuery get_via_station_name_hin("SELECT * FROM `tbl_StationName` WHERE `station_code`='"+QString::fromUtf8((const char *)current_route_data.train.mid_stn_code)+"' and `stn_LangId`='Hindi' ");
    get_via_station_name_hin.first();
    memcpy(current_route_data.train.mid.name.hin,get_via_station_name_hin.value(StationName::STATION_NAME).toString().toLatin1(),get_via_station_name_hin.value(StationName::STATION_NAME).toString().size());
    QSqlQuery get_via_station_name_reg("SELECT * FROM `tbl_StationName` WHERE `station_code`='"+QString::fromUtf8((const char *)current_route_data.train.mid_stn_code)+"' and `stn_LangId`='Tamil'");
    get_via_station_name_reg.first();
    memcpy(current_route_data.train.mid.name.reg1,get_via_station_name_reg.value(StationName::STATION_NAME).toString().toLatin1(),get_via_station_name_reg.value(StationName::STATION_NAME).toString().size());

    ///////////////////////////////////  DESTINATION STATION NAME //////////////////
    QSqlQuery get_destination_station_name("SELECT `station_name` FROM `tbl_StationName` WHERE `station_code`='"+QString::fromUtf8((const char *)current_route_data.train.des_stn_code)+"' and `stn_LangId`='english' ");
    get_destination_station_name.first();
    memcpy(current_route_data.train.des.name.eng,get_destination_station_name.value(0).toString().toLatin1(),get_destination_station_name.value(0).toString().size());
    QSqlQuery get_destination_station_name_hin("SELECT * FROM `tbl_StationName` WHERE `station_code`='"+QString::fromUtf8((const char *)current_route_data.train.des_stn_code)+"' and `stn_LangId`='Hindi' ");
    get_destination_station_name_hin.first();
    memcpy(current_route_data.train.des.name.hin,get_destination_station_name_hin.value(StationName::STATION_NAME).toString().toLatin1(),get_destination_station_name_hin.value(StationName::STATION_NAME).toString().size());
    QSqlQuery get_destination_station_name_reg("SELECT * FROM `tbl_StationName` WHERE `station_code`='"+QString::fromUtf8((const char *)current_route_data.train.des_stn_code)+"' and `stn_LangId`='Tamil'");
    get_destination_station_name_reg.first();
    memcpy(current_route_data.train.des.name.reg1,get_destination_station_name_reg.value(StationName::STATION_NAME).toString().toLatin1(),get_destination_station_name_reg.value(StationName::STATION_NAME).toString().size());
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
            current_route_data.train.ladies_special = 'Y';
        }
        else
        {
            ladies_special = false;
            current_route_data.train.ladies_special = 'N';
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
            current_route_data.train.ladies_special = 'Y';
        }
        else
        {
            ladies_special = false;
            current_route_data.train.ladies_special = 'N';
        }
        if(query_slow_fast_status_master.value(0).toString() == "S")
        {
            slow=true;
            fast=false;
            current_route_data.train.slow_fast = 'S';
        }
        else
        {
            fast=true;
            slow=false;
            current_route_data.train.slow_fast = 'F';
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
    xmlWriter->writeAttribute("HC",handicap_coach_no);
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
        current_route_data.train.no_of_stns = current_train_info.value(TrainNumber::TOTAL_STATION_ROUTE).toInt();
        current_route_data.train.journ_dist = current_train_info.value(TrainNumber::JRNY_DISTANCE).toInt();
        arr_time_master = current_train_info.value((TrainNumber::ARR_TIME)).toString().split(":");
        dep_time_master = current_train_info.value(TrainNumber::DEP_TIME).toString().split(":");
    }
    QSqlQuery find_coach_count("SELECT `coach_count` FROM `configuration`");
    find_coach_count.first();
    current_route_data.train.coach_count = find_coach_count.value(0).toInt();
    if(!slave_train)
    {
        current_route_data.train.arr_time_hrs = arr_time_master.at(Time::HOURS).toInt();
        current_route_data.train.arr_time_min = arr_time_master.at(Time::MINUTES).toInt();
        current_route_data.train.dep_time_hrs = dep_time_master.at(Time::HOURS).toInt();
        current_route_data.train.dep_time_min = dep_time_master.at(Time::MINUTES).toInt();
    }
    else
    {
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
    /*    qDebug() << "train Number" << QString::fromUtf8((const char *)current_route_data.train.train_num);
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
    qDebug() << "Dep Time MINUTES" << QString::number(current_route_data.train.dep_time_min);*/
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
    for(loop_count=0;loop_count<station_codes.size();loop_count++)
    {

        current_route_data.stn[loop_count].wait_time = '\0';
        QSqlQuery get_each_station_info("SELECT * FROM `tbl_RouteMaster` WHERE `stn_code`='"+ station_codes.at(loop_count) +"' and `train_sno`= '"+master_train_no+"'");
        get_each_station_info.first();
        QSqlQuery get_stn_name("SELECT `station_name`,`stn_LangId` from `tbl_StationName` where `station_code` = '" + station_codes.at(loop_count) +"'");
        QStringList names;
        QStringList language;
        while(get_stn_name.next())
        {
            names<<get_stn_name.value(0).toString();
            language<<get_stn_name.value(1).toString();
        }
        for(int k=0;k<3;k++)
        {
            QSqlQuery get_lang_codes("SELECT `lang_id` from `Language` WHERE `lang_name` = '" + language[k] + "'");
            get_lang_codes.first();
            if(get_lang_codes.value(0).toInt() > 1)
                memcpy(current_route_data.stn[loop_count].stn_name[2],names[k].toLatin1(),names[k].length());
            else
                memcpy(current_route_data.stn[loop_count].stn_name[get_lang_codes.value(0).toInt()],names[k].toLatin1(),names[k].length());
        }
        memcpy(current_route_data.stn[loop_count].stn_code,get_each_station_info.value(RouteMaster::STN_CODE).toString().toStdString().c_str(),get_each_station_info.value(RouteMaster::STN_CODE).toString().size());
        if(get_each_station_info.value(RouteMaster::PLATFORM_DIRECTION).toString() == "L")
            current_route_data.stn[loop_count].bits.pf_left = true;
        else
            current_route_data.stn[loop_count].bits.pf_left = false;
        if(fast)
            current_route_data.stn[loop_count].bits.fast_train = true;
        else
            current_route_data.stn[loop_count].bits.fast_train = false;
        current_route_data.stn[loop_count].distance_frm_src = get_each_station_info.value(RouteMaster::DISTANCE_FRM_SOURCE).toFloat();// - previous_distance;
        current_route_data.stn[loop_count].wait_time                      = get_each_station_info.value(RouteMaster::WAIT_TIME).toInt();
        previous_distance                                                 = get_each_station_info.value(RouteMaster::DISTANCE_FRM_SOURCE).toFloat();
        current_route_data.stn[loop_count].status.bits.station_skipped    = false;
        current_route_data.stn[loop_count].arrival_peri                   = get_each_station_info.value(RouteMaster::ARR_TRIGGERING).toInt();
        current_route_data.stn[loop_count].approaching_peri               = get_each_station_info.value(RouteMaster::APP_TRIGGERING).toInt();
        current_route_data.stn[loop_count].departure_peri                 = 50;//get_each_station_info.value(RouteMaster::DEP_TRIGGERING).toInt();

        QSqlQuery get_long_latt_for_each_station("SELECT * FROM `tbl_StationCode` WHERE `station_code`='"+station_codes.at(loop_count)+"'");
        get_long_latt_for_each_station.first();
        current_route_data.stn[loop_count].loc.coordintes.longitude       = get_long_latt_for_each_station.value(StationCode::LONGITUDE).toFloat();
        current_route_data.stn[loop_count].loc.coordintes.latitude        = get_long_latt_for_each_station.value(StationCode::LATITUDE).toFloat();

        uword temp_lat_long1 = 0,temp_lat_long2 = 0;
        temp_lat_long1 = (uword)(current_route_data.stn[loop_count].loc.coordintes.latitude * 10000);
        temp_lat_long2 = (temp_lat_long1/1000000)*60*10000;
        temp_lat_long2 += (temp_lat_long1%1000000);
        current_route_data.stn[loop_count].loc.coordintes.latitude = (float)temp_lat_long2;

        temp_lat_long1 = (uword)(current_route_data.stn[loop_count].loc.coordintes.longitude * 10000);
        temp_lat_long2 = (temp_lat_long1/1000000)*60*10000;
        temp_lat_long2 += (temp_lat_long1%1000000);
        current_route_data.stn[loop_count].loc.coordintes.longitude = (float)temp_lat_long2;
    }
    station_codes.clear();
}
void train_route::generate_station_departure()
{

    /*********************** Replacing XML CONTENT ********************************************************/
    if (!updating_file->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "unable to open xml file";
        return;
    }
    QByteArray xmlData(updating_file->readAll());
    QDomDocument doc("route_stat");
    QDomNodeList n;
    doc.setContent(xmlData);
    QDomElement root = doc.firstChildElement("CATALOG");
    QDomElement routetrain = root.firstChildElement("ROUTEtrain");
    routetrain.setAttribute("NEXT",QString::number(current_route_data.status.next_halting_stn));
    routetrain.setAttribute("PERIPHERY","OUT");
    n = root.childNodes();
    //  qDebug()<<n.length();
    updating_file->resize(0);
    QTextStream stream(updating_file);
    stream.setDevice(updating_file);
    doc.save(stream, 4);
    updating_file->close();
    emit send_route_info(FC_SDF);

}

int train_route::on_next_station_clicked()
{
    generate_station_departure();

    /*********************** Replacing XML CONTENT ********************************************************/
check_again:
    if(current_route_data.stn[current_route_data.status.next_halting_stn].status.bits.station_skipped)
    {
        /* if(current_route_data.status.next_halting_stn!=0)
        {
            QListWidgetItem *prev_item;
            QWidget *prev_widget;
         // prev_item = ui->listWidget->item(current_route_data.status.next_halting_stn-1);
            prev_item = ui->listWidget->item(current_station);
            prev_widget =  ui->listWidget->itemWidget(prev_item);
            prev_widget->setDisabled(true);
            prev_widget->setStyleSheet("background-color: rgba(150,150,150,255);color: rgb(0,0,0);");
        }*/
        current_route_data.status.next_halting_stn ++ ;
        goto check_again;
    }
    else
    {
        if(current_route_data.status.next_halting_stn!=0)
        {
            QListWidgetItem *prev_item,*second_prev_item;
            QWidget *prev_widget,*second_prev_widget;
            prev_item = ui->listWidget->item(current_route_data.status.next_halting_stn);
            prev_widget = ui->listWidget->itemWidget(prev_item);
            prev_widget->setDisabled(true);
            prev_widget->setStyleSheet("background-color: rgb(150,0,0);");
            //  second_prev_item = ui->listWidget->item(current_route_data.status.next_halting_stn-1);
            second_prev_item = ui->listWidget->item(current_station);

            second_prev_widget = ui->listWidget->itemWidget(second_prev_item);
            second_prev_widget->setDisabled(true);
            second_prev_widget->setStyleSheet("background-color: rgba(150,150,150,255);color: rgb(190,190,190);");
        }
        QListWidgetItem *current_item;
        QWidget *current_widget;
        current_station = current_route_data.status.next_halting_stn;
        while(current_route_data.stn[current_route_data.status.next_halting_stn+1].status.bits.station_skipped)
        {
            QListWidgetItem *prev_item,*second_prev_item;
            QWidget *prev_widget,*second_prev_widget;
            prev_item = ui->listWidget->item(current_route_data.status.next_halting_stn+1);
            prev_widget = ui->listWidget->itemWidget(prev_item);
            prev_widget->setDisabled(true);

            prev_widget->setStyleSheet("background-color: rgba(150,150,150,255);");
            second_prev_item = ui->listWidget->item(current_route_data.status.next_halting_stn);
            second_prev_widget = ui->listWidget->itemWidget(second_prev_item);
            //   second_prev_widget->setDisabled(true);
            // second_prev_widget->setStyleSheet("background-color: rgb(150,150,150);");
            current_route_data.status.next_halting_stn = current_route_data.status.next_halting_stn + 1;
            //            QDomElement cs = n.at(current_route_data.status.next_halting_stn + 1).toElement();
            //          qDebug() << "SKIPPED STOP  NAME" << cs.attribute("STOP");
            //        cs.setAttribute("ADD","0");
            //      cs.setAttribute("PFD","LEFT");
        }

        current_item = ui->listWidget->item(current_route_data.status.next_halting_stn+1);
        current_widget = ui->listWidget->itemWidget(current_item);
        current_widget->setStyleSheet("background-color: rgb(0, 150,0);");
        //  current_route_data.status.next_halting_stn ++ ;
        //   current_route_data.status.next_halting_stn -- ;
        //  emit send_route_info(FC_REF);
        ///////////////////////// SET AUTO SCROLLING OF VIEW //////////////////////
        ui->listWidget->setAutoScroll(true);
        ui->listWidget->setCurrentItem(ui->listWidget->item(current_route_data.status.next_halting_stn+1));
        ///////////////////////////////////////////////////////////////////////////
        if(current_route_data.stn[current_route_data.status.next_halting_stn].bits.pf_left)
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


        current_route_data.status.next_halting_stn ++;

        if(((current_route_data.status.next_halting_stn)+1) == (station_codes.size()))
        {
            ui->next_station->setDisabled(true);
            ui->next_station->setStyleSheet(" color: rgb(50,30,130);");
            //            emit send_route_info(FC_REF);
        }
    }
    return 0;
}
void train_route::generate_station_arrival()
{
    qDebug() << "/////////   halting station   //////" << current_route_data.status.next_halting_stn;

    if(current_route_data.status.next_halting_stn == (station_codes.size()))
    {
        emit send_route_info(FC_REF);
        isRouteEnded = true ;
        update_date_time();
         emit route_end();
        qDebug() << "/////////   halting station   //////" << current_route_data.status.next_halting_stn;
    }
    else
        emit send_route_info(FC_SAF);
    if (!updating_file->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "unable to open xml file";
        return;
    }

    QByteArray xmlData(updating_file->readAll());
    QDomDocument doc("route_stat");
    QDomNodeList n;
    doc.setContent(xmlData);
    QDomElement root = doc.firstChildElement("CATALOG");
    QDomElement routetrain = root.firstChildElement("ROUTEtrain");
    routetrain.setAttribute("PERIPHERY","IN");
    updating_file->resize(0);
    QTextStream stream(updating_file);
    stream.setDevice(updating_file);
    doc.save(stream, 4);
    updating_file->close();
}

void train_route::on_station_arrived_clicked()
{
    if(current_route_data.status.next_halting_stn == (station_codes.size()))
    {
        // ui->next_station->setStyleSheet(" color: rgb(50,30,130);");
        current_route_data.status.next_halting_stn --;
    }
    else
    {
        current_route_data.status.next_halting_stn = current_station;
        current_route_data.status.next_halting_stn ++ ;
    }
    generate_station_arrival();
}
void train_route::route_tasks()
{
    // qDebug()<<"route_tasks() route.cpp called..;";
    //   manage_device_updates();
    if(gps_packet.data.status.bits.to_be_processed)
    {
        gps_packet.data.status.bits.to_be_processed = 0;
        curr_lattit = gps_packet.data.cpu.latit;
        curr_longit = gps_packet.data.cpu.longit;
        if(current_route_data.status.flags.bits.position_identified)
        {
            /*********************************************************************************************************************************************************/
            /***********************Calculate distances based on stop lat longs and the curr lat longs****************************************************************/
            /*********************************************************************************************************************************************************/
            current_route_data.stn[current_route_data.status.next_halting_stn].gps_distance_from_prev_loc = current_route_data.stn[current_route_data.status.next_halting_stn].gps_distance_from_curr_loc;
            current_route_data.stn[current_route_data.status.next_halting_stn].gps_distance_from_curr_loc = get_distance(current_route_data.stn[current_route_data.status.next_halting_stn].loc.coordintes.latitude,current_route_data.stn[current_route_data.status.next_halting_stn].loc.coordintes.longitude);
            current_route_data.stn[current_route_data.status.next_halting_stn].distance_from_prev_loc = current_route_data.stn[current_route_data.status.next_halting_stn].distance_from_curr_loc;
            double curr_distance = 0;
            curr_distance = current_route_data.stn[current_route_data.status.next_halting_stn].gps_distance_from_curr_loc;
            if(current_route_data.status.next_halting_stn)
                curr_distance = (((float)mul_factor[current_route_data.status.next_halting_stn - 1] * curr_distance) / 10000) + curr_distance;
            else
                curr_distance = (((float)mul_factor[0] * curr_distance) / 10000) + curr_distance;
            current_route_data.stn[current_route_data.status.next_halting_stn].distance_from_curr_loc = curr_distance;
            /*********************************************************************************************************************************************************/
            /***********************Calculate distances based on stop lat longs and the curr lat longs****************************************************************/
            /*********************************************************************************************************************************************************/

            /*********************************************************************************************************************************************************/
            /***********************Generate Arrival Departure triggers based on the distance of current stop form the current location*******************************/
            /*********************************************************************************************************************************************************/
            if(((current_route_data.stn[current_route_data.status.next_halting_stn].distance_from_curr_loc*1000) <= current_route_data.stn[current_route_data.status.next_halting_stn].approaching_peri) && ((current_route_data.stn[current_route_data.status.next_halting_stn].distance_from_prev_loc*1000) > current_route_data.stn[current_route_data.status.next_halting_stn].approaching_peri))
            {
                //    qDebug() << "WITHIN 1 KM OF " << QString::fromLatin1((const char*)current_route_data.stn[current_route_data.status.next_stn].stn_name);
                //emit route_events(STOP_APPROACHING,0);
            }
            else if(((int)(current_route_data.stn[current_route_data.status.next_halting_stn].distance_from_curr_loc*1000) <= current_route_data.stn[current_route_data.status.next_halting_stn].arrival_peri) && ((current_route_data.stn[current_route_data.status.next_halting_stn].distance_from_prev_loc*1000) > (current_route_data.stn[current_route_data.status.next_halting_stn].distance_from_curr_loc*1000)))
            {
                if(current_route_data.status.flags.bits.inside_peri == 0)
                {
                    //       qDebug() << "ENTERED ENTRY PERIPHERY OF " << QString::fromLatin1((const char*)current_route_data.stn[current_route_data.status.next_halting_stn].stn_name);
                    current_route_data.status.flags.bits.inside_peri = 1;
                    current_route_data.status.flags.bits.outside_peri = 0;
                    //emit route_events(STOP_ARRIVAL,0);
                    generate_station_arrival();
                }
            }
            else if(((int)(current_route_data.stn[current_route_data.status.next_halting_stn].distance_from_curr_loc*1000) > current_route_data.stn[current_route_data.status.next_halting_stn].departure_peri) && ((current_route_data.stn[current_route_data.status.next_halting_stn].distance_from_prev_loc*1000) < (current_route_data.stn[current_route_data.status.next_halting_stn].distance_from_curr_loc*1000)))
            {
                if(current_route_data.status.flags.bits.outside_peri == 0 && current_route_data.status.flags.bits.inside_peri == 1)
                {
                    //      qDebug() << "LEFT EXIT PERIPHERY OF " << QString::fromLatin1((const char*)current_route_data.stn[current_route_data.status.next_halting_stn].stn_name);
                    // current_route_data.Prev_stop = current_route_data.status.next_halting_stn;
                    current_route_data.status.next_halting_stn++;
                    current_route_data.status.next_stn = current_route_data.status.next_halting_stn + 1;
                    current_route_data.status.flags.bits.inside_peri = 0;
                    current_route_data.status.flags.bits.outside_peri = 1;
                    generate_station_departure();
                    //emit route_events(STOP_DEPARTURE,0);
                }
            }
            /*********************************************************************************************************************************************************/
            /***********************Ended Arrival Departure triggers based on the distance of current stop from the current location**********************************/
            /*********************************************************************************************************************************************************/
        }
        if(current_route_data.status.flags.bits.route_info_avail && (!current_route_data.status.flags.bits.position_identified))
            lost_path_recovery();
    }
}


void train_route::lost_path_recovery()
{

    int nearest_stn_no = current_route_data.status.next_halting_stn;
    float actual_distance_between_currpt_n_a,actual_distance_between_currpt_n_b,actual_distance_between_currpt_n_c;
    while(current_route_data.status.next_halting_stn <  current_route_data.train.no_of_stns)
    {
        current_route_data.stn[current_route_data.status.next_halting_stn].distance_from_curr_loc = get_distance(current_route_data.stn[current_route_data.status.next_halting_stn].loc.coordintes.latitude,current_route_data.stn[current_route_data.status.next_halting_stn].loc.coordintes.longitude);
        current_route_data.status.next_halting_stn++;
    }
    while(1)
    {
        while((current_route_data.stn[nearest_stn_no].distance_from_curr_loc > current_route_data.stn[nearest_stn_no + 1].distance_from_curr_loc) && (nearest_stn_no < current_route_data.train.no_of_stns))
            nearest_stn_no++;
        current_route_data.status.next_halting_stn = nearest_stn_no;
        if(!current_route_data.status.next_halting_stn && current_route_data.stn[0].distance_from_curr_loc < track_dist_bn_stns[0])
        {
            current_route_data.status.next_halting_stn++;
            break;
        }
        else if(current_route_data.status.next_halting_stn ==  (current_route_data.train.no_of_stns - 1))
        {
            if(current_route_data.stn[current_route_data.status.next_halting_stn].distance_from_curr_loc < track_dist_bn_stns[current_route_data.status.next_halting_stn - 1])
                break;
            else
            {
                current_route_data.status.next_halting_stn = 0;
                return;
            }
        }
        else
        {
            actual_distance_between_currpt_n_a = (((float)mul_factor[nearest_stn_no - 1] * current_route_data.stn[nearest_stn_no - 1].distance_from_curr_loc)/10000) + current_route_data.stn[nearest_stn_no - 1].distance_from_curr_loc;
            actual_distance_between_currpt_n_b = (((((float)mul_factor[nearest_stn_no - 1] + (float)mul_factor[nearest_stn_no - 1])/2)* current_route_data.stn[nearest_stn_no].distance_from_curr_loc)/10000) + current_route_data.stn[nearest_stn_no].distance_from_curr_loc;
            actual_distance_between_currpt_n_c = (((float)mul_factor[nearest_stn_no] * current_route_data.stn[nearest_stn_no + 1].distance_from_curr_loc)/10000) + current_route_data.stn[nearest_stn_no + 1].distance_from_curr_loc;
            if(actual_distance_between_currpt_n_b < 0.800)
                break;
            if(actual_distance_between_currpt_n_a < track_dist_bn_stns[nearest_stn_no - 1] && actual_distance_between_currpt_n_c > track_dist_bn_stns[nearest_stn_no])
                break;
            else if(actual_distance_between_currpt_n_a > track_dist_bn_stns[nearest_stn_no - 1] && actual_distance_between_currpt_n_c < track_dist_bn_stns[nearest_stn_no])
            {
                current_route_data.status.next_halting_stn++;
                break;
            }
            else if(actual_distance_between_currpt_n_b > track_dist_bn_stns[nearest_stn_no - 1])
            {
                while((current_route_data.stn[nearest_stn_no].distance_from_curr_loc > current_route_data.stn[nearest_stn_no + 1].distance_from_curr_loc) && (nearest_stn_no < current_route_data.train.no_of_stns))
                    nearest_stn_no++;
                if(current_route_data.status.next_halting_stn == current_route_data.train.no_of_stns - 1 && current_route_data.stn[current_route_data.status.next_halting_stn].distance_from_curr_loc < track_dist_bn_stns[current_route_data.status.next_halting_stn - 1])
                    break;

            }
            else if(actual_distance_between_currpt_n_b > track_dist_bn_stns[nearest_stn_no])
            {
                current_route_data.status.flags.bits.position_identified = 0;
                return;
            }
            else if(actual_distance_between_currpt_n_a < track_dist_bn_stns[nearest_stn_no - 1] && actual_distance_between_currpt_n_c < track_dist_bn_stns[nearest_stn_no])
            {
                if(temp_prev_distance != 0.0)
                {
                    if(gps_packet.data.cpu.speed>2 && temp_prev_distance > actual_distance_between_currpt_n_b)
                    {
                        current_route_data.status.flags.bits.right_angle = 0;
                        break;
                    }
                    else if(gps_packet.data.cpu.speed>2 && temp_prev_distance < actual_distance_between_currpt_n_b)
                    {
                        current_route_data.status.next_halting_stn++;
                        current_route_data.status.flags.bits.right_angle = 0;
                        break;
                    }
                    else
                        return;
                }
                temp_prev_distance = actual_distance_between_currpt_n_b;
                current_route_data.status.flags.bits.position_identified = 0;
                current_route_data.status.flags.bits.right_angle = 1;
            }
            else
                break;
        }
    }
    if(!current_route_data.status.flags.bits.right_angle)
    {
        current_route_data.status.flags.bits.position_identified = 1;
        // if(current_route_data.status.next_halting_stn)
        //    current_route_data.Prev_stop = current_route_data.status.next_halting_stn - 1;
        // else
        //2    current_route_data.Prev_stop = current_route_data.status.next_halting_stn;
        current_route_data.status.next_stn = current_route_data.status.next_halting_stn + 1;
        if((current_route_data.stn[current_route_data.status.next_halting_stn].distance_from_curr_loc*1000) > current_route_data.stn[current_route_data.status.next_halting_stn].arrival_peri)
        {
            current_route_data.status.flags.bits.outside_peri = 1;
            generate_station_departure();
            //emit route_events(STOP_DEPARTURE,0);
        }
        else
        {
            current_route_data.status.flags.bits.inside_peri = 1;
            generate_station_arrival();

            //emit route_events(STOP_ARRIVAL,0);
        }
    }
}
void train_route::calculate_multiplying_factor(void)
{
    float temp_mul_factor = 0;
    int stn_no = 0;
    int prev_stn_dist = current_route_data.stn[stn_no++].distance_frm_src;
    while(stn_no < current_route_data.train.no_of_stns)
    {
        track_dist_bn_stns[stn_no - 1]   = current_route_data.stn[stn_no].distance_frm_src - prev_stn_dist;
        prev_stn_dist = current_route_data.stn[stn_no].distance_frm_src;
        temp_mul_factor = get_distance_bn_pts(current_route_data.stn[stn_no - 1].loc.coordintes.latitude,current_route_data.stn[stn_no - 1].loc.coordintes.longitude,current_route_data.stn[stn_no].loc.coordintes.latitude,current_route_data.stn[stn_no].loc.coordintes.longitude);
        temp_mul_factor = (((float)(track_dist_bn_stns[stn_no - 1]) - temp_mul_factor)/temp_mul_factor)*10000;
        mul_factor[stn_no++ - 1] = (sinteger)temp_mul_factor;
    }
    current_route_data.status.flags.bits.route_info_avail  = 1;
}
float train_route::get_distance(float x2, float y2)
{
    float temp_distance;
    temp_distance = (curr_lattit - x2)*(curr_lattit - x2)+(curr_longit - y2)*(curr_longit - y2);
    temp_distance = std::sqrt(temp_distance);
    temp_distance = temp_distance * 176 / 945 / 1000;
    return(temp_distance);
}
float train_route::get_distance_bn_pts(float x1, float y1,float x2, float y2)
{
    float temp_distance;
    temp_distance = (x1 - x2)*(x1 - x2)+(y1 - y2)*(y1 - y2);
    temp_distance = std::sqrt(temp_distance);
    temp_distance = temp_distance * 176 / 945 / 1000;
    return(temp_distance);
}
void train_route::show_end_route()
{
    time_update.stop();
    QMessageBox* msgBox 	= new QMessageBox();
    msgBox->setWindowTitle("Train Route Ended");
    msgBox->setText("This Journey Ends Here!");
    msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
    msgBox->show();
}
