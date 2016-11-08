#include "display_communication.h"
#define RS485_DATA_PORT 5000
extern QSqlDatabase db;
extern int current_station;
int aau_repeat_count,icd_repeat_count;
unsigned char crc_high_lookup[] =
{
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40
};

unsigned char crc_low_lookup[] =
{
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
    0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
    0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
    0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
    0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
    0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
    0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
    0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
    0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
    0x40
};
extern route_struct current_route_data;
display_communication::display_communication(QObject *parent) : QObject(parent)
{
    server = new QUdpSocket(this);
    announcements_streamer = new music_streamer();
    server->bind(QHostAddress::Broadcast,RS485_DATA_PORT);
    hcd_timer = new QTimer;
    QSqlQuery update_configuration_table("SELECT  `head_code_scheme`,`handicap_coach1`,`handicap_coach2` from `configuration`");
    update_configuration_table.first();
    QSqlQuery get_schemes("SELECT * from `tbl_schemes` where `scheme_id` = '" + update_configuration_table.value(0).toString() + "'");
    get_schemes.first();
    hcd_timer->setInterval(get_schemes.value(2).toInt() * 1000);
   // qDebug() << "HCD TIMER INTERVAL" << QString::number(((get_schemes.value(2).toInt()) * 1000));
    connect(hcd_timer,SIGNAL(timeout()),this,SLOT(send_headcode_frame()));
    connect(this,SIGNAL(create_playlist(QString)),announcements_streamer,SLOT(create_announcement_playlist(QString)));
    connect(server,SIGNAL(readyRead()),this,SLOT(start_player()));
    port = new QSerialPort;
    open_serialport();
    //hcd_timer->start();
    //send_display_event_messages('A');
}

display_communication::~display_communication()
{

}

void display_communication::send_train_route_info(QString func_code)
{

    //device_reset();
    //Sleeper::sleep(15);
   send_display_event_messages(func_code);
   // send_headcode_frame();

}

QByteArray display_communication::generate_crc(unsigned char *buffer, unsigned int buffer_length)
{
    unsigned char crc_high = 0xFF;
    unsigned char crc_low = 0xFF;
    unsigned char crc_index;
    while(buffer_length!=0)
    {
        crc_index = crc_low ^ *buffer++;
        crc_low = crc_high ^ crc_high_lookup[crc_index];
        crc_high = crc_low_lookup[crc_index];
        buffer_length --;
    }
    QByteArray crc;
    crc.append(crc_low);
    crc.append(crc_high);
    return crc;
}

void display_communication::device_reset()
{
    data.clear();
    data.append("STX0047,TCU         ,ALL               ,G,");
    data.append(generate_crc((unsigned char *)data.toStdString().c_str(),data.length()));
    data.append("ETX");
    server->writeDatagram(data,data.size(),QHostAddress::Broadcast,RS485_DATA_PORT);
   // qDebug() << "DATA written --->" << data;
}

void display_communication::open_serialport()
{
  /*  port->setPortName("/dev/ttyS1");
    port->setPortName(port->portName());
    port->setBaudRate(QSerialPort::Baud9600);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);
    if (port->open(QIODevice::ReadWrite)) {
      //  qDebug() << "Connected to " << port->portName();
    } else {
       // qDebug() << "Not Connected to " << port->portName();
    }*/
}

QString display_communication::replace_eng_delimiters(QString *eng_message)
{
    qDebug() << "ENGLISH Original :::" << *eng_message;
    QString *english_msg;
    QTime current_time;
    current_time = QTime::currentTime();
    english_msg = eng_message;
    QStringList delimiters,slow_fast_string_id,platform_dir_string_id;
    delimiters << "<TT>"<<"<CNUM>"<<"<SSTN>"<<"<DSTN>"<<"<VSTN>"<<"<LS>"<<"<HH>"<<"<MM>"<<"<NSTN>"<<"<PF>"<<"<SSTA>";
    slow_fast_string_id << "'STRTSE'" << "'STRTFE'";
    platform_dir_string_id << "'STRPLE'"<<"'STRPRE'";
    int i = 0;

    for(i=0;i<delimiters.length();i++)
    {
        if(english_msg->contains(delimiters[i]))
        {
            switch(i)
            {
            case 0:
            {
                QString query_string = "SELECT `string_msg` FROM `tbl_string` where string_id =  ";
                query_string += slow_fast_string_id[current_route_data.train.slow_fast == 'F'];
                QSqlQuery find_slow_fast_string(query_string);
                find_slow_fast_string.next();
                english_msg->replace(delimiters[i],find_slow_fast_string.value(0).toString());
            }
                break;
            case 1: english_msg->replace(delimiters[i],QString::number(current_route_data.train.coach_count));
                break;
            case 2: english_msg->replace(delimiters[i],QString::fromLatin1((const char *)current_route_data.train.src.name.eng));
                break;
            case 3: english_msg->replace(delimiters[i],QString::fromLatin1((const char *)current_route_data.train.des.name.eng));
                break;
            case 4: english_msg->replace(delimiters[i],QString::fromLatin1((const char *)current_route_data.train.mid.name.eng));
                break;
            case 5:
            {
                if(current_route_data.train.ladies_special == 'Y')
                {
                    QString query_string = "SELECT `string_msg` FROM `tbl_string` where string_id = 'STRLSE'";
                    QSqlQuery find_ladies_special_string(query_string);
                    find_ladies_special_string.next();
                    english_msg->replace(delimiters[i],find_ladies_special_string.value(0).toString());
                }
                else
                    english_msg->replace(delimiters[i]," ");
            }
                break;
            case 6: english_msg->replace(delimiters[i],QString::number(current_time.hour()));
                break;
            case 7: english_msg->replace(delimiters[i],QString::number(current_time.minute()));
                break;
            case 8: english_msg->replace(delimiters[i],QString::fromLatin1((const char *)current_route_data.stn[current_route_data.status.next_halting_stn].stn_name[0]));
                break;
            case 9: QString query_string = "SELECT `string_msg` FROM `tbl_string` where string_id =  ";
                query_string += platform_dir_string_id[!(current_route_data.stn[current_route_data.status.next_halting_stn].bits.pf_left)];
                QSqlQuery find_platform_direction_string(query_string);
                find_platform_direction_string.next();
                english_msg->replace(delimiters[i],find_platform_direction_string.value(0).toString());
                break;
            }
        }
    }
    return *english_msg;
}

QString display_communication::replace_hindi_delimiters(QString *hindi_message)
{

    QString *hindi_msg;
    QTime current_time;
    current_time = QTime::currentTime();
    hindi_msg = hindi_message;
    QStringList delimiters,slow_fast_string_id,platform_dir_string_id;
    delimiters << "<TT>"<<"<CNUM>"<<"<SSTN>"<<"<DSTN>"<<"<VSTN>"<<"<LS>"<<"<HH>"<<"<MM>"<<"<NSTN>"<<"<PF>"<<"<SSTA>";
    slow_fast_string_id << "'STRTSH'" << "'STRTFH'";
    platform_dir_string_id << "'STRPLH'"<<"'STRPRH'";
    int i = 0;

    for(i=0;i<delimiters.length();i++)
    {
        if(hindi_msg->contains(delimiters[i]))
        {
            switch(i)
            {
            case 0:
            {
                QString query_string = "SELECT `string_msg` FROM `tbl_string` where string_id =  ";
                query_string += slow_fast_string_id[current_route_data.train.slow_fast == 'F'];
                QSqlQuery find_slow_fast_string(query_string);
                find_slow_fast_string.next();
                hindi_msg->replace(delimiters[i],find_slow_fast_string.value(0).toString());
            }
                break;
            case 1: hindi_msg->replace(delimiters[i],QString::number(current_route_data.train.coach_count));
                break;
            case 2: hindi_msg->replace(delimiters[i],QString::fromLatin1((const char *)current_route_data.train.src.name.hin));
                break;
            case 3: hindi_msg->replace(delimiters[i],QString::fromLatin1((const char *)current_route_data.train.des.name.hin));
                break;
            case 4: hindi_msg->replace(delimiters[i],QString::fromLatin1((const char *)current_route_data.train.mid.name.hin));
                break;
            case 5:
            {
                if(current_route_data.train.ladies_special == 'Y')
                {
                    QString query_string = "SELECT `string_msg` FROM `tbl_string` where string_id = 'STRLSH'";
                    QSqlQuery find_ladies_special_string(query_string);
                    find_ladies_special_string.next();
                    hindi_msg->replace(delimiters[i],find_ladies_special_string.value(0).toString());
                }
                else
                    hindi_msg->replace(delimiters[i]," ");
            }
                break;
            case 6: hindi_msg->replace(delimiters[i],QString::number(current_time.hour()));
                break;
            case 7: hindi_msg->replace(delimiters[i],QString::number(current_time.minute()));
                break;
            case 8: hindi_msg->replace(delimiters[i],QString::fromLatin1((const char *)current_route_data.stn[current_route_data.status.next_halting_stn].stn_name[1]));
                break;
            case 9: QString query_string = "SELECT `string_msg` FROM `tbl_string` where string_id =  ";
                query_string += platform_dir_string_id[!(current_route_data.stn[current_route_data.status.next_halting_stn].bits.pf_left)];
                QSqlQuery find_platform_direction_string(query_string);
                find_platform_direction_string.next();
                hindi_msg->replace(delimiters[i],find_platform_direction_string.value(0).toString());
                break;
            }
        }
    }
    qDebug() << "HINDI MESSAGE:::" << hindi_msg;
    return *hindi_msg;
}

QString display_communication::replace_regional_delimiters(QString *regional_message)
{
    QString *regional_msg;
    QTime current_time;
    current_time = QTime::currentTime();
    regional_msg = regional_message;
    QStringList delimiters,slow_fast_string_id,platform_dir_string_id;
    delimiters << "<TT>"<<"<CNUM>"<<"<SSTN>"<<"<DSTN>"<<"<VSTN>"<<"<LS>"<<"<HH>"<<"<MM>"<<"<NSTN>"<<"<PF>"<<"<SSTA>";
    slow_fast_string_id << "'STRTSR'" << "'STRTFR'";
    platform_dir_string_id << "'STRPLR'"<<"'STRPRR'";
    int i = 0;

    for(i=0;i<delimiters.length();i++)
    {
        if(regional_msg->contains(delimiters[i]))
        {
            switch(i)
            {
            case 0:
            {
                QString query_string = "SELECT `string_msg` FROM `tbl_string` where string_id =  ";
                query_string += slow_fast_string_id[current_route_data.train.slow_fast == 'F'];
                QSqlQuery find_slow_fast_string(query_string);
                find_slow_fast_string.next();
                regional_msg->replace(delimiters[i],find_slow_fast_string.value(0).toString());
            }
                break;
            case 1: regional_msg->replace(delimiters[i],QString::number(current_route_data.train.coach_count));
                break;
            case 2: regional_msg->replace(delimiters[i],QString::fromLatin1((const char *)current_route_data.train.src.name.reg1));
                break;
            case 3: regional_msg->replace(delimiters[i],QString::fromLatin1((const char *)current_route_data.train.des.name.reg1));
                break;
            case 4: regional_msg->replace(delimiters[i],QString::fromLatin1((const char *)current_route_data.train.mid.name.reg1));
                break;
            case 5:
            {
                if(current_route_data.train.ladies_special == 'Y')
                {
                    QString query_string = "SELECT `string_msg` FROM `tbl_string` where string_id = 'STRLSR'";
                    QSqlQuery find_ladies_special_string(query_string);
                    find_ladies_special_string.next();
                    regional_msg->replace(delimiters[i],find_ladies_special_string.value(0).toString());
                }
                else
                    regional_msg->replace(delimiters[i]," ");

            }
                break;
            case 6: regional_msg->replace(delimiters[i],QString::number(current_time.hour()));
                break;
            case 7: regional_msg->replace(delimiters[i],QString::number(current_time.minute()));
                break;
            case 8:
                regional_msg->replace(delimiters[i],QString::fromLatin1((const char *)current_route_data.stn[current_route_data.status.next_halting_stn].stn_name[2]));
                break;
            case 9: QString query_string = "SELECT `string_msg` FROM `tbl_string` where string_id =  ";
                query_string += platform_dir_string_id[!(current_route_data.stn[current_route_data.status.next_halting_stn].bits.pf_left)];
                QSqlQuery find_platform_direction_string(query_string);
                find_platform_direction_string.next();
                regional_msg->replace(delimiters[i],find_platform_direction_string.value(0).toString());
                break;
            }
        }
    }
    return *regional_msg;
}



void display_communication::form_packet_for_transmission(QString dest_id, QString function_code, const char *packet_data, unsigned int data_length)
{
    data.clear();
    data.append("STX");
    data.append(QString::number(data_length+3+4+1+13+19+2+3+2).rightJustified(4,'0'));
    data.append(',');
    data.append("TCU         ,");
    data.append(dest_id);
    data.append(',');
    data.append(function_code);
    data.append(',');
    data.append(packet_data);
    data.append(generate_crc((unsigned char *)data.toStdString().c_str(),data.length()));
    data.append("ETX");
    //qDebug() << "PACKET FOR HCD::::"  << QString::fromUtf8(data.data());
}
void display_communication::send_headcode_frame()
{
    QString func_code("A");
    QByteArray message;
    /**************fill pkt for headcode as per communication protocol*****************************/
    message.clear();
    current_route_data.train.reg_lang1_code = Telugu;
    message.append(QString::number(current_route_data.train.reg_lang1_code));
    message.append(',');
    QSqlQuery update_configuration_table("SELECT  `head_code_scheme`,`handicap_coach1`,`handicap_coach2` from `configuration`");
    update_configuration_table.first();
   // qDebug() << update_configuration_table.value(0).toString();
    QSqlQuery get_schemes("SELECT * from `tbl_schemes` where `scheme_id` = '" + update_configuration_table.value(0).toString() + "'");
    get_schemes.first();
    message.append(get_schemes.value(2).toString());   //display-time
    message.append(',');
    if(current_route_data.status.hcd_frame_number > get_schemes.value(1).toInt())
        current_route_data.status.hcd_frame_number = 0;
    current_route_data.status.hcd_frame_number++;
    message.append(QString::number(current_route_data.status.hcd_frame_number));
    message.append(',');
    message.append(QString::fromLatin1((const char *)current_route_data.train.train_num));
    message.append(",G,");
    message.append(current_route_data.train.slow_fast);
    message.append(",");
    message.append(QString::number(current_route_data.train.coach_count));
    message.append(",");
    message.append(QString::number(current_route_data.train.ladies_special=='Y'));
    message.append(",");
    message.append(update_configuration_table.value(1).toString());
    message.append((","));
    message.append(update_configuration_table.value(2).toString());
    message.append((","));
    message.append("00:00:00");//time to be updated here
    message.append((","));
    message.append(QString::fromLatin1((const char *)current_route_data.train.src.name.eng));
    message.append(7);
    message.append(QString::fromLatin1((const char *)current_route_data.train.src.name.hin));
    message.append(7);
    message.append(QString::fromLatin1((const char *)current_route_data.train.src.name.reg1));
    message.append(7);
    message.append(QString::fromLatin1((const char *)current_route_data.train.des.name.eng));
    message.append(7);
    message.append(QString::fromLatin1((const char *)current_route_data.train.des.name.hin));
    message.append(7);
    message.append(QString::fromLatin1((const char *)current_route_data.train.des.name.reg1));
    message.append(7);
    message.append(QString::fromLatin1((const char *)current_route_data.train.mid.name.eng));
    message.append(7);
    message.append(QString::fromLatin1((const char *)current_route_data.train.mid.name.hin));
    message.append(7);
    message.append(QString::fromLatin1((const char *)current_route_data.train.mid.name.reg1));
    message.append(7);
    //message.append(generate_crc((unsigned char *)data.toStdString().c_str(),data.length()));
    //message.append("ETX");
  //  qDebug() << "data" << QString::fromLatin1(message.data());
  //  qDebug() << "data length" << message.length();
    QString device_id = "HCD" + update_configuration_table.value(0).toString() + "              ";
    /**********************************************************************************************/
    form_packet_for_transmission(device_id,func_code,message.toStdString().c_str(),message.length());
  //  port->write(data);
    data.clear();
}

void display_communication::start_player()
{

}
void display_communication::send_display_event_messages(QString func_code)
{
    QByteArray message;
    QString english_msg,hindi_msg,regional_msg;
    /******************************Announcement to be send from here*********************************************/

    /*********************************check database table tbl.msg for available function codes******************
    if msg code exists in database table then take the information from the table and form packet to send else return without sending.
    1. retirve string from databse table.
    2. Replace delimeters with existing route information as per the real time running of route.
    ********************************************************************************************************/

    QString Query_to_get_data_for_msg_code = "SELECT * FROM `tbl_msg` where `msg_code` = '";
    Query_to_get_data_for_msg_code += func_code;
    Query_to_get_data_for_msg_code += "' and msg_instance = '1'";
    QSqlQuery get_msg_strings(Query_to_get_data_for_msg_code);
    get_msg_strings.next();
    if(get_msg_strings.value(1).toString() == func_code)
    {
        english_msg  = get_msg_strings.value(9).toString();
        hindi_msg    = get_msg_strings.value(10).toString();
        regional_msg = get_msg_strings.value(11).toString();
        english_msg = replace_eng_delimiters(&english_msg);
        hindi_msg = replace_hindi_delimiters(&hindi_msg);
        regional_msg = replace_regional_delimiters(&regional_msg);
      //  qDebug() << "English Message after removing delimiters" << english_msg;
      //  qDebug() << "Hindi Message after removing delimiters" << hindi_msg;
      //  qDebug() << "Regional Message after removing delimiters" << regional_msg;
    }
    else
        return;
    aau_repeat_count = 2;
    icd_repeat_count = 2;
    current_route_data.train.reg_lang1_code = 4;
    message.append(QString::number(current_route_data.train.reg_lang1_code).rightJustified(2,'0'));
    message.append(',');
    message.append(QString::number(aau_repeat_count));   //TO DO Take the value from Database Configuration table
    message.append(',');
    message.append(QString::number(icd_repeat_count));   //TO DO Take the value from Database Configuration table
    message.append(',');
    message.append(get_msg_strings.value(8).toString());
    message.append(',');
    message.append(english_msg.toLatin1());
    message.append(7);
    message.append(hindi_msg.toLatin1());
    message.append(7);
    message.append(regional_msg.toLatin1());
    message.append(7);
    form_packet_for_transmission("ICD1              ",func_code,message.toStdString().c_str(),message.length());
   server->writeDatagram(data,data.size(),QHostAddress::Broadcast,RS485_DATA_PORT);
    emit create_playlist(func_code);
    qDebug() << "DATA written --->" << data;
    data.clear();
}

