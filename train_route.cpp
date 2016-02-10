#include "train_route.h"
#include "skipbutton.h"
#include "ui_train_route.h"
extern QString master_train_no;
extern QString slave_train_no;
route_struct current_route_data;
train_route::train_route(QSqlDatabase *emu_database,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::train_route)
{
    ui->setupUi(this);
    connect(this,SIGNAL(add_stations()),this,SLOT(add_stations_for_current_train()));
    connect(this,SIGNAL(skip_clicked(int)),this,SLOT(current_selected_station(int)));
    connect(this,SIGNAL(fill_structure()),this,SLOT(structure_filling(bool)));
    connect(&time_update,SIGNAL(timeout()),this,SLOT(update_date_time()));
}

train_route::~train_route()
{
    delete ui;
}

void train_route::current_selected_train_info(bool slave_train)
{
    QString source_station_name;
    QString destination_station_name;
    QString coach_count;
    QString via_station_code,via_station_name;
    QString handicap_coach_no;
    bool slow=false;
    bool fast=false;

    ///////////////////////////////////////// TIMER FOR UPDATION OF TIME /////////////////////////////////
    time_update.setInterval(1000);
    time_update.start();
    //--------------------------------------------------------------------------------------------------//

    /////////////////////////////////////////   STYLESHEETS OF LABELS   //////////////////////////////////
    ui->coach_count->setStyleSheet("color: rgb(0,0,255)");             // BLUE COLOR
    ui->ladies_special_type->setStyleSheet("color: rgb(0,0,255)");     // BLUE COLOR
    ui->slow_fast_type->setStyleSheet("color: rgb(0,0,255)");          // BLUE COLOR
    ui->source_station_name->setStyleSheet("color: rgb(0,0,255)");     // BLUE COLOR
    ui->destination_station_name->setStyleSheet("color: rgb(0,0,255)");// BLUE COLOR
    //--------------------------------------------------------------------------------------------------//
    /////////////////////////////////  FINDING SOURCE/DESTINATION STATIONS CODES /////////////////////////
    QSqlQuery query_find_source_destination_station_codes("SELECT `src_stn_sno`,`dest_stn_sno` FROM `tbl_TrainNumber` where `train_no`='"+ master_train_no +"'");
    while(query_find_source_destination_station_codes.next())
    {
        source_destination_station_codes.clear();
        QSqlRecord record = query_find_source_destination_station_codes.record();
        for(int i=0; i < record.count(); i++)
            source_destination_station_codes << record.value(i).toString();
    }
    //**************************************************************************************************//

    ///////////////////////////// FINDING SOURCE STATION NAME BASED ON STATION CODE //////////////////////
    QSqlQuery query_find_source_station("SELECT `station_name` FROM `tbl_StationName` where `station_code`='"+ source_destination_station_codes.at(0) +"' and `stn_LangId`='English'");
    query_find_source_station.next();
    source_station_name = query_find_source_station.value(0).toString();
    //**************************************************************************************************//

    /////////////////////////// FINDING DESTINATION STATION NAME BASED ON STATION CODE ///////////////////
    QSqlQuery query_find_destination_station("SELECT `station_name` FROM `tbl_StationName` where `station_code`='"+ source_destination_station_codes.at(1) +"' and `stn_LangId`='English'");
    query_find_destination_station.next();
    destination_station_name = query_find_destination_station.value(0).toString();
    //**************************************************************************************************//
    ui->source_station_name->setText(source_station_name);
    ui->destination_station_name->setText(destination_station_name);

    //////////////////////////// FIND LADIES_SPECIAL_STATUS AND SLOW/FAST STATUS OF SLAVE TRAIN ///////////////////
    if (slave_train)
    {
        QSqlQuery query_ladies_train_status("SELECT `ladies_trn_status` FROM `tbl_slave_route` where `train_number`='"+ slave_train_no + "'");
        QSqlQuery query_slow_fast_status("SELECT `train_status` FROM `tbl_slave_route` where `train_number`='"+ slave_train_no + "'");
        query_ladies_train_status.next();
        query_slow_fast_status.next();
        if(query_ladies_train_status.value(0).toString().at(0) == 1)
        {
            ui->ladies_special_type->setText("Yes");
        }
        else
        {
            ui->ladies_special_type->setText("No");
        }
        if(query_slow_fast_status.value(0).toString() == "S")
        {
            ui->slow_fast_type->setText("Slow");
            current_route_data.train.slow_fast = 'S';
            slow=true;
        }
        else
        {
            ui->slow_fast_type->setText("Fast");
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
            ui->ladies_special_type->setText("Yes");
        }
        else
        {
            ui->ladies_special_type->setText("No");
        }
        if(query_slow_fast_status_master.value(0).toString() == "S")
            ui->slow_fast_type->setText("Slow");
        else
            ui->slow_fast_type->setText("Fast");
    }
    //**************************************************************************************************//

    ////////////////////////////////// FIND COACH COUNT OF CURRENT TRAIN  ////////////////////////////////
    QSqlQuery query_find_coach_count("SELECT `no_of_coaches` FROM `tbl_TrainNumber` where `train_no`='"+ master_train_no + "'");
    query_find_coach_count.next();
    coach_count = query_find_coach_count.value(0).toString();
    ui->coach_count->setText(coach_count);
    memcpy(current_route_data.train.coach_count,coach_count.toStdString().c_str(),sizeof(coach_count));

    //**************************************************************************************************//

    ////////////////////////////////// FIND VIA STATION OF CURRENT TRAIN  ////////////////////////////////

    QSqlQuery query_find_via_station_code("SELECT `via_stn_sno` FROM `tbl_TrainNumber` where `train_no`='"+ master_train_no + "'");
    query_find_via_station_code.first();
    via_station_code = query_find_via_station_code.value(0).toString();
    memcpy(current_route_data.train.mid_stn_code,via_station_code.toStdString().c_str(),sizeof(via_station_code));
    QSqlQuery query_find_via_station_name("SELECT `station_name` FROM `tbl_StationName` where `station_code`='"+ via_station_code +"' and `stn_LangId`='English'");
    query_find_via_station_name.first();
    via_station_name = query_find_via_station_name.value(0).toString();
    ui->via_name->setText(via_station_name);
    memcpy(current_route_data.train.mid.name.eng,via_station_name.toStdString().c_str(),sizeof(via_station_name));
    //**************************************************************************************************//

    ////////////////////////////////// FIND HANDICAP COACH NO'S OF CURRENT TRAIN  ////////////////////////////////

    QSqlQuery query_find_handicap_coaches("select `handicap_coach1`,`handicap_coach2` from `configuration`");
    query_find_handicap_coaches.next();
    handicap_coach_no=query_find_handicap_coaches.value(0).toString();
    handicap_coach_no.append("/");
    handicap_coach_no.append(query_find_handicap_coaches.value(1).toString());
    ui->handicap_coach->setText(handicap_coach_no);
    //**************************************************************************************************//
    ui->train_name->setText(master_train_no);

    emit fill_structure();
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
        station_name[loop_count] = new QLabel;
        widget[loop_count] = new QWidget(this);
        skip_button[loop_count] = new skipbutton("Skip",loop_count,station_name[loop_count],widget[loop_count],this);
        widgetLayout[loop_count] = new QHBoxLayout;
        item[loop_count] = new QListWidgetItem;
        spacer_item[loop_count] = new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed);
        skip_button[loop_count]->setFont(*skip_button_font);
        skip_button[loop_count]->setMinimumSize(QSize(400,50));
        station_name[loop_count]->setFont(*station_name_font);
        skip_button[loop_count]->setStyleSheet("QPushButton{ background-color: rgb(179, 179, 179); }QPushButton:pressed{background-color: rgb(100, 100, 100); }");
        widgetLayout[loop_count]->addWidget(skip_button[loop_count]);
        widgetLayout[loop_count]->addWidget(station_name[loop_count]);
        widgetLayout[loop_count]->addSpacerItem(spacer_item[loop_count]);
        widgetLayout[loop_count]->setAlignment(skip_button[loop_count],Qt::AlignLeft);
        widgetLayout[loop_count]->setAlignment(station_name[loop_count],Qt::AlignLeft);
        widget[loop_count]->setLayout(widgetLayout[loop_count]);
        widget[loop_count]->setStyleSheet("background-color: rgb(179,179,179);");
        ui->listWidget->addItem(item[loop_count]);
        item[loop_count]->setSizeHint(skip_button[loop_count]->minimumSizeHint());
        ui->listWidget->setItemWidget(item[loop_count],widget[loop_count]);

        QSqlQuery get_station_wait_time("SELECT `wait_time` FROM `tbl_RouteMaster` WHERE `train_sno`='"+ master_train_no +"' and `stn_code`= '"+station_codes.at(loop_count)+"' ");
        get_station_wait_time.first();
        if(!get_station_wait_time.value(0).toInt())
        {
            widget[loop_count]->setStyleSheet("background-color: rgb(200,200,200);");
            skip_button[loop_count]->setDisabled(true);
            station_name[loop_count]->setStyleSheet("color: rgb(150,150,150)");
        }


        QSqlQuery get_station_names("SELECT `station_name` FROM `tbl_StationName` WHERE `station_code`='"+station_codes.at(loop_count)+"' and `stn_LangId`='english' ");
        while(get_station_names.next())
        {
            station_name[loop_count]->setText(get_station_names.value(0).toString());
            item[loop_count]->setText(get_station_names.value(0).toString());
            //station_names.append(get_station_names.value(0).toString());
        }
        connect(skip_button[loop_count],SIGNAL(skip_clicked(int)),this,SLOT(on_skip_station_clicked(int)));

        widget[0]->setStyleSheet("background-color: rgb(255, 148, 124);");
    }
}

///////////////////// STRUCTURE FILLING FOR SELECTED ROUTE //////////////////////

void train_route::structure_filling(bool slave_train)
{
    QSqlQuery current_train_info("SELECT * FROM `tbl_TrainNumber` WHERE `train_no`='"+ master_train_no +"'");
    while(current_train_info.next())
    {
       qDebug() << "train info..." << current_train_info.value(0).toString();
       qDebug() << "train info..." << current_train_info.value(1).toString();
       qDebug() << "train info..." << current_train_info.value(2).toString();
       qDebug() << "train info..." << current_train_info.value(3).toString();
    }
    emit add_stations();
}

/********************************************************************************/

void train_route::on_skip_station_clicked(int id)
{
    qDebug() << "station skipped" << id;
    QListWidgetItem *current_item;
    QWidget *current_widget;
    current_item = ui->listWidget->item(id);
    current_widget =  ui->listWidget->itemWidget(current_item);
    current_widget->setStyleSheet("background-color: rgb(200,200,200);");

    //    ui->listWidget->setCurrentItem(current_item);

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
}


