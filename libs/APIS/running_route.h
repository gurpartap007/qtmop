
#ifndef RUNNING_ROUTE_H
#define RUNNING_ROUTE_H
#include "PIS_global.h"
#include "qt_headers.h"
#include "lgps.h"
#include "crc_lib.h"
#include "ui_running_route.h"
#include "PIS_Structs.h"
typedef enum
{
    TRAIN_DEPARTURE,
    STOP_APPROACHING,
    STOP_ARRIVAL,
    STOP_DEPARTURE,
    JOURNEY_END
}location_stat;
struct rxtx_struct
{
    unsigned char stx[4];
    unsigned char length[5];
    unsigned char src_id[13];
    unsigned char dest_id[19];
    unsigned char func_code[3];
    unsigned char frame_id[5];
    unsigned char frame_num[3];
    unsigned char data_crc_bytes[900];
};
struct pis_rxtx_struct
{
  unsigned char stx[2] ;
  qint16 length;
  struct cntrl_struct
  {
    unsigned char src_add;
    unsigned char dest_add;
    unsigned char sr_num;
  }cntrl;
  unsigned char fn_code;
  union data_struct
  {
    struct data_structt_message
    {
        unsigned char disp_mode_id;
        unsigned char langid;
        unsigned char train_num[6];
        unsigned char date;
        unsigned char month;
        unsigned char year;
        unsigned char hrs;
        unsigned char min;
        unsigned char sec;
        unsigned char start_time;
        unsigned char hold_time;
        unsigned char rpt_cnt;
        unsigned char brigthness;
        unsigned char future[2];
        unsigned char bytes[900];
     }dat;
     unsigned char data_crc_bytes[900];
  }data;
};
 union PIS_VIEWSHARED_EXPORT rxtx_union
{
    struct rxtx_struct buff;
    struct pis_rxtx_struct data;
    unsigned char bytes[sizeof(rxtx_struct)];
};


namespace Ui {
class running_route;
}

class PIS_VIEWSHARED_EXPORT running_route : public QWidget
{
    Q_OBJECT

public:
    explicit running_route(QWidget *parent = 0);
//    QList<MyThread*> threads;//list of thread objects
    ~running_route();
    int display_timer_id;
    int route_tasks_timer_id;
    int gps_timeout_timer_id;
    void calculate_multiplying_factor(void);
    QSerialPort *serial;
    QPixmap *pixmap;
    QTimer msg_timer;
    QTimer Read_timer;
    CRC_LIB crc_o;
    qint64 rdso0087protocol(QString msg_type,qint64 index);
    QStringList check_n_replace_voice_delim(QString,qint64);
    void openSerialPort();   // void paintEvent(QPaintEvent *);
    QByteArray rec_data;
    QMediaPlaylist *Playlist;
    QMediaPlayer *player;
    qint64 prev_safety_msg_id;
    union gps_union gps_packet;
    qint64 generate_alerts(int ,int);
    void close_timer(void);
//    QTextStream simulation_in_stream;
//    QFile simulation_file;

//    /* GPS file simulation */
//    gps_class *gps_ptr;

//    gps_serial *GPSSerial;
//    int SECOND_TIME=0;

public slots:
    void timerEvent(QTimerEvent *event);
    void message_generator(qint64,void *);
    void gps_data_collector(qint64,void *);
    void manage_device_updates(void);
    void mediachanged(int);
    void read_pkt(void);
    void check_pkt(void);
    void play_message(int *);
//    void initialise_display(void);
//    //void skip_event(void);
//    void gps_simulation();
//    void on_et_clicked();
//    void on_skip_clicked();
//    void on_announce_clicked();

//    void on_prm_clicked();

signals:
//    void Journey_Start(qint64 option);
//    void Pre_Recorded_Display();
//    void running_route_event(qint64 option,void *);
//    void route_ended();
//    void gps_file_selected();
//    void dis_ann_packet(qint64 option);
    void log_event(void);
    void route_events(qint64 event,void *data);
    void GPSSimulationActive(QString);

private:
    Ui::running_route *ui;
    void display_tasks(void);
    void route_tasks(union gps_union *data);
    float get_distance(float x2, float y2);
    float get_distance_bn_pts(float x1, float y1,float x2, float y2);
    void lost_path_recovery();
    float curr_lattit;
    float curr_longit;
    float temp_prev_distance;
    union rxtx_union slave_tx;
//    bool GPSDataEnabled;
//    QWidget *widget;
//    QHBoxLayout *widgetLayout;
//    QLabel *widgetText;

};

#endif // RUNNING_ROUTE_H
