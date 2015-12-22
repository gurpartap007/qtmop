#include "mpd.h"
#include "ui_mpd.h"
#include "header.h"

mpd_connection *conn,*conn1;
mpd::mpd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mpd)
{
    ui->setupUi(this);
    QString mpd_music_path;
    mpd_music_path = "/var/lib/mpd/music";
    mpd_pair *pair1;
    song = NULL;
    conn = mpd_connection_new("localhost",6600,1000);
    conn1=conn;
    if ( mpd_connection_get_error(conn) != MPD_ERROR_SUCCESS )
    {
        mpd_connection_clear_error(conn);
        if (conn != NULL)
        {
            mpd_connection_free(conn);
            conn = NULL;
        }
    }
    mpd_send_allowed_commands(conn);
    while( ( pair1 = mpd_recv_command_pair(conn))!= NULL)
    {
        command = (char *)pair1->value;
        mpd_return_pair(conn, pair1);
        qDebug() << command;
    }
    qDebug() <<  mpd_response_finish(conn);
    /////////////////////////////////////////////   MUSIC PATH  //////////////////////////////////////////////////
    if (!mpd_music_path.isEmpty())
    {
        if (!mpd_music_path.endsWith("/"))
            mpd_music_path.append("/");

        QDir dir(mpd_music_path);
        if (!dir.exists())
        {
            qDebug() << "MPD's music dir : does not exist\n";

        }
        else
            if (!dir.isReadable())
            {
                qDebug() << "MPD's music dir : appears to be read-only\n";
            }
            else
            {
                qDebug() << "MPD's music dir : appears to be accessible\n";
            }
    }

    ////////////////////////////////  mpd status and song info /////////////////////////////////////////////////
    status= mpd_run_status(conn);
    if (status == NULL)
        qDebug()  << "status is NULL";
    else
    {
        qDebug()  <<  "volume" << mpd_status_get_volume(status);
        qDebug()  <<  "repeat" << mpd_status_get_repeat(status);
        qDebug()  <<  "queue version" << mpd_status_get_queue_version(status);
        qDebug()  <<  "queue length" << mpd_status_get_queue_length(status);
        if (mpd_status_get_state(status) == MPD_STATE_PLAY ||
                mpd_status_get_state(status) == MPD_STATE_PAUSE) {
            qDebug()  << "song position " << mpd_status_get_song_pos(status);
            qDebug()  <<  "elapsed time " << mpd_status_get_elapsed_time(status);
            qDebug()  <<  "elapsed ms " << mpd_status_get_elapsed_ms(status);
            qDebug()  <<  "total song time " <<  mpd_status_get_total_time(status);
            qDebug()  <<  "Bit Rate" << mpd_status_get_kbit_rate(status);
        }
        audio_format = mpd_status_get_audio_format(status);
        if (audio_format != NULL) {
            qDebug()  <<  "audio sample rate " <<  audio_format->sample_rate;
            qDebug()  <<  "bits " << audio_format->bits;
            qDebug()  <<  "audio channels " << audio_format->channels;
        }
    }

}

mpd::~mpd()
{
    delete ui;
    mpd_connection_free(conn);
}

void mpd::on_next_clicked()
{
    qDebug() <<  mpd_run_next(conn);
    qDebug() <<   mpd_response_finish(conn);
}
void mpd::on_prev_clicked()
{
    qDebug() <<  mpd_run_previous(conn);
    qDebug() <<   mpd_response_finish(conn);
}

void mpd::on_play_clicked()
{
    qDebug() <<  mpd_run_play (conn);
    qDebug() <<   mpd_response_finish(conn);
}

void mpd::on_pause_clicked()
{
    qDebug() <<  mpd_run_pause( conn,true);
    qDebug() <<   mpd_response_finish(conn);
}

void mpd::on_song_info_clicked()
{
    song = mpd_run_current_song(conn);
    qDebug() << mpd_response_finish(conn);

    if (song != NULL)
    {
       ui->textEdit->clear();
        const char *value;
         QString artist,
                       title,
                       album,
                       date;
        value = mpd_song_get_tag(song,MPD_TAG_ARTIST,0);
        qDebug()  <<  "artist: " << value ;
        artist=QString::fromUtf8(value);
        ui->textEdit->append(artist);

        value = mpd_song_get_tag(song,MPD_TAG_TITLE ,0);
        qDebug()  <<  "Title: " << value ;
        title=QString::fromUtf8(value);
        ui->textEdit->append(title);
        value = mpd_song_get_tag(song,MPD_TAG_ALBUM ,0);
        qDebug()  <<  "Album: " << value ;
         album=QString::fromUtf8(value);
        ui->textEdit->append(album);
        value = mpd_song_get_tag(song,MPD_TAG_DATE ,0);
        qDebug()  <<  "Date: " << value ;
         date=QString::fromUtf8(value);
        ui->textEdit->append(date);


    }



}
