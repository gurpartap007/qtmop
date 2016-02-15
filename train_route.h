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
class SkipButton;
}

class train_route : public QWidget
{
    Q_OBJECT

public:
    explicit train_route(QSqlDatabase *emu_database,QWidget *parent = 0);
    //   QSqlTableModel *master_train_model;
    QStringList source_destination_list;
    QStringList station_codes,station_names;
    QStringList source_destination_station_codes;
    //   QStandardItemModel *model;
    QFont *skip_button_font;
    QFont *station_name_font;
    QString getStringFromUnsignedChar( unsigned char *str );
    ~train_route();
signals:

    void add_stations();
    void skip_clicked(int);
    void fill_structure();
    // void rowsRemoved(QModelIndex,int,int);
public slots:
    void show_train_info();
    void current_selected_train_info(bool slave_train);
    void add_stations_for_current_train();
    void structure_filling(bool);

private slots:
    void on_skip_station_clicked(int id);
    void update_date_time();


private:
    Ui::train_route *ui;
    QTimer time_update;
    QString date_time;
    QDate current_date;
    QTime current_time;

};

#endif // TRAIN_ROUTE_H
