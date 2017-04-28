#include "running_route.h"

qint64 msg_index = 0,safety_msg_index=0;
uinteger track_dist_bn_stns[MAX_STNS_PER_BUS];
sinteger mul_factor[MAX_STNS_PER_BUS];
QTimer device_update_timer;
int manual_msg_id,manual_msg_index,manual_total_index;
QSqlRecord manual_record[10];

union msg_status_union
{
  struct msg_status_struct
  {
      unsigned int trigger_on_approaching_periphery:1;
      unsigned int trigger_on_arrival:1;
      unsigned int trigger_on_exit_periphery:1;
      unsigned int trigger_pre_departure:1;
      unsigned int trigger_on_gen_start:1;
      unsigned int trigger_on_departure:1;
      unsigned int trigger_on_journey_end:1;
      unsigned int trigger_manual_alerts:1;
  }bits;
  unsigned int flags;
}msg_status;


running_route::running_route(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::running_route)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::X11BypassWindowManagerHint|Qt::FramelessWindowHint);

    serial = new QSerialPort();
    player = new QMediaPlayer;
    Playlist = new QMediaPlaylist;
    prev_safety_msg_id = 32;
    qDebug("\nSetting running route Interface...\n");
    connect(this,SIGNAL(route_events(qint64,void *)),this,SLOT(message_generator(qint64,void *)));
    memset(gps_packet.word,0,sizeof(gps_packet));
    pixmap = new QPixmap(1000,300);
    pixmap->fill(QColor(Qt::transparent));
    device_update_timer.setSingleShot(true);
    connect(&device_update_timer,SIGNAL(timeout()),this,SLOT(manage_device_updates()));
    connect(serial,SIGNAL(readyRead()),this,SLOT(read_pkt()));
    connect(&Read_timer,SIGNAL(timeout()),this,SLOT(check_pkt()));
    connect(Playlist,SIGNAL(currentIndexChanged(int)),this,SLOT(mediachanged(int)));
    gps_timeout_timer_id = 255;
    display_timer_id = 255;
    route_tasks_timer_id = 255;
    route_path.params.audio = 'D';
    route_path.params.alarm = 'D';

    openSerialPort();
}

void running_route::mediachanged(int index)
{
     if(index == -1)
        player->stop();
}

running_route::~running_route()
{
     delete ui;
}

QStringList running_route::check_n_replace_voice_delim(QString delim,qint64 language)
{
    QStringList langugae_suffix,new_list,num_identifier;
    langugae_suffix<<""<<"_H"<<"_R";
    num_identifier<<"E"<<"H"<<"R";
    qint16 stops;
    new_list.clear();
    QFile file;
    qint64 temp_language;
    if(delim == "TRN")
    {
        file.setFileName("T_"+QString::fromLatin1(route_path.Header.Route)+langugae_suffix[language]);
        if(!file.exists() && language)
            language = 0;
        return(new_list<<"T_"+QString::fromLatin1(route_path.Header.Route)+langugae_suffix[language]);
    }
    else if(delim == "SRC")
    {
        file.setFileName("S_"+QString::fromLatin1(route_path.Header.Source_Stop)+langugae_suffix[language]);
        if(!file.exists() && language)
            language = 0;
        return(new_list<<"S_"+QString::fromLatin1(route_path.Header.Source_Stop)+langugae_suffix[language]);
    }
    else if(delim == "DES")
    {
        file.setFileName("S_"+QString::fromLatin1(route_path.Header.Destination_Stop)+langugae_suffix[language]);
        if(!file.exists() && language)
            language = 0;
        return(new_list<<"S_"+QString::fromLatin1(route_path.Header.Destination_Stop)+langugae_suffix[language]);
    }
    else if(delim == "NSTN")
    {
        file.setFileName("S_"+QString::fromLatin1(route_path.Stops[route_path.Curr_stop].info.Code)+langugae_suffix[language]);
        if(!file.exists() && language)
            language = 0;
        return(new_list<<"S_"+QString::fromLatin1(route_path.Stops[route_path.Curr_stop].info.Code)+langugae_suffix[language]);
    }
    else if(delim == "UPSTNS")
    {
        if((route_path.Curr_stop+5) < route_path.Header.no_of_stns)
            stops = route_path.Curr_stop+5;
        else
            stops = route_path.Header.no_of_stns;
        for(int i = route_path.Curr_stop;i<stops;i++)
        {
            temp_language = language;
            file.setFileName("S_"+QString::fromLatin1(route_path.Header.Destination_Stop)+langugae_suffix[language]);
            if(!file.exists() && temp_language)
                temp_language = 0;
            new_list<<"S_"+QString::fromLatin1(route_path.Stops[i].info.Code)+langugae_suffix[temp_language];
        }
        return(new_list);
    }
    else if(delim == "TNUM")
    {
        for(int j=0;j<strlen(route_path.Header.Route);j++)
            new_list<<"M_"+QString(QChar(route_path.Header.Route[j])).rightJustified(2,'0')+num_identifier[language];
        return(new_list);
    }
    else
    {
        new_list<<delim;
        return(new_list);
    }
}

qint64 running_route::generate_alerts(int msg_id,int msg_index)
{
    union int_union
    {
        struct int_struct
        {
            unsigned char a;
            unsigned char b;
        }data;
        qint16 integer;
    }distance;

    if(manual_total_index <= msg_index)
    {
        device_update_timer.start(10);
        return(0);
    }
    QSqlRecord record = manual_record[msg_index];
    QList<QMediaContent> list;
    QString filename;
    player->stop();
    Playlist->clear();
    slave_tx.data.data.dat.disp_mode_id = record.value(4).toInt();
    slave_tx.data.data.dat.langid = record.value(3).toInt();
    QStringList templist = record.value(6).toString().split(",");
    QStringList templist_1;
    for(int z = 0; z <templist.size();z++)
    {
        templist_1 = check_n_replace_voice_delim(templist[z],slave_tx.data.data.dat.langid);
        for(int j=0;j<templist_1.size();j++)
            list<<QUrl::fromLocalFile(QString("/home/apaul/PIS_VDB/"+templist_1[j]+".mp3"));
        qDebug()<<filename;
    }
    memset(slave_tx.data.data.dat.train_num,' ',6);
    memcpy(slave_tx.data.data.dat.train_num,route_path.Header.Route,strlen(route_path.Header.Route));
    slave_tx.data.data.dat.date = gps_packet.data.cpu.date.day;
    slave_tx.data.data.dat.month = gps_packet.data.cpu.date.month;
    slave_tx.data.data.dat.year = gps_packet.data.cpu.date.yrs;
    slave_tx.data.data.dat.hrs = gps_packet.data.cpu.time.hrs;
    slave_tx.data.data.dat.min = gps_packet.data.cpu.time.min;
    slave_tx.data.data.dat.sec = gps_packet.data.cpu.time.sec;
    slave_tx.data.data.dat.start_time = 1;
    slave_tx.data.data.dat.hold_time = 25;
    slave_tx.data.data.dat.rpt_cnt = 1;
    slave_tx.data.data.dat.brigthness = 100;
    slave_tx.data.fn_code = 0x81;
    if(slave_tx.data.data.dat.langid == 255)
        slave_tx.data.data.dat.langid = route_path.Stops[route_path.Curr_stop].info.regional_lngugage;
    unsigned char *dest_ptr = slave_tx.data.data.dat.bytes;
    ubyte language = 0;
    ubyte stops = 0;
    if(slave_tx.data.data.dat.langid == 255)
        slave_tx.data.data.dat.langid = route_path.Stops[route_path.Curr_stop].info.regional_lngugage;
    if(slave_tx.data.data.dat.langid > 1)
    {
        if(route_path.Stops[route_path.Curr_stop].info.regional_lngugage == route_path.Stops[0].info.regional_lngugage)
            language = 2;
        else if(route_path.Stops[route_path.Curr_stop].info.regional_lngugage == route_path.Stops[route_path.Header.no_of_stns - 1].info.regional_lngugage)
            language = 3;
        else
            language = 4;
    }
    switch(slave_tx.data.data.dat.disp_mode_id)
    {
        case 89:
            slave_tx.data.data.dat.brigthness = 80;
            break;
        case 2:
            if(language < 4)
            {
                *dest_ptr++ = strlen(route_path.Header.Description[language]);
                memcpy((unsigned char *)dest_ptr,(unsigned char *)route_path.Header.Description[language],strlen(route_path.Header.Description[language]));
                dest_ptr += strlen(route_path.Header.Description[language]);
                break;
            }
            break;
        case 3:
            if(language < 4)
            {
                *dest_ptr++ = strlen(route_path.Header.Source_station_name[language]);
                memcpy((unsigned char *)dest_ptr,(unsigned char *)route_path.Header.Source_station_name[language],strlen(route_path.Header.Source_station_name[language]));
                dest_ptr += strlen(route_path.Header.Source_station_name[language]);
                *dest_ptr++ = strlen(route_path.Header.Destination_station_name[language]);
                memcpy((unsigned char *)dest_ptr,(unsigned char *)route_path.Header.Destination_station_name[language],strlen(route_path.Header.Destination_station_name[language]));
                dest_ptr += strlen(route_path.Header.Destination_station_name[language]);
            }
            break;
        case 73:
        case 67:
            *dest_ptr++ = strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]);
            memcpy(dest_ptr,route_path.Stops[route_path.Curr_stop].info.station_name[language],strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]));
            dest_ptr += strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]);
            break;
        case 68:
            *dest_ptr++ = strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]);
            memcpy(dest_ptr,route_path.Stops[route_path.Curr_stop].info.station_name[language],strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]));
            dest_ptr += strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]);
            break;
        case 69:
            distance.integer = (qint16)route_path.Stops[route_path.Curr_stop].info.distance_from_curr_loc;
            *dest_ptr++ = distance.data.b;
            *dest_ptr++ = distance.data.a;
            *dest_ptr++ = strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]);
            memcpy(dest_ptr,route_path.Stops[route_path.Curr_stop].info.station_name[language],strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]));
            dest_ptr += strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]);
            break;
        case 70:
            distance.integer = (qint16)route_path.Stops[route_path.Curr_stop].info.distance_from_curr_loc;
            *dest_ptr++ = distance.data.b;
            *dest_ptr++ = distance.data.a;
            break;
        case 71:
            *dest_ptr++ = route_path.Stops[route_path.Curr_stop].info.arrival_time.hrs;
            *dest_ptr++ = route_path.Stops[route_path.Curr_stop].info.arrival_time.min;
            *dest_ptr++ = route_path.Stops[route_path.Curr_stop].info.arrival_time.hrs;
            *dest_ptr++ = route_path.Stops[route_path.Curr_stop].info.arrival_time.min;
            *dest_ptr++ = route_path.Stops[route_path.Curr_stop].info.arrival_time.hrs;
            *dest_ptr++ = route_path.Stops[route_path.Curr_stop].info.arrival_time.min;
            *dest_ptr++ = strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]);
            memcpy(dest_ptr,route_path.Stops[route_path.Curr_stop].info.station_name[language],strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]));
            dest_ptr += strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]);
            break;
        case 72:
            distance.integer = (qint16)gps_packet.data.cpu.speed;
            *dest_ptr++ = distance.data.b;
            *dest_ptr++ = distance.data.a;
            break;
        case 74:
            distance.integer = (qint16)route_path.Header.distance;
            *dest_ptr++ = distance.data.b;
            *dest_ptr++ = distance.data.a;
            *dest_ptr++ = route_path.Header.time.hrs;
            *dest_ptr++ = route_path.Header.time.min;
            *dest_ptr++ = strlen(route_path.Header.Source_station_name[language]);
            memcpy(dest_ptr,route_path.Header.Source_station_name[language],strlen(route_path.Header.Source_station_name[language]));
            dest_ptr += strlen(route_path.Header.Source_station_name[language]);
            *dest_ptr++ = strlen(route_path.Header.Destination_station_name[language]);
            memcpy(dest_ptr,route_path.Header.Destination_station_name[language],strlen(route_path.Header.Destination_station_name[language]));
            dest_ptr += strlen(route_path.Header.Destination_station_name[language]);
            break;
        case 75:
           *dest_ptr++ = route_path.Header.no_of_stns;
            for(int i=0;i<route_path.Header.no_of_stns-2;i++)
            {
               *dest_ptr++ = strlen(route_path.Stops[i+1].info.station_name[language]);
               memcpy(dest_ptr,route_path.Stops[i+1].info.station_name[language],strlen(route_path.Stops[i+1].info.station_name[language]));
               dest_ptr += strlen(route_path.Stops[i+1].info.station_name[language]);
            }
            break;
        case 76:
            distance.integer = (qint16)(gps_packet.data.cpu.speed/100);
            *dest_ptr++ = distance.data.b;
            *dest_ptr++ = distance.data.a;
            if((route_path.Curr_stop+5) < route_path.Header.no_of_stns)
            {
                *dest_ptr++ = 5;
                stops = route_path.Curr_stop+5;
            }
            else
            {
                *dest_ptr++ = route_path.Header.no_of_stns - route_path.Curr_stop;
                stops = route_path.Header.no_of_stns;
            }
            for(int i = route_path.Curr_stop;i<stops;i++)
            {
                *dest_ptr++ = strlen(route_path.Stops[i].info.station_name[language]);
                memcpy(dest_ptr,route_path.Stops[i].info.station_name[language],strlen(route_path.Stops[i].info.station_name[language]));
                dest_ptr += strlen(route_path.Stops[i].info.station_name[language]);
            }
            break;
        case 77:
            distance.integer = (qint16)route_path.Stops[route_path.Curr_stop].info.distance_from_curr_loc;
            *dest_ptr++ = distance.data.b;
            *dest_ptr++ = distance.data.a;
            *dest_ptr++ = route_path.Stops[route_path.Curr_stop].info.arrival_time.hrs;
            *dest_ptr++ = route_path.Stops[route_path.Curr_stop].info.arrival_time.min;
            *dest_ptr++ = route_path.Stops[route_path.Curr_stop].info.arrival_time.hrs;
            *dest_ptr++ = route_path.Stops[route_path.Curr_stop].info.arrival_time.min;
            *dest_ptr++ = strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]);
            memcpy(dest_ptr,route_path.Stops[route_path.Curr_stop].info.station_name[language],strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]));
            dest_ptr += strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]);
            break;
    }
    *dest_ptr++ = 0;
    *dest_ptr++ = 0;
    slave_tx.data.stx[0] = 0xAA;
    slave_tx.data.stx[1] = 0xCC;
    slave_tx.data.cntrl.src_add = 0x01;
    slave_tx.data.cntrl.dest_add = 0xFF;
    slave_tx.data.cntrl.sr_num = 1;
    slave_tx.data.length = 20 + (dest_ptr - slave_tx.data.data.dat.bytes) + 10 - 4;
    QByteArray crc = crc_o.crc_generate_modbus(&slave_tx.bytes[2],slave_tx.data.length);
    *dest_ptr++ = crc[0];
    *dest_ptr++ = crc[1];
    serial->write((char *)slave_tx.bytes,slave_tx.data.length+4);
    Playlist->addMedia(list);
    Playlist->setPlaybackMode(QMediaPlaylist::Sequential);
    if(!Playlist->isEmpty())
    {
        player->setPlaylist(Playlist);
        player->setVolume(80);
        player->play();
    }
    manual_msg_index++;
    device_update_timer.start(10000);
    return(1);
}

qint64 running_route::rdso0087protocol(QString msg_type,qint64 index)
{
    union int_union
    {
        struct int_struct
        {
            unsigned char a;
            unsigned char b;
        }data;
        qint16 integer;
    }distance;
    QSqlQuery query1(QSqlDatabase::database("Connection1"));
    query1.exec("SELECT *FROM `tbl_msg_frame_list` where `messagetype` = '" + msg_type + "' AND `msg_Index` = '" + QString::number(index) + "'");
    qDebug() << query1.lastQuery();
    if(!query1.next())
    {
        if(msg_type == "S")
            safety_msg_index = 0;
        device_update_timer.start(10);
        return(0);
    }
    QSqlRecord record = query1.record();
    if(msg_type == "S")
    {
        if(record.value(4).toInt() != prev_safety_msg_id)
        {
            device_update_timer.start(10);
            return(0);
        }
        else
        {
            prev_safety_msg_id = record.value(4).toInt();
            safety_msg_index++;
        }
    }
    QList<QMediaContent> list;
    QString filename;
    player->stop();
    Playlist->clear();
    slave_tx.data.data.dat.disp_mode_id = record.value(4).toInt();
    slave_tx.data.data.dat.langid = record.value(3).toInt();
    QStringList templist = record.value(6).toString().split(",");
    QStringList templist_1;
    for(int z = 0; z <templist.size();z++)
    {
        templist_1 = check_n_replace_voice_delim(templist[z],slave_tx.data.data.dat.langid);
        for(int j=0;j<templist_1.size();j++)
            list<<QUrl::fromLocalFile(QString("/home/apaul/PIS_VDB/"+templist_1[j]+".mp3"));
        qDebug()<<filename;
    }
    memset(slave_tx.data.data.dat.train_num,' ',6);
    memcpy(slave_tx.data.data.dat.train_num,route_path.Header.Route,strlen(route_path.Header.Route));
    slave_tx.data.data.dat.date = gps_packet.data.cpu.date.day;
    slave_tx.data.data.dat.month = gps_packet.data.cpu.date.month;
    slave_tx.data.data.dat.year = gps_packet.data.cpu.date.yrs;
    slave_tx.data.data.dat.hrs = gps_packet.data.cpu.time.hrs;
    slave_tx.data.data.dat.min = gps_packet.data.cpu.time.min;
    slave_tx.data.data.dat.sec = gps_packet.data.cpu.time.sec;
    slave_tx.data.data.dat.start_time = 1;
    slave_tx.data.data.dat.hold_time = 25;
    slave_tx.data.data.dat.rpt_cnt = 1;
    slave_tx.data.data.dat.brigthness = 100;
    slave_tx.data.fn_code = 0x81;
    unsigned char *dest_ptr = slave_tx.data.data.dat.bytes;
    ubyte language = 0;
    ubyte stops = 0;
    if(slave_tx.data.data.dat.langid == 255)
        slave_tx.data.data.dat.langid = route_path.Stops[route_path.Curr_stop].info.regional_lngugage;
    if(slave_tx.data.data.dat.langid > 1)
    {
        if(route_path.Stops[route_path.Curr_stop].info.regional_lngugage == route_path.Stops[0].info.regional_lngugage)
            language = 2;
        else if(route_path.Stops[route_path.Curr_stop].info.regional_lngugage == route_path.Stops[route_path.Header.no_of_stns - 1].info.regional_lngugage)
            language = 3;
        else
            language = 4;
    }
    switch(slave_tx.data.data.dat.disp_mode_id)
    {
        case 89:
            slave_tx.data.data.dat.brigthness = 80;
            break;
        case 2:
            if(language < 4)
            {
                *dest_ptr++ = strlen(route_path.Header.Description[language]);
                memcpy((unsigned char *)dest_ptr,(unsigned char *)route_path.Header.Description[language],strlen(route_path.Header.Description[language]));
                dest_ptr += strlen(route_path.Header.Description[language]);
                break;
            }
            break;
        case 3:
            if(language < 4)
            {
                *dest_ptr++ = strlen(route_path.Header.Source_station_name[language]);
                memcpy((unsigned char *)dest_ptr,(unsigned char *)route_path.Header.Source_station_name[language],strlen(route_path.Header.Source_station_name[language]));
                dest_ptr += strlen(route_path.Header.Source_station_name[language]);
                *dest_ptr++ = strlen(route_path.Header.Destination_station_name[language]);
                memcpy((unsigned char *)dest_ptr,(unsigned char *)route_path.Header.Destination_station_name[language],strlen(route_path.Header.Destination_station_name[language]));
                dest_ptr += strlen(route_path.Header.Destination_station_name[language]);
            }
            break;
        case 73:
        case 67:
            *dest_ptr++ = strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]);
            memcpy(dest_ptr,route_path.Stops[route_path.Curr_stop].info.station_name[language],strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]));
            dest_ptr += strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]);
            break;
        case 68:
            *dest_ptr++ = strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]);
            memcpy(dest_ptr,route_path.Stops[route_path.Curr_stop].info.station_name[language],strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]));
            dest_ptr += strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]);
            break;
        case 69:
            distance.integer = (qint16)route_path.Stops[route_path.Curr_stop].info.distance_from_curr_loc;
            *dest_ptr++ = distance.data.b;
            *dest_ptr++ = distance.data.a;
            *dest_ptr++ = strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]);
            memcpy(dest_ptr,route_path.Stops[route_path.Curr_stop].info.station_name[language],strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]));
            dest_ptr += strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]);
            break;
        case 70:
            distance.integer = (qint16)route_path.Stops[route_path.Curr_stop].info.distance_from_curr_loc;
            *dest_ptr++ = distance.data.b;
            *dest_ptr++ = distance.data.a;
            break;
        case 71:
            *dest_ptr++ = route_path.Stops[route_path.Curr_stop].info.arrival_time.hrs;
            *dest_ptr++ = route_path.Stops[route_path.Curr_stop].info.arrival_time.min;
            *dest_ptr++ = route_path.Stops[route_path.Curr_stop].info.arrival_time.hrs;
            *dest_ptr++ = route_path.Stops[route_path.Curr_stop].info.arrival_time.min;
            *dest_ptr++ = route_path.Stops[route_path.Curr_stop].info.arrival_time.hrs;
            *dest_ptr++ = route_path.Stops[route_path.Curr_stop].info.arrival_time.min;
            *dest_ptr++ = strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]);
            memcpy(dest_ptr,route_path.Stops[route_path.Curr_stop].info.station_name[language],strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]));
            dest_ptr += strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]);
            break;
        case 72:
            distance.integer = (qint16)gps_packet.data.cpu.speed;
            *dest_ptr++ = distance.data.b;
            *dest_ptr++ = distance.data.a;
            break;
        case 74:
            distance.integer = (qint16)route_path.Header.distance;
            *dest_ptr++ = distance.data.b;
            *dest_ptr++ = distance.data.a;
            *dest_ptr++ = route_path.Header.time.hrs;
            *dest_ptr++ = route_path.Header.time.min;
            *dest_ptr++ = strlen(route_path.Header.Source_station_name[language]);
            memcpy(dest_ptr,route_path.Header.Source_station_name[language],strlen(route_path.Header.Source_station_name[language]));
            dest_ptr += strlen(route_path.Header.Source_station_name[language]);
            *dest_ptr++ = strlen(route_path.Header.Destination_station_name[language]);
            memcpy(dest_ptr,route_path.Header.Destination_station_name[language],strlen(route_path.Header.Destination_station_name[language]));
            dest_ptr += strlen(route_path.Header.Destination_station_name[language]);
            break;
        case 75:
           *dest_ptr++ = route_path.Header.no_of_stns;
            for(int i=0;i<route_path.Header.no_of_stns-2;i++)
            {
               *dest_ptr++ = strlen(route_path.Stops[i+1].info.station_name[language]);
               memcpy(dest_ptr,route_path.Stops[i+1].info.station_name[language],strlen(route_path.Stops[i+1].info.station_name[language]));
               dest_ptr += strlen(route_path.Stops[i+1].info.station_name[language]);
            }
            break;
        case 76:
            distance.integer = (qint16)(gps_packet.data.cpu.speed/100);
            *dest_ptr++ = distance.data.b;
            *dest_ptr++ = distance.data.a;
            if((route_path.Curr_stop+5) < route_path.Header.no_of_stns)
            {
                *dest_ptr++ = 5;
                stops = route_path.Curr_stop+5;
            }
            else
            {
                *dest_ptr++ = route_path.Header.no_of_stns - route_path.Curr_stop;
                stops = route_path.Header.no_of_stns;
            }
            for(int i = route_path.Curr_stop;i<stops;i++)
            {
                *dest_ptr++ = strlen(route_path.Stops[i].info.station_name[language]);
                memcpy(dest_ptr,route_path.Stops[i].info.station_name[language],strlen(route_path.Stops[i].info.station_name[language]));
                dest_ptr += strlen(route_path.Stops[i].info.station_name[language]);
            }
            break;
        case 77:
            distance.integer = (qint16)route_path.Stops[route_path.Curr_stop].info.distance_from_curr_loc;
            *dest_ptr++ = distance.data.b;
            *dest_ptr++ = distance.data.a;
            *dest_ptr++ = route_path.Stops[route_path.Curr_stop].info.arrival_time.hrs;
            *dest_ptr++ = route_path.Stops[route_path.Curr_stop].info.arrival_time.min;
            *dest_ptr++ = route_path.Stops[route_path.Curr_stop].info.arrival_time.hrs;
            *dest_ptr++ = route_path.Stops[route_path.Curr_stop].info.arrival_time.min;
            *dest_ptr++ = strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]);
            memcpy(dest_ptr,route_path.Stops[route_path.Curr_stop].info.station_name[language],strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]));
            dest_ptr += strlen(route_path.Stops[route_path.Curr_stop].info.station_name[language]);
            break;
    }
    *dest_ptr++ = 0;
    *dest_ptr++ = 0;
    slave_tx.data.stx[0] = 0xAA;
    slave_tx.data.stx[1] = 0xCC;
    slave_tx.data.cntrl.src_add = 0x01;
    slave_tx.data.cntrl.dest_add = 0xFF;
    slave_tx.data.cntrl.sr_num = 1;
    slave_tx.data.length = 20 + (dest_ptr - slave_tx.data.data.dat.bytes) + 10 - 4;
    QByteArray crc = crc_o.crc_generate_modbus(&slave_tx.bytes[2],slave_tx.data.length);
    *dest_ptr++ = crc[0];
    *dest_ptr++ = crc[1];
    serial->write((char *)slave_tx.bytes,slave_tx.data.length+4);
    route_path.params.audio = 'D';
    if(gps_packet.data.cpu.time.hrs > 6 && gps_packet.data.cpu.time.hrs < 22)
    {
        if(route_path.Stops[route_path.Curr_stop].info.distance_from_curr_loc < 5 || ((route_path.Stops[route_path.Curr_stop].info.distance_frm_src  - route_path.Stops[route_path.Curr_stop].info.distance_from_curr_loc) < 5))
        {
            Playlist->addMedia(list);
            Playlist->setPlaybackMode(QMediaPlaylist::Sequential);
            if(!Playlist->isEmpty())
            {
                player->setPlaylist(Playlist);
                player->setVolume(80);
                player->play();
                route_path.params.audio = 'E';
            }
        }
    }
    device_update_timer.start(25000);
    return(1);
}

void running_route::check_pkt(void)
{
    Read_timer.stop();
}

void running_route::read_pkt(void)
{
    Read_timer.start(200);
    rec_data.append(serial->readAll());
}

void running_route::message_generator(qint64 event, void *data)
{
    QByteArray message;
    QByteArray transmit_pkt;
    QByteArray crc;
    QSettings settings("A_Paul_Instruments","COACHID");
    QSettings pissettings("A_Paul_Instruments","PIS");
    switch(event)
    {
        case TRAIN_DEPARTURE:
            message.clear();
            message.append("0000,");
            message.append("00,");
            message.append(QString::number(route_path.Stops[0].info.regional_lngugage).rightJustified(2,'0') + ",");
            message.append(QString::number(route_path.Stops[route_path.Header.no_of_stns-1].info.regional_lngugage).rightJustified(2,'0') + ",");
            message.append("00,");
            message.append("99,");

            message.append(settings.value("CoachAbbr").toString()+",");
            message.append(QString::fromLatin1(route_path.Header.Route) + ",");
            for(int language = 0; language < 4; language++)
            {
                if(language == 2 && route_path.Stops[0].info.regional_lngugage < 2)
                    continue;
                if(language == 3 && route_path.Stops[route_path.Header.no_of_stns-1].info.regional_lngugage < 2)
                    continue;
                message.append(QString::fromLatin1(route_path.Header.Description[language]));
                message.append(7);
                message.append(QString::fromLatin1(route_path.Header.Source_station_name[language]) + QString::fromLatin1(route_path.Header.to[language]) +QString::fromLatin1(route_path.Header.Destination_station_name[language]));
                message.append(7);
                message.append(QString::fromLatin1(route_path.Header.via[language]));
                for(int i = 1;i < route_path.Header.no_of_stns-1;i++)
                {
                    if(route_path.Stops[i].info.included_in_via_list)
                    {
                        message.append(QString::fromLatin1(route_path.Stops[i].info.station_name[language]));
                        if(i < route_path.Header.no_of_stns-2)
                            message.append(QString::fromLatin1(route_path.Header.comma[language]));
                    }
                }
                message.append(7);
                message.append(QString::fromLatin1(route_path.Header.welcome_message[language]));
                message.append(7);
            }
            transmit_pkt.clear();
            transmit_pkt.append("STX,");
            transmit_pkt.append(QString::number(message.size()+4+5+13+19+3+6+4).rightJustified(4,'0') + ",");
            transmit_pkt.append("CPU         ,");
            transmit_pkt.append("DDB               ,");
            transmit_pkt.append('D');
            transmit_pkt.append('B');
            transmit_pkt.append(",");
            transmit_pkt.append(message);
            crc = crc_o.crc_generate_modbus((unsigned char *)transmit_pkt.toStdString().c_str(),transmit_pkt.length());
            transmit_pkt.append(QString::number((unsigned char)crc[0]).rightJustified(3,'0'));
            transmit_pkt.append(QString::number((unsigned char)crc[1]).rightJustified(3,'0'));
            transmit_pkt.append(",ETX");
            serial->write(transmit_pkt);
            qDebug()<<"Pkt for Destination Board : " << transmit_pkt;
            route_path.params.event = "ROUTE SELECTED";
            break;
        case STOP_APPROACHING:
            msg_index = 0;
            msg_status.bits.trigger_on_approaching_periphery = 1;
            route_path.params.event = "STOP APPROACHING";
        break;
        case STOP_ARRIVAL:
            msg_index = 0;
            msg_status.bits.trigger_on_exit_periphery = 0;
            msg_status.bits.trigger_on_arrival = 1;
            route_path.params.event = "STOP ARRIVAL";
            if(route_path.Curr_stop == (route_path.Header.no_of_stns - 2))
            {
                pissettings.setValue("ROUTE",route_path.Header.LinkRoute);
                pissettings.sync();
            }
        break;
        case STOP_DEPARTURE:
            msg_index = 0;
            msg_status.bits.trigger_on_arrival = 0;
            msg_status.bits.trigger_on_exit_periphery = 1;
            route_path.params.event = "STOP DEPARTURE";
        break;
        case JOURNEY_END:
            msg_index = 0;
            msg_status.bits.trigger_on_journey_end = 1;
            route_path.params.event = "JOURNEY END";
        break;
    }
    emit log_event();
    device_update_timer.stop();
    manage_device_updates();
}

void running_route::openSerialPort()
{
    serial->setPortName("/dev/ttyACM0");
    if(!serial->setBaudRate(QSerialPort::Baud57600))
        qDebug() << "Can not set port_AT->setBaudRate";
    if(!serial->setDataBits(QSerialPort::Data8))
        qDebug() << "Can not set port_AT->setDataBits";
    if(!serial->setParity(QSerialPort::NoParity))
        qDebug() << "Can not set port_AT->setParity";
    if(!serial->setStopBits(QSerialPort::OneStop))
        qDebug() << "Can not set port_AT->setStopBits";
    if(!serial->setFlowControl(QSerialPort::NoFlowControl))
        qDebug() << "Can not set port_AT->setFlowControl";
    if (serial->open(QIODevice::ReadWrite))
        qDebug() << "Connected to PIS serial port successfully...";
    //else
       // qDebug("running_route::openSerialPort(): failed to open port....");
}

void running_route::timerEvent(QTimerEvent *event)
{
    int id = event->timerId();
    if(id == route_tasks_timer_id)
        route_tasks(&gps_packet);
    if(id == display_timer_id)
    {
        display_tasks();
    }
    else if(id == gps_timeout_timer_id)
    {
        killTimer(gps_timeout_timer_id);
        gps_timeout_timer_id = 255;
        if(route_path.status.bits.outage_rec)
            route_path.status.bits.outage_rec = 0;
    }
}

void running_route::calculate_multiplying_factor(void)
{
    float temp_mul_factor = 0;
    int stn_no = 0;
    int prev_stn_dist = route_path.Stops[stn_no++].info.distance_frm_src;
    while(stn_no < route_path.Header.no_of_stns)
    {
        track_dist_bn_stns[stn_no - 1]   = route_path.Stops[stn_no].info.distance_frm_src - prev_stn_dist;
        prev_stn_dist = route_path.Stops[stn_no].info.distance_frm_src;
        temp_mul_factor = get_distance_bn_pts(route_path.Stops[stn_no - 1].info.latit,route_path.Stops[stn_no - 1].info.longit,route_path.Stops[stn_no].info.latit,route_path.Stops[stn_no].info.longit);
        temp_mul_factor = (((float)(track_dist_bn_stns[stn_no - 1]) - temp_mul_factor)/temp_mul_factor)*10000;
        mul_factor[stn_no++ - 1] = (sinteger)temp_mul_factor;
    }
    emit route_events(TRAIN_DEPARTURE,0);
    msg_status.bits.trigger_pre_departure = 1;
}

void running_route::display_tasks(void)
{
    static int x = 1000;
    if(!serial->isOpen())
        openSerialPort();
    QString upcoming_stops;
    /** CLEAR THE STATIONS LIST EVERY TIME RUNNING ROUTE DISPLAY IS INITIALISED.IT DELETES THE ITEMS PERMANENTLY.  */
  //  qDebug("Running Route Display Initialising ...");
    ui->RouteNUm->setText(QString(route_path.Header.Route));
    ui->TrainName->setText(QString(route_path.Header.Description[0]));
    upcoming_stops = QString(route_path.Stops[route_path.Curr_stop].info.station_name[0]);
    for(int z=route_path.Next_stop;z<route_path.Header.no_of_stns;z++)
    {
        upcoming_stops += "," + QString(route_path.Stops[z].info.station_name[0]);
    }
    ui->nxt_station->setText(QString(route_path.Stops[route_path.Curr_stop].info.station_name[0]));


    QPainter painter(pixmap);
    painter.setBackground(QBrush(ui->next_upcoming->palette().color(QPalette::Background)));
    painter.setBackgroundMode(Qt::OpaqueMode);
    painter.setPen(ui->next_upcoming->palette().color(QPalette::Text));
    QFont font = painter.font();
    font.setPointSize(ui->next_upcoming->font().pointSize());
    painter.setFont(font);
    QFontMetrics fm(font);
    pixmap->fill(ui->next_upcoming->palette().color(QPalette::Background));
//    int width = fm.width(upcoming_stops);
//    if(width > 1000)
//        x--;
//    else
//        x = 500 - width/2;
//    painter.drawText(x,pixmap->rect().height()/2 + fm.height()/2,upcoming_stops);
    painter.drawText(pixmap->rect(),Qt::AlignCenter|Qt::TextWordWrap,upcoming_stops);
//    if(x == 0 - 1000 - width)
//        x = 1000;
    ui->next_upcoming->setPixmap(*pixmap);


    ui->distance->setText(QString::number(route_path.Stops[route_path.Curr_stop].info.distance_from_curr_loc) + " Kms");
    ui->estimatedtimearr->setText(QString::number(gps_packet.data.cpu.time.hrs).rightJustified(2,'0')+":"+QString::number(gps_packet.data.cpu.time.min).rightJustified(2,'0')+":"+QString::number(gps_packet.data.cpu.time.sec).rightJustified(2,'0'));
    ui->TrainName->setText(QString(route_path.Header.Description[0]));
}

float running_route::get_distance(float x2, float y2)
{
    float temp_distance;
    temp_distance = (curr_lattit - x2)*(curr_lattit - x2)+(curr_longit - y2)*(curr_longit - y2);
    temp_distance = sqrt(temp_distance);
    temp_distance = temp_distance * 176 / 945 / 1000;
    return(temp_distance);
}

float running_route::get_distance_bn_pts(float x1, float y1,float x2, float y2)
{
    float temp_distance;
    temp_distance = (x1 - x2)*(x1 - x2)+(y1 - y2)*(y1 - y2);
    temp_distance = sqrt(temp_distance);
    temp_distance = temp_distance * 176 / 945 / 1000;
    return(temp_distance);
}

void running_route::gps_data_collector(qint64 event, void *data)
{
    gps_packet = *(union gps_union *)data;
    gps_packet.data.status.bits.to_be_processed = 1;
    if(gps_timeout_timer_id != 255)
    {
        killTimer(gps_timeout_timer_id);
        gps_timeout_timer_id = 255;
    }

}

void running_route::play_message(int *data)
{
    manual_msg_id = *data++;
    manual_msg_index = *data;
    QSqlQuery mquery1(QSqlDatabase::database("Connection1"));
    mquery1.exec((QString("SELECT *FROM `tbl_msg_frame_list` where `msg_id` = '") + QString::number(manual_msg_id) + "'"));
    qDebug() << mquery1.lastQuery();
    manual_total_index = 0;
    while(mquery1.next())
    {
        manual_record[manual_total_index++] = mquery1.record();
    }
    manual_msg_index = 0;
    msg_status.bits.trigger_manual_alerts = 1;
    device_update_timer.stop();
    manage_device_updates();
}

void running_route::close_timer(void)
{
    if(display_timer_id != 255)
        killTimer(display_timer_id);
    if(route_tasks_timer_id != 255)
        killTimer(route_tasks_timer_id);
}

void running_route::manage_device_updates()
{
    if(msg_status.bits.trigger_manual_alerts)
    {
        if(!generate_alerts(manual_msg_id,manual_msg_index))
            msg_status.bits.trigger_manual_alerts = 0;
    }
    else if(msg_status.bits.trigger_pre_departure)
    {
        if(!rdso0087protocol("A",msg_index++))
        {
            msg_index = 0;
            msg_status.bits.trigger_pre_departure = 0;
        }
    }
    else if(msg_status.bits.trigger_on_departure)
    {
        if(!rdso0087protocol("A",msg_index++))
        {
            msg_index = 0;
            msg_status.bits.trigger_on_departure = 0;
        }
    }
    else if(msg_status.bits.trigger_on_exit_periphery)
    {
        route_path.params.event = "TRANSIT";
        if(!rdso0087protocol("B",msg_index++))
        {
            msg_index = 0;
            msg_status.bits.trigger_on_exit_periphery = 0;
            msg_status.bits.trigger_on_gen_start = 1;
        }
    }

    else if(msg_status.bits.trigger_on_approaching_periphery)
    {
        if(!rdso0087protocol("C",msg_index++))
        {
            msg_index = 0;
            msg_status.bits.trigger_on_approaching_periphery = 0;
        }
    }
    else if(msg_status.bits.trigger_on_arrival)
    {
        if(!rdso0087protocol("D",msg_index++))
        {
            msg_index = 0;
            msg_status.bits.trigger_on_arrival = 0;
            if(route_path.Curr_stop == route_path.Header.no_of_stns)
                msg_status.bits.trigger_on_journey_end = 1;
        }
    }
    else if(msg_status.bits.trigger_on_journey_end)
    {
        if(!rdso0087protocol("F",msg_index++))
        {
            msg_index = 0;
            killTimer(display_timer_id);
            msg_status.bits.trigger_on_journey_end = 0;
            return;
        }
    }
    else if(msg_status.bits.trigger_on_gen_start)
    {
        if(!rdso0087protocol("S",safety_msg_index))
        {
            if(route_path.status.bits.outage_rec)
            {
                msg_index = 0;
                if(!msg_status.bits.trigger_on_arrival)
                    msg_status.bits.trigger_on_exit_periphery = 1;
            }
            msg_status.bits.trigger_on_gen_start = 0;
        }
    }
}

void running_route::route_tasks(union gps_union *data)
{
   // qDebug()<<"route_tasks() route.cpp called....;";
 //   manage_device_updates();
    if(gps_packet.data.status.bits.to_be_processed)
    {
        if(gps_timeout_timer_id == 255)
            gps_timeout_timer_id = startTimer(3000);
        gps_packet.data.status.bits.to_be_processed = 0;
        curr_lattit = gps_packet.data.cpu.latit;
        curr_longit = gps_packet.data.cpu.longit;
        if(route_path.status.bits.outage_rec)
        {
           /*********************************************************************************************************************************************************/
           /***********************Calculate distances based on stop lat longs and the curr lat longs****************************************************************/
           /*********************************************************************************************************************************************************/
                route_path.Stops[route_path.Curr_stop].info.gps_distance_from_prev_loc = route_path.Stops[route_path.Curr_stop].info.gps_distance_from_curr_loc;
                route_path.Stops[route_path.Curr_stop].info.gps_distance_from_curr_loc = get_distance(route_path.Stops[route_path.Curr_stop].info.latit,route_path.Stops[route_path.Curr_stop].info.longit);
                route_path.Stops[route_path.Curr_stop].info.distance_from_prev_loc = route_path.Stops[route_path.Curr_stop].info.distance_from_curr_loc;
                double curr_distance = 0;
                curr_distance = route_path.Stops[route_path.Curr_stop].info.gps_distance_from_curr_loc;
                if(route_path.Curr_stop)
                    curr_distance = (((float)mul_factor[route_path.Curr_stop - 1] * curr_distance) / 10000) + curr_distance;
                else
                    curr_distance = (((float)mul_factor[0] * curr_distance) / 10000) + curr_distance;
                route_path.Stops[route_path.Curr_stop].info.distance_from_curr_loc = curr_distance;
            /*********************************************************************************************************************************************************/
            /***********************Calculate distances based on stop lat longs and the curr lat longs****************************************************************/
            /*********************************************************************************************************************************************************/

            /*********************************************************************************************************************************************************/
            /***********************Generate Arrival Departure triggers based on the distance of current stop form the current location*******************************/
            /*********************************************************************************************************************************************************/
             if(((route_path.Stops[route_path.Curr_stop].info.distance_from_curr_loc*1000) <= route_path.Stops[route_path.Curr_stop].info.approaching_peri) && ((route_path.Stops[route_path.Curr_stop].info.distance_from_prev_loc*1000) > route_path.Stops[route_path.Curr_stop].info.approaching_peri))
             {
                qDebug() << "WITHIN 1 KM OF " << QString::fromLatin1((const char*)route_path.Stops[route_path.Next_stop].info.station_name);
                emit route_events(STOP_APPROACHING,0);
             }
             else if(((uinteger)(route_path.Stops[route_path.Curr_stop].info.distance_from_curr_loc*1000) <= route_path.Stops[route_path.Curr_stop].info.entry_peri) && ((route_path.Stops[route_path.Curr_stop].info.distance_from_prev_loc*1000) > (route_path.Stops[route_path.Curr_stop].info.distance_from_curr_loc*1000)))
             {
                if(route_path.status.bits.inside_peri == 0)
                {
                    qDebug() << "ENTERED ENTRY PERIPHERY OF " << QString::fromLatin1((const char*)route_path.Stops[route_path.Curr_stop].info.station_name);
                    route_path.status.bits.inside_peri = 1;
                    route_path.status.bits.outside_peri = 0;
                    emit route_events(STOP_ARRIVAL,0);
                }
             }
             else if(((uinteger)(route_path.Stops[route_path.Curr_stop].info.distance_from_curr_loc*1000) > route_path.Stops[route_path.Curr_stop].info.exit_peri) && ((route_path.Stops[route_path.Curr_stop].info.distance_from_prev_loc*1000) < (route_path.Stops[route_path.Curr_stop].info.distance_from_curr_loc*1000)))
             {
                 if(route_path.status.bits.outside_peri == 0 && route_path.status.bits.inside_peri == 1)
                 {
                    qDebug() << "LEFT EXIT PERIPHERY OF " << QString::fromLatin1((const char*)route_path.Stops[route_path.Curr_stop].info.station_name);
                    route_path.Prev_stop = route_path.Curr_stop;
                    route_path.Curr_stop++;
                    route_path.Next_stop = route_path.Curr_stop + 1;
                    route_path.status.bits.inside_peri = 0;
                    route_path.status.bits.outside_peri = 1;
                    emit route_events(STOP_DEPARTURE,0);
                 }
             }
             /*********************************************************************************************************************************************************/
             /***********************Ended Arrival Departure triggers based on the distance of current stop form the current location**********************************/
             /*********************************************************************************************************************************************************/
        }
        if(route_path.status.bits.route_info_avail && (!route_path.status.bits.outage_rec))
            lost_path_recovery();
    }
}

void running_route::lost_path_recovery()
{
    int nearest_stn_no = route_path.Curr_stop;
    float actual_distance_between_currpt_n_a,actual_distance_between_currpt_n_b,actual_distance_between_currpt_n_c;
    while(route_path.Curr_stop <  route_path.Header.no_of_stns)
    {
        route_path.Stops[route_path.Curr_stop].info.distance_from_curr_loc = get_distance(route_path.Stops[route_path.Curr_stop].info.latit,route_path.Stops[route_path.Curr_stop].info.longit);
        route_path.Curr_stop++;
    }
    while(1)
    {
        while((route_path.Stops[nearest_stn_no].info.distance_from_curr_loc > route_path.Stops[nearest_stn_no + 1].info.distance_from_curr_loc) && (nearest_stn_no < route_path.Header.no_of_stns))
            nearest_stn_no++;
        route_path.Curr_stop = nearest_stn_no;
        if(!route_path.Curr_stop && route_path.Stops[0].info.distance_from_curr_loc < track_dist_bn_stns[0])
        {
            route_path.Curr_stop++;
            break;
        }
        else if(route_path.Curr_stop ==  (route_path.Header.no_of_stns - 1))
        {
            if(route_path.Stops[route_path.Curr_stop].info.distance_from_curr_loc < track_dist_bn_stns[route_path.Curr_stop - 1])
                break;
            else
            {
                route_path.Curr_stop = 0;
                return;
            }
        }
        else
        {
            actual_distance_between_currpt_n_a = (((float)mul_factor[nearest_stn_no - 1] * route_path.Stops[nearest_stn_no - 1].info.distance_from_curr_loc)/10000) + route_path.Stops[nearest_stn_no - 1].info.distance_from_curr_loc;
            actual_distance_between_currpt_n_b = (((((float)mul_factor[nearest_stn_no - 1] + (float)mul_factor[nearest_stn_no - 1])/2)* route_path.Stops[nearest_stn_no].info.distance_from_curr_loc)/10000) + route_path.Stops[nearest_stn_no].info.distance_from_curr_loc;
            actual_distance_between_currpt_n_c = (((float)mul_factor[nearest_stn_no] * route_path.Stops[nearest_stn_no + 1].info.distance_from_curr_loc)/10000) + route_path.Stops[nearest_stn_no + 1].info.distance_from_curr_loc;
            if(actual_distance_between_currpt_n_b < 0.800)
                break;
            if(actual_distance_between_currpt_n_a < track_dist_bn_stns[nearest_stn_no - 1] && actual_distance_between_currpt_n_c > track_dist_bn_stns[nearest_stn_no])
                break;
            else if(actual_distance_between_currpt_n_a > track_dist_bn_stns[nearest_stn_no - 1] && actual_distance_between_currpt_n_c < track_dist_bn_stns[nearest_stn_no])
            {
                route_path.Curr_stop++;
                break;
            }
            else if(actual_distance_between_currpt_n_b > track_dist_bn_stns[nearest_stn_no - 1])
            {
                while((route_path.Stops[nearest_stn_no].info.distance_from_curr_loc > route_path.Stops[nearest_stn_no + 1].info.distance_from_curr_loc) && (nearest_stn_no < route_path.Header.no_of_stns))
                    nearest_stn_no++;
                if(route_path.Curr_stop == route_path.Header.no_of_stns - 1 && route_path.Stops[route_path.Curr_stop].info.distance_from_curr_loc < track_dist_bn_stns[route_path.Curr_stop - 1])
                    break;

            }
            else if(actual_distance_between_currpt_n_b > track_dist_bn_stns[nearest_stn_no])
            {
                route_path.status.bits.outage_rec = 0;
                return;
            }
            else if(actual_distance_between_currpt_n_a < track_dist_bn_stns[nearest_stn_no - 1] && actual_distance_between_currpt_n_c < track_dist_bn_stns[nearest_stn_no])
            {
                if(temp_prev_distance != 0.0)
                {
                    if(gps_packet.data.cpu.speed>2 && temp_prev_distance > actual_distance_between_currpt_n_b)
                    {
                        route_path.status.bits.right_angle = 0;
                        break;
                    }
                    else if(gps_packet.data.cpu.speed>2 && temp_prev_distance < actual_distance_between_currpt_n_b)
                    {
                        route_path.Curr_stop++;
                        route_path.status.bits.right_angle = 0;
                        break;
                    }
                    else
                        return;
                }
                temp_prev_distance = actual_distance_between_currpt_n_b;
                route_path.status.bits.outage_rec = 0;
                route_path.status.bits.right_angle = 1;
            }
            else
                break;
        }
    }
    if(!route_path.status.bits.right_angle)
    {
        route_path.status.bits.outage_rec = 1;
        if(route_path.Curr_stop)
            route_path.Prev_stop = route_path.Curr_stop - 1;
        else
            route_path.Prev_stop = route_path.Curr_stop;
        route_path.Next_stop = route_path.Curr_stop + 1;
        if((route_path.Stops[route_path.Curr_stop].info.distance_from_curr_loc*1000) > route_path.Stops[route_path.Curr_stop].info.entry_peri)
        {
            route_path.status.bits.outside_peri = 1;
            emit route_events(STOP_DEPARTURE,0);
        }
        else
        {
            route_path.status.bits.inside_peri = 1;
            emit route_events(STOP_ARRIVAL,0);
        }
    }
}
