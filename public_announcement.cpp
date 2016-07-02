#include "public_announcement.h"
#include "ui_public_announcement.h"
#define COMMAND_PORT 4000
bool idle_mode = false;
void public_announcement::paintEvent(QPaintEvent* /*event*/)
{
    QColor backgroundColor ;
    backgroundColor.setRgb(173, 216, 230);
    backgroundColor.setAlpha(180);
    QPainter customPainter(this);
    customPainter.fillRect(rect(),backgroundColor);
}

bool public_announcement::eventFilter(QObject *watched, QEvent *event)
{
    if ( event->type() == QEvent::MouseButtonPress )
    {
        emit back_clicked();
        qDebug() << "back button clicked";
    }
    return QObject::eventFilter(watched, event);
}
public_announcement::public_announcement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::public_announcement)
{
    ui->setupUi(this);
    gstreamer = new QProcess(this);
    command_channel = new QUdpSocket(this);
    command_channel->bind(QHostAddress::Broadcast,COMMAND_PORT);
    /*Music Streamer based on mpdclient API which stream through ICECAST server on LOCALHOST on 6600 port no.
     *
   //  * */

    this->installEventFilter(this);
    qDebug() << "Event filter installed";
}

public_announcement::~public_announcement()
{
    delete ui;
    // delete announcement_streamer;
}



void public_announcement::on_pushButton_clicked()
{

}

void public_announcement::start_gstreamer()
{
    QByteArray command_data ;
    command_data.append(QString::number(GSTREAMER_START));
    command_channel->writeDatagram(command_data.data(),QHostAddress::Broadcast,4000);
    gstreamer->start("/usr/bin/gst-launch-1.0 alsasrc ! audioconvert ! audio/x-raw,channels=1,depth=16,width=16,rate=44100 ! rtpL16pay  ! udpsink host=224.0.0.1 port=5555");

}
void public_announcement::on_pushButton_2_clicked()
{

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
