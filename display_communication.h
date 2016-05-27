#ifndef DISPLAY_COMMUNICATION_H
#define DISPLAY_COMMUNICATION_H

#include <QObject>
#include <QWidget>
#include "header.h"
#include "database.h"
#include <QUdpSocket>
#include <QThread>
#include <QTimer>
#define English "00"
#define Hindi   "01"
#define Telugu  "00"
class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};

class display_communication : public QObject
{
    Q_OBJECT
public:
    explicit display_communication(QObject *parent = 0);
    ~display_communication();
    database *emu_database;

signals:

public slots:
    void send_train_route_info();
    QByteArray generate_crc(unsigned char * buffer,unsigned int buffer_length);
    void device_reset();
    void send_display_event_messages(unsigned char func_code);
    void form_packet_for_transmission(QString dest_id, unsigned char function_code,const char *packet_data, unsigned int data_length);
private:
    QUdpSocket *server;
    QByteArray data;

};

#endif // DISPLAY_COMMUNICATION_H
