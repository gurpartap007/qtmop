#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include "header.h"
#include "sql_enums.h"
/** @brief Mysql Database class containing all routes and train numbers,messages

    Detailed description follows here.
    @author Gurpartap Singh
    @date December 23 2015
    */
/** @file
 *
 */
class database : public QObject
{
    Q_OBJECT
public:
    explicit database(QObject *parent = 0);
    ~database();
    QStringList *data_name;
};

#endif // DATABASE_H
