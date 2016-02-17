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
    explicit train_route(QWidget *parent = 0);
    ~train_route();

signals:
    void add_stations();
    void fill_structure();

public slots:
    void show_train_info();
    void add_stations_for_current_train();
    void structure_filling(bool);

private slots:
    void on_skip_station_clicked(int id);
    void update_date_time();
    int on_next_station_clicked();

private:
    void src_mid_des_station_name_filling();
    void find_ladies_and_slow_fast_status(bool slave_train);
    void show_handicap_coaches();
    void fill_train_struct(bool slave_train);
    void fill_stn_struct();
    Ui::train_route *ui;
    QTimer time_update;
    QString date_time,
            handicap_coach_no;
    QDate current_date;
    QTime current_time;
    bool slow,
         fast,
         ladies_special;
    QStringList station_codes,
                station_names,
                source_destination_list,
                source_destination_station_codes;
    QFont *skip_button_font,
          *station_name_font;
};

#endif // TRAIN_ROUTE_H
