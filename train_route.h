#ifndef TRAIN_ROUTE_H
#define TRAIN_ROUTE_H

#include <QWidget>
#include "header.h"
#include "sql_enums.h"
#include "display_communication.h"
#include "database.h"
#include <QXmlStreamWriter>
#include <QDomDocument>
#include "skipbutton.h"
#include "lgps.h"
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
     display_communication *udp_connection;
     QXmlStreamWriter *xmlWriter;
     QFile *file,*updating_file;
    ~train_route();
     skipbutton *skip_button[128];

signals:
    void add_stations();
    void fill_structure();
    void send_route_info(QString func_code);
    void emulate_skip_click(int);
    void simulate(QString filename);
public slots:
    void show_train_info();
    void add_stations_for_current_train();
    void structure_filling(bool);
    void emulate_skip(int);
    void gps_packet_handler(qint64 event,void *data);
    void route_tasks();
    void lost_path_recovery();
    float get_distance(float x2, float y2);
    void calculate_multiplying_factor(void);
    float get_distance_bn_pts(float x1, float y1,float x2, float y2);
private slots:
    void generate_station_departure();
    void generate_station_arrival();
    void on_skip_station_clicked(int id);
    void update_date_time();
    int on_next_station_clicked();

    void on_station_arrived_clicked();

private:
    void src_mid_des_station_name_filling();
    void find_ladies_and_slow_fast_status(bool slave_train);
    void show_handicap_coaches();
    void fill_train_struct(bool slave_train);
    void fill_stn_struct();
    Ui::train_route *ui;
    QTimer time_update;
    QString date_time;
    QString handicap_coach_no;
    QDate current_date;
    QTime current_time;
    union gps_union gps_packet;
    bool slow;
    bool fast;
    bool ladies_special;
    QStringList station_codes;
    QStringList source_destination_list;
    QStringList source_destination_station_codes;
    QFont *skip_button_font;
    QFont *station_name_font;
    float curr_lattit;
    float curr_longit;
    float temp_prev_distance;
};

#endif // TRAIN_ROUTE_H
