#include "display_communication.h"
extern route_struct current_route_data;
display_communication::display_communication(QObject *parent) : QObject(parent)
{
    server = new QUdpSocket(this);
    server->bind(QHostAddress("192.168.0.30"),5000);
}

display_communication::~display_communication()
{

}

void display_communication::send_train_route_info()
{
    QByteArray data;
    data.clear();
    data.append((const char *)current_route_data.train.train_num);
     data.append('\0');
    data.append(',');
    data.append(QString::fromUtf8((const char *)current_route_data.train.src.name.eng));
     data.append('\0');
    data.append(',');
    data.append(QString::fromUtf8((const char *)current_route_data.train.mid.name.eng));
     data.append('\0');
    data.append(',');
    data.append(QString::fromUtf8((const char *)current_route_data.train.des.name.eng));
     data.append('\0');
    data.append(',');
    qDebug() << QString::fromUtf8((const char *)current_route_data.train.current_station.name.eng);
    data.append(QString::fromUtf8((const char *)current_route_data.train.current_station.name.eng));
    data.append('\0');
    data.append(',');
    server->writeDatagram(data,data.size(),QHostAddress("192.168.0.7"),5001);
}

