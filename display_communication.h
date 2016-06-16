#ifndef DISPLAY_COMMUNICATION_H
#define DISPLAY_COMMUNICATION_H

#include <QObject>
#include <QWidget>
#include "header.h"
#include "music_streamer.h"
#include "database.h"
#include <QUdpSocket>
#include <QTcpSocket>
#include <QThread>
#include <QSerialPort>
#include <QTimer>
#define English "00"
#define Hindi   "01"
#define Telugu  "00"
/*class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};*/

class display_communication : public QObject
{
    Q_OBJECT
public:
    explicit display_communication(QObject *parent = 0);
    ~display_communication();
     void device_reset();
     void open_serialport();
    database *emu_database;
    music_streamer *announcements_streamer;
    QTimer *hcd_timer;
    QSerialPort *port;

signals:
 void create_playlist(QString msg_code);
public slots:
    void send_train_route_info(QString);
    QByteArray generate_crc(unsigned char * buffer,unsigned int buffer_length);
    QString replace_eng_delimiters(QString *eng_message);
    QString replace_hindi_delimiters(QString *hindi_message);
    QString replace_regional_delimiters(QString *regional_message);
    void send_display_event_messages(QString func_code);
    void send_headcode_frame();
    void start_player();
    void form_packet_for_transmission(QString dest_id, QString function_code,const char *packet_data, unsigned int data_length);
private:
    QUdpSocket *server;
    //QTcpSocket *server;

    QByteArray data;

};

#endif // DISPLAY_COMMUNICATION_H
