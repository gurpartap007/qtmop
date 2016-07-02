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
}

music_streamer::~music_streamer()
{
    delete ui;
    delete player_timer;
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
        send_playlists_to_player();
        send_command_to_player(CLEAR);
        repeat_count = 6;
        player_timer->start();
        play_hindi = false;
        player_started = true;
        mpd_timer->stop();
        ANNOUNCE_LANGUAGE = regional;
        check_mpd_status();
        QSqlQuery Query_to_get_data_for_msg_code("SELECT `msg_time` FROM `tbl_msg` where `msg_code` = '"+func_code+"'");
        Query_to_get_data_for_msg_code.first();
        mpd_timer->start((Query_to_get_data_for_msg_code.value(0).toInt()) * 1000);
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
    send_command_to_player(CLEAR);
     send_command_to_player(LOAD_REGIONAL);
     ANNOUNCE_LANGUAGE = hindi;
    break;
case hindi:
    send_command_to_player(CLEAR);
    send_command_to_player(LOAD_HINDI);
    ANNOUNCE_LANGUAGE = english;
    break;
case english:
    send_command_to_player(CLEAR);
    send_command_to_player(LOAD_ENGLISH);
    ANNOUNCE_LANGUAGE = regional;
    break;
}
}

void music_streamer::send_command_to_player(int command)
{
    command_data.append(QString::number(command));
    qDebug() << "COMMAND SENT ::::  " << command_data;
    command_data.clear();
}

void music_streamer::send_playlists_to_player()
{
    playlists_data.clear();
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
