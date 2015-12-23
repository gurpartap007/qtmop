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


}

database::~database()
{

}

