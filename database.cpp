#include "database.h"
extern QStringList train_routes;
QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
database::database(QObject *parent) : QObject(parent)
{

    db.setHostName("localhost");
    db.setDatabaseName("emu");
    db.setUserName("root");
    db.setPassword("terron");
    if(db.open())
        qDebug() << "Database Successfully opened";
    data_name = new QStringList;
    QStringList tables = db.tables();
    qDebug() << tables;
    QSqlQuery announcements_query("SELECT * FROM `final_tbl_routemaster`");
    while (announcements_query.next()) {
        train_routes.append(announcements_query.value(0).toString());
    }
   train_routes.append(NULL);
}

database::~database()
{

}

