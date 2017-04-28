#include "public_announcement.h"
#define COMMAND_PORT 4000
bool idle_mode = false;

public_announcement::public_announcement(QWidget *parent) :
    QWidget(parent)
{
    gstreamer = new QProcess(this);
    command_channel = new QUdpSocket(this);
    command_channel->bind(QHostAddress::Broadcast,COMMAND_PORT);
}

public_announcement::~public_announcement()
{

}

void public_announcement::start_gstreamer()
{
    QByteArray command_data ;
    command_data.append(QString::number(GSTREAMER_START));
    command_channel->writeDatagram(command_data.data(),QHostAddress::Broadcast,4000);
    gstreamer->start("/usr/bin/gst-launch-1.0 alsasrc ! audioconvert ! audio/x-raw,channels=1,depth=16,width=16,rate=44100 ! rtpL16pay  ! udpsink host=224.0.0.1 port=5555");

}

void public_announcement::on_start_announcement_clicked()
{
    start_gstreamer();
}

void public_announcement::on_end_announcement_clicked()
{
    QByteArray command_data ;
    command_data.append(QString::number(GSTREAMER_STOP));
    command_channel->writeDatagram(command_data.data(),QHostAddress::Broadcast,4000);
    gstreamer->kill();
}
