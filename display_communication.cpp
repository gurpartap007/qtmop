#include "display_communication.h"
extern QSqlDatabase db;
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
    server->bind(QHostAddress("192.168.0.30"),5000);
    send_display_event_messages('A');
}

display_communication::~display_communication()
{

}

void display_communication::send_train_route_info()
{
    QByteArray data;
    data.clear();
    data.append((const char *)current_route_data.train.train_num);
     data.append('\0');
    data.append(',');
    data.append(QString::fromUtf8((const char *)current_route_data.train.src.name.eng));
     data.append('\0');
    data.append(',');
    data.append(QString::fromUtf8((const char *)current_route_data.train.mid.name.eng));
     data.append('\0');
    data.append(',');
    data.append(QString::fromUtf8((const char *)current_route_data.train.des.name.eng));
     data.append('\0');
    data.append(',');
    qDebug() << QString::fromUtf8((const char *)current_route_data.train.current_station.name.eng);
    data.append(QString::fromUtf8((const char *)current_route_data.train.current_station.name.eng));
    data.append('\0');
    data.append(',');
    server->writeDatagram(data,data.size(),QHostAddress("192.168.0.25"),5001);
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
    server->writeDatagram(data,data.size(),QHostAddress("192.168.0.105"),5001);
    qDebug() << "DATA written --->" << data;
}

void display_communication::send_display_event_messages(unsigned char func_code)
{
    QByteArray message;
    QStringList message_codes;
    int message_code_index=0;
    /*********************************check database table tbl.msg fot available function codes****************
    if msg code exists in database table then take the information from the table and form packet to send else return without sending.
    1. retirve string from databse table.
    2. Replace delimeters with existing route information as per the real time running of route.
    ********************************************************************************************************/
    QSqlQuery find_msg_code("SELECT `msg_code` FROM `tbl_msg` ");
    while(find_msg_code.size() != message_code_index )
    {
    find_msg_code.next();
    message_codes.append(find_msg_code.value(message_code_index).toString());
    message_code_index ++;
    }
    qDebug() << "Message codes in DATABASE  ###### " << message_codes;
   /* form_packet_for_transmission("ICD",func_code,message.toStdString().c_str(),message.length());
    server->writeDatagram(data,data.size(),QHostAddress("192.168.0.105"),5001);
    qDebug() << "DATA written --->" << data;
    qDebug() << "data length" << data.length();
    data.clear();*/
}

void display_communication::form_packet_for_transmission(QString dest_id, unsigned char function_code, const char *packet_data, unsigned int data_length)
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
}

