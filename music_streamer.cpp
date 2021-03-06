﻿#include "music_streamer.h"
#include "ui_music_streamer.h"
#define COMMAND_PORT 4000
#define PLAYLISTS_PORT 4001

extern route_struct current_route_data;
enum{
    regional,
    hindi,
    english
};
bool play_hindi = false;
int repeat_count,ANNOUNCE_LANGUAGE=regional;
music_streamer::music_streamer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::music_streamer)
{
    ui->setupUi(this);
    command_channel  = new QUdpSocket(this);
    playlists_channel    = new QUdpSocket(this);
    command_channel->bind(QHostAddress::Broadcast,COMMAND_PORT);
    playlists_channel->bind(QHostAddress::Broadcast,PLAYLISTS_PORT);
    this->setGeometry(0,0,0,0);
    conn = mpd_connection_new("localhost",6600,1000);
    mpd_timer = new QTimer;
    connect(mpd_timer,SIGNAL(timeout()),this,SLOT(check_mpd_status()));
}

music_streamer::~music_streamer()
{
    delete ui;
    delete mpd_timer ;
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
                coach_count.prepend('0');
                coach_count.prepend("M_");
                coach_count.append("E");
                original_string.replace(voice_delimiters[i],coach_count);
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
                coach_count.prepend('0');
                coach_count.prepend("M_");
                coach_count.append("H");
                original_string.replace(voice_delimiters[i],coach_count);
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

        if(!(status= mpd_run_status(conn)))
            conn = mpd_connection_new("localhost",6600,1000);
        mpd_run_status(conn);
        mpd_run_clear(conn);
        QTextStream stream_eng( &english_playlist_file );
        QTextStream stream_hin( &hindi_playlist_file );
        QTextStream stream_reg( &regional_playlist_file );

        if ( english_playlist_file.open(QIODevice::ReadWrite | QIODevice::Truncate  ) )
        {
            for(int i=0;i<eng_playlist.length();i++)
                stream_eng << eng_playlist.at(i) << endl;
        }
        else
            qDebug() << "Unable To Open File: English";
        if ( hindi_playlist_file.open(QIODevice::ReadWrite | QIODevice::Truncate ) )
        {
            for(int i=0;i<hindi_playlist.length();i++)
                stream_hin << hindi_playlist.at(i) << endl;
        }
        else
            qDebug() << "Unable To Open File: Hindi";
        if ( regional_playlist_file.open(QIODevice::ReadWrite| QIODevice::Truncate  ) )
        {
            for(int i=0;i<reg_playlist.length();i++)
                stream_reg << reg_playlist.at(i) << endl;
        }
        else
            qDebug() << "Unable To Open File: regional";
        repeat_count = 6;
        ANNOUNCE_LANGUAGE = regional; // [TO-DO] get language positioning from Database
        check_mpd_status();
        QSqlQuery Query_to_get_data_for_msg_code("SELECT `msg_time` FROM `tbl_msg` where `msg_code` = '"+func_code+"'");
        Query_to_get_data_for_msg_code.first();
        mpd_timer->start((Query_to_get_data_for_msg_code.value(0).toInt() * 1000));
        qDebug() << "mpd Timer :: " << Query_to_get_data_for_msg_code.value(0).toInt();
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
    }

    switch(ANNOUNCE_LANGUAGE)
    {
    case regional:
        mpd_run_clear(conn);
        mpd_run_load(conn,"regional");
        mpd_run_play(conn);
        send_command_to_player(PLAY);
        Sleeper::msleep(50);
        ANNOUNCE_LANGUAGE = hindi;
        break;
    case hindi:
        mpd_run_clear(conn);
        mpd_run_load(conn,"hindi");
        //   Sleeper::sleep(2);
        mpd_run_play(conn);
        send_command_to_player(PLAY);
        Sleeper::msleep(50);
        ANNOUNCE_LANGUAGE = english;
        break;
    case english:
        mpd_run_clear(conn);
        mpd_run_load(conn,"english");
        // Sleeper::sleep(2);
        mpd_run_play(conn);
        send_command_to_player(PLAY);
        Sleeper::msleep(50);
        ANNOUNCE_LANGUAGE = regional;
        break;
    }

}

void music_streamer::send_command_to_player(int command)
{
    command_data.append(QString::number(command));
    command_channel->writeDatagram(command_data.data(),QHostAddress::Broadcast,4000);
    qDebug() << "COMMAND SENT >->->----:::::::::::::------::::::---->->-> " << command_data;
    command_data.clear();
}


