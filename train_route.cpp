#include "train_route.h"
#include "ui_train_route.h"
//extern QString selected_train_no;
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
    QString ladies_special_train;
    QChar test = 1;
    bool slow=false;
    bool fast=false;
    QChar ladies_special=0;
    qDebug() << "Slave train =  " << slave_train;
    /////////////////////////////////  FINDING SOURCE/DESTINATION STATIONS CODES /////////////////////////
    QSqlQuery query1("SELECT `src_stn_sno`,`dest_stn_sno` FROM `tbl_TrainNumber` where `train_no`='"+ master_train_no +"'");
    while(query1.next())
    {
        source_destination_station_codes.clear();
        QSqlRecord record = query1.record();
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
        qDebug() << slave_train_no;
        QSqlQuery query_ladies_train_status("SELECT `ladies_trn_status` FROM `tbl_slave_route` where `train_number`='"+ slave_train_no + "'");
        query_ladies_train_status.next();
        ladies_special_train = query_ladies_train_status.value(0).toString();
        ladies_special = ladies_special_train.at(0);
        if(ladies_special == 1)
        {
            ui->ladies_special_type->setText("Yes");
         qDebug() << "This is ladies_special Train";
        }
        else
        {
        qDebug() << "This is not ladies_special train";
        ui->ladies_special_type->setText("No");
        }
        //ladies_special_train.append('\0');
        //qDebug() << check.contains(ladies_special_train.at(0));
        //pData = new char(ladies_special_train.size());
       // memset(pData,ladies_special_train.size(),'\0');
        //memcpy(pData, ladies_special_train.data(),ladies_special_train.size());
        //qDebug() << ladies_special_train.at(1);
        // qDebug() << ladies_special_train.at(2);
        //qDebug() << ladies_special_train->size();
        //qDebug() << "TSET BIT " << ladies_special_train->testBit(0);
        //qDebug() << "LADIES SPECIAL TRAIN -->" <<  query_ladies_train_status.value(0).toInt();
        //}
    }
}


