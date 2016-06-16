#include "public_announcement.h"
#include "ui_public_announcement.h"
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
    /*Music Streamer based on mpdclient API which stream through ICECAST server on LOCALHOST on 6600 port no.
     *
     * */
   // announcement_streamer = new music_streamer(this);
   // connect(ui->start_announcement,SIGNAL(clicked()),announcement_streamer,SLOT(on_play_clicked()));
   // connect(ui->pause_announcement,SIGNAL(clicked()),announcement_streamer,SLOT(on_pause_clicked()));
   // connect(ui->end_announcement,SIGNAL(clicked()),announcement_streamer,SLOT(close_streaming()));
   // connect(ui->start_announcement,SIGNAL(clicked(bool)),announcement_streamer,SLOT(close_streaming()));
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
    if( !(mpd_run_next(announcement_streamer->conn)))
    {
        announcement_streamer->conn = mpd_connection_new("localhost",6600,0);
        mpd_run_next(announcement_streamer->conn);
    }
}
void public_announcement::on_pushButton_2_clicked()
{
    if( !(mpd_run_previous(announcement_streamer->conn)))
    {
        announcement_streamer->conn = mpd_connection_new("localhost",6600,0);
        mpd_run_previous(announcement_streamer->conn);
    }
}
