#include "public_announcement.h"
#include "ui_public_announcement.h"
void public_announcement::paintEvent(QPaintEvent* /*event*/)
{
    QColor backgroundColor = palette().light().color();
    backgroundColor.setAlpha(150);
    QPainter customPainter(this);
    customPainter.fillRect(rect(),backgroundColor);
}
public_announcement::public_announcement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::public_announcement)
{
    ui->setupUi(this);
    /*Music Streamer based on mpdclient API which stream through ICECAST server on LOCALHOST on 6600 port no.
     *
     * */
    announcement_streamer = new music_streamer(this );
}

public_announcement::~public_announcement()
{
    delete ui;
    delete announcement_streamer;
}

void public_announcement::on_announcement_back_button_clicked()
{
emit back_clicked();
}
