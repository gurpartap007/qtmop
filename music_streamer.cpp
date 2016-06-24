    #include "music_streamer.h"
#include "ui_music_streamer.h"
#define COMMAND_PORT 4000
#define PLAYLISTS_PORT 4001

extern route_struct current_route_data;
enum{
    regional,
    hindi,
    english
};
enum
{
    CLEAR,
    PLAY,
    LOAD_HINDI,
    LOAD_ENGLISH,
    LOAD_REGIONAL,
    PLAYLIST_ENGLISH,
    PLAYLIST_HINDI,
    PLAYLIST_REGIONAL
};
bool play_hindi = false;
int repeat_count,ANNOUNCE_LANGUAGE=regional;
music_streamer::music_streamer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::music_streamer)
{
    ui->setupUi(this);
    command_channel = new QUdpSocket(this);
    playlists_channel = new QUdpSocket(this);
    command_channel->bind(QHostAddress::Broadcast,COMMAND_PORT);
    playlists_channel->bind(QHostAddress::Broadcast,PLAYLISTS_PORT);
    ui->next->hide();
    ui->prev->hide();
    ui->pause->hide();
    ui->playlist->hide();
    ui->textEdit->hide();
    this->setGeometry(0,0,0,0);
    /* New Sql database which hold the all details about Routes,Devices,Events and announcements.
     * * */
    // bus_database = new database;
    /* New process will be created and "/usr/bin/mp3-decoder" will run in new process
     */

    player = new QProcess();
    // player->setProcessChannelMode(QProcess::MergedChannels);
    //////////////////// Setting player_timer to delay mplayer start  ////////////////////////

    player_timer = new QTimer;
    player_timer->setInterval(1000);
    mpd_timer = new QTimer;
    player_started = false;
    connect(player_timer,SIGNAL(timeout()),this,SLOT(mplayer_start()));
    connect(mpd_timer,SIGNAL(timeout()),this,SLOT(check_mpd_status()));
    /////////////////// player_timer start ////////////////////

    mpd_music_path = "/var/lib/mpd/music";
    song = NULL;
//    conn = mpd_connection_new("localhost",6600,0);
 //   mpd_connection_set_timeout(conn,120000);
/*    if ( mpd_connection_get_error(conn) != MPD_ERROR_SUCCESS )
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


    /***********************************************************************************************************/
  /*  status= mpd_run_status(conn);
    if (status == NULL)
        qDebug() << "Status is NULL";

    else
    {
        qDebug()  <<  "volume" << mpd_status_get_volume(status);
        qDebug()  <<  "repeat" << mpd_status_get_repeat(status);
        qDebug()  <<  "queue version" << mpd_status_get_queue_version(status);
        qDebug()  <<  "queue length" << mpd_status_get_queue_length(status);
        if (mpd_status_get_state(status) == MPD_STATE_PLAY ||
                mpd_status_get_state(status) == MPD_STATE_PAUSE) {
            qDebug()  <<  "song position " << mpd_status_get_song_pos(status);
            qDebug()  <<  "elapsed time " << mpd_status_get_elapsed_time(status);
            qDebug()  <<  "elapsed ms " << mpd_status_get_elapsed_ms(status);
            qDebug()  <<  "total song time " <<  mpd_status_get_total_time(status);
            qDebug()  <<  "Bit Rate" << mpd_status_get_kbit_rate(status);
        }
        audio_format = mpd_status_get_audio_format(status);
        if (audio_format != NULL) {

            qDebug()  <<  "audio sample rate" <<  audio_format->sample_rate;
            qDebug()  <<  "bits" << audio_format->bits;
            qDebug()  <<  "audio channels" << audio_format->channels;
            qDebug()  <<  "audio bit rate" << audio_format->sample_rate;
            qDebug()  <<  "audio format type" << audio_format->reserved0;
        }
    }*/
}

music_streamer::~music_streamer()
{
    delete ui;
    delete player_timer;
 /*   mpd_run_rm(conn,"english");
    mpd_run_rm(conn,"hindi");
    mpd_connection_free(conn);*/
    system("pkill -9 mplayer");
}

QStringList  music_streamer::replace_voice_delimiters_eng(QString original_string)
{
    QStringList voice_delimiters,split_words,appended_list;
    int i;
    voice_delimiters << "TTE" << "CCE" << "SSTN" << "DSTN" << "NSTN" << "STRLSE" ;
    for(i=0;i<voice_delimiters.length();i++)
    {
        if(original_string.contains(voice_delimiters[i]))
        {
            switch(i)
            {
            case 0:
            {
                if(current_route_data.train.slow_fast == 'F')
                    original_string.replace(voice_delimiters[i],"M_STRTFE");
                else
                    original_string.replace(voice_delimiters[i],"M_STRTSE");
            }
                break;

            case 1:
            {
                QString coach_count;
                coach_count = QString::number(current_route_data.train.coach_count);
                coach_count.prepend("M_");
                coach_count.append("E");
                original_string.replace(voice_delimiters[i],coach_count);
          //      qDebug() << coach_count;
                break;
            }
            case 2:
            {
                QString src_stn_code;
                src_stn_code = QString::fromLatin1((const char *)current_route_data.train.src_stn_code);
                src_stn_code.prepend("S_");
                original_string.replace(voice_delimiters[i],src_stn_code);
                break;
            }
            case 3:
            {
                QString des_stn_code;
                des_stn_code = QString::fromLatin1((const char *)current_route_data.train.des_stn_code);
                des_stn_code.prepend("S_");
                original_string.replace(voice_delimiters[i],des_stn_code);
                break;
            }
            case 4:
            {
                QString next_stn_code;
                next_stn_code = QString::fromLatin1((const char *)current_route_data.stn[current_route_data.status.next_halting_stn].stn_code);
                next_stn_code.prepend("S_");
                original_string.replace(voice_delimiters[i],next_stn_code);

                break;
            }
            case 5:
            {
                if(current_route_data.train.ladies_special == 'Y')
                    original_string.replace(voice_delimiters[i],"M_STRLSE");
                else
                    original_string.replace(voice_delimiters[i],"");
                break;
            }
            }
        }
    }
    QString mp3(".mp3") ;
    QString temp;
    split_words = original_string.split(',');
    for(i=0;i<split_words.length();i++)
    {
        if(split_words.at(i) == "")
            continue;
        temp = split_words.at(i);
        temp.append(mp3);
        appended_list.append(temp) ;
    }
    return appended_list;
}

QStringList  music_streamer::replace_voice_delimiters_hindi(QString original_string)
{

    QStringList voice_delimiters,split_words,appended_list;
    int i;
    voice_delimiters << "TTH" << "CCH" << "SSTN" << "DSTN" << "NSTN" << "STRLSH" ;
    for(i=0;i<voice_delimiters.length();i++)
    {
        if(original_string.contains(voice_delimiters[i]))
        {
            switch(i)
            {
            case 0:
            {
                if(current_route_data.train.slow_fast == 'F')
                    original_string.replace(voice_delimiters[i],"M_STRTFH");
                else
                    original_string.replace(voice_delimiters[i],"M_STRTSH");
            }
                break;

            case 1:
            {
                QString coach_count;
                coach_count = QString::number(current_route_data.train.coach_count);
                coach_count.prepend("M_");
                coach_count.append("H");
                original_string.replace(voice_delimiters[i],coach_count);
      //          qDebug() << coach_count;
                break;
            }
            case 2:
            {
                QString src_stn_code;
                src_stn_code = QString::fromLatin1((const char *)current_route_data.train.src_stn_code);
                src_stn_code.prepend("S_");
                original_string.replace(voice_delimiters[i],src_stn_code);
                break;
            }
            case 3:
            {
                QString des_stn_code;
                des_stn_code = QString::fromLatin1((const char *)current_route_data.train.des_stn_code);
                des_stn_code.prepend("S_");
                original_string.replace(voice_delimiters[i],des_stn_code);
                break;
            }
            case 4:
            {
                QString next_stn_code;
                next_stn_code = QString::fromLatin1((const char *)current_route_data.stn[current_route_data.status.next_halting_stn].stn_code);
                next_stn_code.prepend("S_");
                original_string.replace(voice_delimiters[i],next_stn_code);

                break;
            }
            case 5:
            {
                if(current_route_data.train.ladies_special == 'Y')
                    original_string.replace(voice_delimiters[i],"M_STRLSH");
                else
                    original_string.replace(voice_delimiters[i],"");
                break;
            }
            }
        }
    }
    QString mp3(".mp3") ;
    QString temp;
    split_words = original_string.split(',');
    for(i=0;i<split_words.length();i++)
    {
        if(split_words.at(i) == "")
            continue;
        temp = split_words.at(i);
        temp.append(mp3);
        appended_list.append(temp) ;
    }
    return appended_list;
}

QStringList  music_streamer::replace_voice_delimiters_reg(QString original_string)
{

    QStringList voice_delimiters,split_words,appended_list;
    int i;
    voice_delimiters << "TTR" << "CCR" << "SSTN" << "DSTN" << "NSTN" << "STRLSR" ;
    for(i=0;i<voice_delimiters.length();i++)
    {
        if(original_string.contains(voice_delimiters[i]))
        {
            switch(i)
            {
            case 0:
            {
                if(current_route_data.train.slow_fast == 'F')
                    original_string.replace(voice_delimiters[i],"M_STRTFR");
                else
                    original_string.replace(voice_delimiters[i],"M_STRTSR");
            }
                break;

            case 1:
            {
                QString coach_count;
                coach_count = QString::number(current_route_data.train.coach_count);
                coach_count.prepend("M_");
                coach_count.append("R");
                original_string.replace(voice_delimiters[i],coach_count);
    //            qDebug() << coach_count;
                break;
            }
            case 2:
            {
                QString src_stn_code;
                src_stn_code = QString::fromLatin1((const char *)current_route_data.train.src_stn_code);
                src_stn_code.prepend("S_");
                original_string.replace(voice_delimiters[i],src_stn_code);
                break;
            }
            case 3:
            {
                QString des_stn_code;
                des_stn_code = QString::fromLatin1((const char *)current_route_data.train.des_stn_code);
                des_stn_code.prepend("S_");
                original_string.replace(voice_delimiters[i],des_stn_code);
                break;
            }
            case 4:
            {
                QString next_stn_code;
                next_stn_code = QString::fromLatin1((const char *)current_route_data.stn[current_route_data.status.next_halting_stn].stn_code);
                next_stn_code.prepend("S_");
                original_string.replace(voice_delimiters[i],next_stn_code);

                break;
            }
            case 5:
            {
                if(current_route_data.train.ladies_special == 'Y')
                    original_string.replace(voice_delimiters[i],"M_STRLSR");
                else
                    original_string.replace(voice_delimiters[i],"");
                break;
            }
            }
        }
    }
    QString mp3(".mp3") ;
    QString temp;
    split_words = original_string.split(',');
    for(i=0;i<split_words.length();i++)
    {
        if(split_words.at(i) == "")
            continue;
        temp = split_words.at(i);
        temp.append(mp3);
        appended_list.append(temp) ;
    }
    return appended_list;
}
void music_streamer::on_next_clicked()
{



}

void music_streamer::mplayer_start()
{
    /*   QString program("/usr/bin/mp3-decoder");
    QStringList arguments;
    arguments << "http://127.0.0.1:8000/mpd.mp3 ";
    arguments << "&";
    player_timer->stop();
    // player->start(program,arguments);
    // player->start("/usr/bin/mp3-decoder http://127.0.0.1:8000/mpd.mp3 & ");
    system("/usr/bin/mplayer http://127.0.0.1:8000/mpd.mp3 & ");
    qDebug() << "PLayer Started";
*/
}

void music_streamer::on_prev_clicked()
{

}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><

void music_streamer::on_play_clicked()
{

}


void music_streamer::on_pause_clicked()
{
//    qDebug() << "Pause: " <<  mpd_run_pause(conn,true);
}

void music_streamer::on_playlist_clicked()
{

}

void music_streamer::close_streaming()
{

}

void music_streamer::create_announcement_playlist(QString func_code)
{
    QString filename_english="/var/lib/mpd/playlists/english.m3u";
    QFile english_playlist_file( filename_english );
    QString filename_hindi="/var/lib/mpd/playlists/hindi.m3u";
    QFile hindi_playlist_file( filename_hindi);
    QString filename_regional="/var/lib/mpd/playlists/regional.m3u";
    QFile regional_playlist_file( filename_regional );
    QString english_string,hindi_string,reg_string;
    QString Query_to_get_data_for_msg_code = "SELECT * FROM `tbl_aau` where `msg_code` = '";
    Query_to_get_data_for_msg_code += func_code;
    Query_to_get_data_for_msg_code += "' and msg_instance = '1'";
    QSqlQuery get_voice_strings(Query_to_get_data_for_msg_code);
    get_voice_strings.next();
    if(get_voice_strings.value(1).toString() == func_code)
    {
        english_string = get_voice_strings.value(2).toString();
        hindi_string   = get_voice_strings.value(3).toString();
        reg_string     = get_voice_strings.value(4).toString();
        eng_playlist   = replace_voice_delimiters_eng(english_string);
        hindi_playlist = replace_voice_delimiters_hindi(hindi_string);
        reg_playlist   = replace_voice_delimiters_reg(reg_string);

        //  if(!(status= mpd_run_status(conn)))
        //    conn = mpd_connection_new("localhost",6600,1000);
        // mpd_run_clear(conn);
        send_playlists_to_player();
       //Sleeper::sleep(1);
        send_command_to_player(CLEAR);
/*
        QTextStream stream_eng( &english_playlist_file );
        QTextStream stream_hin( &hindi_playlist_file );
        QTextStream stream_reg( &regional_playlist_file );

        if ( english_playlist_file.open(QIODevice::ReadWrite | QIODevice::Truncate  ) )
        {
            for(int i=0;i<eng_playlist.length();i++)
                stream_eng << eng_playlist.at(i) << endl;
        }
        if ( hindi_playlist_file.open(QIODevice::ReadWrite | QIODevice::Truncate ) )
        {
            for(int i=0;i<hindi_playlist.length();i++)
                stream_hin << hindi_playlist.at(i) << endl;
        }
        if ( regional_playlist_file.open(QIODevice::ReadWrite| QIODevice::Truncate  ) )
        {
            for(int i=0;i<reg_playlist.length();i++)
                stream_reg << reg_playlist.at(i) << endl;
        }*/
        //     mpd_run_load(conn,"hindi");
     //   send_command_to_player(LOAD_REGIONAL);
        repeat_count = 6;
        // mpd_run_load(conn,"hindi");
        // mpd_run_load(conn,"regional");
        player_timer->start();
        play_hindi = false;
        player_started = true;
        mpd_timer->stop();
        ANNOUNCE_LANGUAGE = regional;

        check_mpd_status();

        //   mpd_run_play(conn);
       // Sleeper::sleep(2);
      //  send_command_to_player(PLAY);
        QSqlQuery Query_to_get_data_for_msg_code("SELECT `msg_time` FROM `tbl_msg` where `msg_code` = '"+func_code+"'");
        Query_to_get_data_for_msg_code.first();
        mpd_timer->start((Query_to_get_data_for_msg_code.value(0).toInt()) * 1000);
        // mpd_timer->start(70 * 1000);
 //       qDebug() << "MPD Timer timeout" <<  Query_to_get_data_for_msg_code.value(0).toString();
        // mpd_run_repeat(conn,false);


    }
    else
        return ;
}

void music_streamer::check_mpd_status()
{
     repeat_count --;
    if(repeat_count == 0)
    {
        mpd_timer->stop();
        repeat_count = 0;
        //play_hindi = false;
    }

switch(ANNOUNCE_LANGUAGE)
{
case regional:
    send_command_to_player(CLEAR);
     send_command_to_player(LOAD_REGIONAL);
     //if(repeat_count == 5)
       //  Sleeper::sleep(3)
     //Sleeper::sleep(1);
   //  send_command_to_player(PLAY);
     ANNOUNCE_LANGUAGE = hindi;
    break;
case hindi:
    send_command_to_player(CLEAR);
    send_command_to_player(LOAD_HINDI);
   // Sleeper::sleep(1);
 //   send_command_to_player(PLAY);
    ANNOUNCE_LANGUAGE = english;
    break;
case english:
    send_command_to_player(CLEAR);
    send_command_to_player(LOAD_ENGLISH);
  //  Sleeper::sleep(1);
  //  send_command_to_player(PLAY);
    ANNOUNCE_LANGUAGE = regional;
    break;

}
  /*  QString command("mpd_run_clear(conn);");
    // if(!(status= mpd_run_status(conn)))
    //   conn = mpd_connection_new("localhost",6600,1000);
    //     status= mpd_run_status(conn);

    /*   if (mpd_status_get_state(status) == MPD_STATE_PLAY)
        qDebug() << "MPD is currently playing ";
    else if (mpd_status_get_state(status) == MPD_STATE_STOP)
    {*/
   /* if(!play_hindi)
    {
        -- repeat_count;
        qDebug() << "MPD is currently halted";
        //       mpd_run_clear(conn);
        send_command_to_player(CLEAR);
        player_timer->start();
        //     mpd_run_load(conn,"english");
        send_command_to_player(LOAD_HINDI);
        //   mpd_run_play(conn);
        send_command_to_player(PLAY);
        play_hindi = true;
        if(repeat_count == 0)
        {
            mpd_timer->stop();
            repeat_count = 0;
            play_hindi = false;
        }
    }
    else
    {

        play_hindi = false;
        qDebug() << "MPD is currently halted";
        //   mpd_run_clear(conn);
        send_command_to_player(CLEAR);
        player_timer->start();
        //   mpd_run_load(conn,"hindi");
        send_command_to_player(LOAD_ENGLISH);
        //   mpd_run_play(conn);
        send_command_to_player(PLAY);


    }*/

    // }
}

void music_streamer::send_command_to_player(int command)
{
    command_data.append(QString::number(command));
 //   command_channel->writeDatagram(command_data.data(),QHostAddress::Broadcast,4000);
    qDebug() << "COMMAND SENT ::::  " << command_data;

    command_data.clear();
}

void music_streamer::send_playlists_to_player()
{
    playlists_data.clear();
//qDebug() << "ENGLISSSH " << eng_playlist;
        for(int i=0;i<eng_playlist.length();i++)
        {
            playlists_data.append(eng_playlist.at(i));
            playlists_data.append(',');
        }
            playlists_data.append("ETX");
            playlists_data.append(',');

        for(int i=0;i<hindi_playlist.length();i++)
        {
            playlists_data.append(hindi_playlist.at(i));
            playlists_data.append(',');
        }
        playlists_data.append("ETX");

        for(int i=0;i<reg_playlist.length();i++)
        {
            playlists_data.append(',');
            playlists_data.append(reg_playlist.at(i));
        }
         playlists_data.append(',');
         playlists_data.append("ETX");
        playlists_channel->writeDatagram(playlists_data.data(),QHostAddress::Broadcast,4001);
}
