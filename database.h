#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include "header.h"
#include "sql_enums.h"

class database : public QObject
{
    Q_OBJECT
public:
    explicit database(QObject *parent = 0);
    ~database();
    QStringList *data_name;
};

#endif // DATABASE_H
