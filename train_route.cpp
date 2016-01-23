#include "train_route.h"
#include "ui_train_route.h"
extern QString master_train_no;
extern QString slave_train_no;
train_route::train_route(QSqlDatabase *emu_database,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::train_route)
{
    ui->setupUi(this);
}

train_route::~train_route()
{
    delete ui;
}

void train_route::current_selected_train_info(bool slave_train)
{

    QStringList source_destination_station_codes;
    QString source_station_name;
    QString destination_station_name;
    QString coach_count;
    QChar test = 1;
    bool slow=false;
    bool fast=false;

    /////////////////////////////////////////   STYLESHEETS OF LABELS   //////////////////////////////////
    ui->coach_count->setStyleSheet("color: rgb(0,0,255)");// BLUE COLOR
    ui->ladies_special_type->setStyleSheet("color: rgb(0,0,255)");// BLUE COLOR
    ui->slow_fast_type->setStyleSheet("color: rgb(0,0,255)");// BLUE COLOR
    ui->source_station_name->setStyleSheet("color: rgb(0,0,255)");// BLUE COLOR
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

    //////////////////////////// FIND LADIES_SPECIAL_STATUS OF CURRENT TRAIN ///////////////////
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
            ui->slow_fast_type->setText("Slow");
        else
            ui->slow_fast_type->setText("Fast");
    }
    else
    {
        QSqlQuery query_ladies_train_status("SELECT `ladies_train_status` FROM `tbl_TrainNumber` where `train_no`='"+ master_train_no + "'");
        QSqlQuery query_slow_fast_status("SELECT `train_status` FROM `tbl_slave_route` where `train_number`='"+ master_train_no + "'");
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
            ui->slow_fast_type->setText("Slow");
        else
            ui->slow_fast_type->setText("Fast");
    }
    QSqlQuery query_find_coach_count("SELECT `no_of_coaches` FROM `tbl_TrainNumber` where `train_no`='"+ master_train_no + "'");
    query_find_coach_count.next();
    qDebug() << query_find_coach_count.value(0).toString();
    ui->coach_count->setText(query_find_coach_count.value(0).toString());
}


