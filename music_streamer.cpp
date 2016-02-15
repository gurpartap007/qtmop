#include "music_streamer.h"
#include "ui_music_streamer.h"

music_streamer::music_streamer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::music_streamer)
{
    ui->setupUi(this);
    ui->next->hide();
    ui->prev->hide();
    ui->play->hide();
    ui->pause->hide();
    ui->playlist->hide();
    ui->textEdit->hide();
    this->setGeometry(0,0,0,0);
    /* New Sql database which hold the all details about Routes,Devices,Events and announcements.
     * * */
    // bus_database = new database;
    /* New process will be created and "/usr/bin/mp3-decoder" will run in new process
     *
     * */
    player = new QProcess(this);
    player->setProcessChannelMode(QProcess::MergedChannels);
    //////////////////// Setting player_timer to delay mplayer start  ////////////////////////
    player_timer = new QTimer;
    player_timer->setInterval(2000);
    player_started = false;
    connect(player_timer,SIGNAL(timeout()),this,SLOT(mplayer_start()));
    /////////////////// player_timer start ////////////////////

    mpd_music_path = "/var/lib/mpd/music";
    song = NULL;
    conn = mpd_connection_new("localhost",6600,1000);
    if ( mpd_connection_get_error(conn) != MPD_ERROR_SUCCESS )
    {
        mpd_connection_clear_error(conn);
        if (conn != NULL)
        {
            mpd_connection_free(conn);
            conn = NULL;
        }
    }

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

music_streamer::~music_streamer()
{
    delete ui;
    delete player_timer;
    //player->deleteLater();
    // system("pkill -9 mp3-decoder");
    qDebug() << "Destructor Called";
    mpd_connection_free(conn);
}
void music_streamer::on_next_clicked()
{
    qDebug() << "Next: " <<  mpd_run_next(conn);
    mpd_response_finish(conn);
    song = mpd_run_current_song(conn);
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

void music_streamer::mplayer_start()
{
    //mpd_run_play(conn);
    QString program("/usr/bin/mp3-decoder");
    QStringList arguments;
    arguments << "http://127.0.0.1:8000/mpd.mp3";
    arguments << "&";
    player_timer->stop();
    player->start(program,arguments);
    qDebug() << "player Id:" << player->processId();

}
void music_streamer::on_prev_clicked()
{
    qDebug() << "Previous: " <<  mpd_run_previous(conn);
    mpd_response_finish(conn);
    song = mpd_run_current_song(conn);
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

void music_streamer::on_play_clicked()
{
    qDebug()<< "Play: " <<  mpd_run_play (conn);
    // mpd_run_play_pos(conn,2);
    mpd_response_finish(conn);
    if(!player_started)
    {
        player_timer->start();
        player_started = true;
    }
}

void music_streamer::on_pause_clicked()
{
    qDebug() << "Pause: " <<  mpd_run_pause(conn,true);
    mpd_response_finish(conn);
}



void music_streamer::on_playlist_clicked()
{
    ui->textEdit->clear();
}

void music_streamer::close_streaming()
{
    mpd_run_stop(conn);
    player->kill();
    player_started=false;
}
