#include "database.h"

database::database(QObject *parent) : QObject(parent)
{
QSqlDatabase db= QSqlDatabase::addDatabase("QMYSQL");
db.setHostName("localhost");
db.setDatabaseName("BUS_PIS");
db.setUserName("root");
db.setPassword("terron");
if(db.open())
qDebug() << "Database Successfully opened";
data_name = new QStringList;
///////// Sending Query to BUS_PIS Database to give announcements DATA  //////////////
QSqlQuery announcements_query("SELECT * FROM `Annuciation_device_type_table` where `Message_code` = '75' and `Page` = '01'");
while (announcements_query.next()) {
    data_name->append(announcements_query.value(Annuciation_device_type_table::Segment_data).toString());
    //qDebug() << data_name;
}
qDebug() << data_name->at(0);
}

database::~database()
{

}

