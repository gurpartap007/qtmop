#ifndef DISPLAY_COMMUNICATION_H
#define DISPLAY_COMMUNICATION_H

#include <QObject>
#include <QWidget>
#include "header.h"

class display_communication : public QObject
{
    Q_OBJECT
public:
    explicit display_communication(QObject *parent = 0);
    ~display_communication();

signals:

public slots:
    void send_train_route_info();
private:
    QUdpSocket *server;
};

#endif // DISPLAY_COMMUNICATION_H
