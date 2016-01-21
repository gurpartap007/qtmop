#include "train_route.h"
#include "ui_train_route.h"
extern QString selected_train_no;
extern int selected_train;
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

void train_route::current_selected_train_info()
{
    QStringList source_destination_station_codes;
    QString source_station_name;
    QString destination_station_name;
    QSqlRecord record_destination_station_name;
qDebug() << "Selected train in train route = " << selected_train_no;


/////////////////////////////  FINDING SOURCE/DESTINATION STATIONS ///////////////////////
qDebug() << "SELECT `src_stn_sno`,`dest_stn_sno` FROM `tbl_TrainNumber` where `train_no`='"+ selected_train_no+"'";
QSqlQuery query1("SELECT `src_stn_sno`,`dest_stn_sno` FROM `tbl_TrainNumber` where `train_no`='"+ selected_train_no+"'");
while(query1.next()){
    source_destination_station_codes.clear();
    QSqlRecord record = query1.record();
    for(int i=0; i < record.count(); i++)
        source_destination_station_codes << record.value(i).toString();
}
qDebug() << source_destination_station_codes;

///////////////////////////// FINDING SOURCE STATION NAME  ////////////////////
QSqlQuery query_find_source_station("SELECT `station_name` FROM `tbl_StationName` where `station_code`='"+ source_destination_station_codes.at(0) +"' and `stn_LangId`='English'");
query_find_source_station.next();
QSqlRecord record_source_station_name= query_find_source_station.record();
source_station_name = record_source_station_name.value(0).toString();
qDebug()  << "SOURCE STATION NAME = " << source_station_name;

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////// FINDING DESTINATION STATION NAME  ///////////////////
QSqlQuery query_find_destination_station("SELECT `station_name` FROM `tbl_StationName` where `station_code`='"+ source_destination_station_codes.at(1) +"' and `stn_LangId`='English'");
query_find_destination_station.next();
record_destination_station_name = query_find_destination_station.record();
destination_station_name = record_destination_station_name.value(0).toString();
qDebug() << "DESTINATION STATION NAME" << destination_station_name;
/////////////////////////////////////////////////////////////////////////////////
ui->source_station_name->setText(source_station_name);
ui->destination_station_name->setText(destination_station_name);
}
