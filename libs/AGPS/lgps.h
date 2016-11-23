#ifndef LGPS_H
#define LGPS_H

#define LIB_VERSION "1.0.0"

#include "lgps_global.h"
#include <QObject>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QTimer>
#include <QtSerialPort/QSerialPort>

#define DM   "/dev/ttyUSB0"
#define NMEA "/dev/ttyUSB1"
#define AT   "/dev/ttyUSB2"
#define PPP  "/dev/ttyUSB3"

#define NEW_GPS_PKT 1
#define SIZE_GPS_RMC_MSG    128
#define	KNOTS_TO_KMS_FACTOR					(float)1.852

struct time_struct
{
    unsigned char hrs;
    unsigned char min;
    unsigned char sec;
};

#define	TIME_STRUCT								sizeof(struct time_struct)

struct date_struct
{
    unsigned char day ;
    unsigned char month;
    unsigned char yrs ;
};

#define	DATE_STRUCT								sizeof(struct date_struct)

struct gps_param_struct
{
    float latit;
    float longit;
    float speed;
    float heading;
    struct time_struct time;
    struct date_struct date;
    unsigned int junk_for_align;
};

#define	GPS_PARAM_STRUCT						sizeof(struct gps_param_struct)

union gps_status_union
{
    struct
    {
        unsigned rtc_time_avail:1;
        unsigned rtc_updated:1;
        unsigned rtc_timer:1;
        unsigned initialised:1;
        unsigned rx_byte:1;
        unsigned gprmc:1;
        unsigned comp:1;
        unsigned time_out:1;
        unsigned cs_not_ok:1;
        unsigned invalid:1;
        unsigned date_time:1;
        unsigned lat_long:1;
        unsigned to_be_processed:1;
        unsigned date_time_processed:1;
        unsigned lat_long_processed:1;
        unsigned isr_to_cpu:1;
        unsigned data_time_out:1;
        unsigned test_ant:1;
    }bits;
    unsigned long word;
};

struct gps_struct
{
    union gps_status_union status;
    struct gps_param_struct cpu;
    struct gps_param_struct isr;
    unsigned char rx[SIZE_GPS_RMC_MSG];
    unsigned int rtc_timer_count;
    unsigned int rtc_data_timer_count;
    unsigned int pkt_timer_count;
    unsigned int data_timer_count;
    unsigned int led_timer_count;
    unsigned int rx_ptr;
    unsigned char prev_byte;
    unsigned char curr_byte;
    unsigned char time[8];
    unsigned char date[10];
    unsigned char speed[5];
};

#define	GPS_STRUCT								sizeof(struct gps_struct)

union gps_union
{
    struct gps_struct data;
    unsigned long word[GPS_STRUCT/4];
};
extern union gps_union gps_packet;
/************************************************/

class  LGPS: public QObject
{
    Q_OBJECT

public:
    LGPS();
    ~LGPS();

public slots:
    /**
     * API
     * @brief initialiseUSBPort
     * It initialises all the serial USB ports.
     */
    void initialiseUSBPort();
    void disableSimulation();
    void enableSimulation();
    /**
     * @brief simulateFromFile
     * If you need to simulate GPS from file, use this function with
     * GPS text file path as argument.
     */
    void simulateFromFile(QString);
    QString getSIM_CCID();
    QString getSIM_IMSI();
    QString getModuleIMEI();
    QString getLongitude();
    QString getLatitude();
    QString getGPSLibVersion();
    QString getSpeed();
    QString getSignalStrength();

signals:
    void gps_available(qint64,void *);
    void gps_valid_packet_received();

private slots:
    QString latLongToQString(float);
    void process_n_fill_packet();
    void update_gps_buffer(QString);
    void openSerialPort();
    void closeSerialPort();
    void readData();
    void handleError(QSerialPort::SerialPortError);
    void show_message(QString);
    void sendATCommand(QByteArray);
    void readGPS();
    void readResponse();
    void readOutputError(QSerialPort::SerialPortError);
    void gpsSimulation();
    void simIdentity();
    void checkGPSHealth();

private:
    QSerialPort *port_AT, *port_NMEA, *port_MD, *port_PPP;
    QSerialPort *serial;
    QByteArray GPSData;
    bool GPSSimulation;
    QTextStream simulation_in_stream;
    QFile simulation_file;
    QTimer simulation_timer;
    QTimer *checkGPS;        //every two minutes
    QString tempData;
    union gps_union gps_packet;

    QString SIM,SIMCARD,IMEI,SIGSTR;

    bool dataAccessible;
    bool initOK;
};

#endif // LGPS_H
