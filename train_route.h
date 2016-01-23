#ifndef TRAIN_ROUTE_H
#define TRAIN_ROUTE_H

#include <QWidget>
#include "header.h"
#include "sql_enums.h"
/** @brief Holds selected current route information and all related functions
    Detailed description follows here.
    @author Gurpartap Singh
    @date December 23 2015
    */
/** @file
 *
 */
namespace Ui {
class train_route;
}

class train_route : public QWidget
{
    Q_OBJECT

public:
    explicit train_route(QSqlDatabase *emu_database,QWidget *parent = 0);
    QSqlTableModel *master_train_model;
    QString source_station_name;
    QStringList destination_station_name;
    QString source_destination_name;
     QStringList source_destination_list;
    ~train_route();
public slots:
    void current_selected_train_info(bool slave_train);

private:
    Ui::train_route *ui;
};

#endif // TRAIN_ROUTE_H
