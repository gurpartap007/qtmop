#include "lgps.h"

LGPS::LGPS()
{
    qDebug()<<"Setting up GPS serial Interface...";
    GPSSimulation=false;
    dataAccessible=false;
    initOK=false;

    checkGPS = new QTimer;
    connect(checkGPS,SIGNAL(timeout()),this,SLOT(checkGPSHealth()));
    //checkGPS->start(2*60*1000);  //2 minutes
}

LGPS::~LGPS()
{
    closeSerialPort();
}

/* GPS  RMC packet structure */
enum gpsdat
{
    HEADING,
    TIME_STAMP,
    VALIDITY,
    LATITUDE,
    NORTH_SOUTH,
    LONGITUDE,
    EAST_WEST,
    SPEED,
    TRUE_COURSE,
    DATE_STAMP,
    VARIATION_1,
    VARIATION_2,
    CHECKSUM
};

void LGPS::process_n_fill_packet()
{
    qDebug("process_n_fill_packet gps.cpp called...");
    QString date,tim,speed;
    unsigned long temp_lat_long1, temp_lat_long2;
    unsigned short temp_speed;
    gps_packet.data.cpu = gps_packet.data.isr;
    tim = QString::number(gps_packet.data.cpu.time.hrs) + ":" + QString::number(gps_packet.data.cpu.time.min) + ":" + QString::number(gps_packet.data.cpu.time.sec);
    memcpy( gps_packet.data.time, tim.toStdString().c_str(), 8);
    date = QString::number(gps_packet.data.cpu.date.day) + "/" + QString::number(gps_packet.data.cpu.date.month) + "/20" + QString::number(gps_packet.data.cpu.date.yrs);
    memcpy( gps_packet.data.date, date.toStdString().c_str(), 10);
    temp_lat_long1 = (unsigned long)(gps_packet.data.cpu.latit*10000);
    temp_lat_long2 = (temp_lat_long1/1000000)*60*10000;
    temp_lat_long2 += (temp_lat_long1%1000000);
    gps_packet.data.cpu.latit = (float)temp_lat_long2;
    temp_lat_long1 = (unsigned long)(gps_packet.data.cpu.longit*10000);
    temp_lat_long2 = (temp_lat_long1/1000000)*60*10000;
    temp_lat_long2 += (temp_lat_long1%1000000);
    gps_packet.data.cpu.longit = (float)temp_lat_long2;
    temp_speed = gps_packet.data.cpu.speed / 100;
    speed = QString::number(temp_speed);
    memcpy( gps_packet.data.speed, speed.toStdString().c_str(), 3);
    gps_packet.data.speed[3] = 0;

    emit gps_available(NEW_GPS_PKT,(void *)&gps_packet);
    emit this->gps_valid_packet_received();
}

void LGPS::update_gps_buffer(QString gps_line)
{
    qDebug("update_gps_buffer gps.cpp called...");
    QStringList gps_data;
    QString subString;
    bool status;
    int len = 0;
    QByteArray array(gps_line.toLocal8Bit());
    unsigned int chk_sum = 0;
    len = 1;
    qDebug()<<"update_gps_buffer ArrayLength :"<<QString::number(array.length());
    while (len < array.length())
    {
        if(array[len] == '*')
        {
            subString = gps_line.mid(gps_line.length()-2,2);
            chk_sum ^= subString.toUInt(&status,16);
            break;
        }
        chk_sum = chk_sum ^ array[len++];
    }
    if(chk_sum == 0)
    {
        gps_data = gps_line.split(",");//, QString::SkipEmptyParts);
        gps_packet.data.isr.latit = gps_data[LATITUDE].toFloat();
        gps_packet.data.isr.longit = gps_data[LONGITUDE].toFloat();
        gps_packet.data.isr.speed = gps_data[SPEED].toFloat();
        gps_packet.data.isr.speed = (KNOTS_TO_KMS_FACTOR*gps_packet.data.isr.speed*1000)/10;
        gps_packet.data.isr.heading = gps_data[TRUE_COURSE].toFloat();
        gps_packet.data.isr.time.hrs = gps_data[TIME_STAMP].mid(0,2).toInt();
        gps_packet.data.isr.time.min = gps_data[TIME_STAMP].mid(2,2).toInt();
        gps_packet.data.isr.time.sec = gps_data[TIME_STAMP].mid(4,2).toInt();
        gps_packet.data.isr.date.day = gps_data[DATE_STAMP].mid(0,2).toInt();
        gps_packet.data.isr.date.month = gps_data[DATE_STAMP].mid(2,2).toInt();
        gps_packet.data.isr.date.yrs = gps_data[DATE_STAMP].mid(4,2).toInt();
        if(gps_data[VALIDITY] == "A")
        {
            process_n_fill_packet();
            dataAccessible = true;
        }
        else
        {
            qDebug("update_gps_buffer : Not a valid GPS Packet.");
            dataAccessible = false;
        }
    }
    else
    {
        qDebug("update_gps_buffer : checksum does not match.");
    }
}

void LGPS::openSerialPort()
{
    serial->setPortName("ttyUSB1");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if (serial->open(QIODevice::ReadWrite))
    {
        qDebug() << "Connected";
    }
    else
    {
        show_message(serial->errorString());
        qDebug() << "Not Connected";
    }
}

void LGPS::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
}

void LGPS::readData()
{
    GPSData = serial->readLine();
    qDebug()<<"GPS Data:"<<GPSData;
}

void LGPS::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError)
    {
        show_message(serial->errorString());
        closeSerialPort();
    }
}

/**
 * @brief GPS::initialiseUSBPort
 * It initialises all the USB ports of Quectel module.
 */
void LGPS::initialiseUSBPort()
{

    /* Providing memory to Quectel Serial Ports */
    port_MD = new QSerialPort;
    port_NMEA = new QSerialPort;
    port_AT = new QSerialPort;
    port_PPP = new QSerialPort;

    /* Connecting its Signals */
    connect(port_AT,SIGNAL(readyRead()),this,SLOT(readResponse()));
    connect(port_AT,SIGNAL(error(QSerialPort::SerialPortError)),\
            this,SLOT(readOutputError(QSerialPort::SerialPortError)));
    connect(port_NMEA,SIGNAL(readyRead()),this,SLOT(readGPS()));

    /** Whenever the device files are created, their permissions have
     *  to be changed for ReadWrite. */

    if(system("sudo chmod 666 /dev/ttyUSB*")== -1)
        qDebug()<<"Can not change /dev/ttyUSB* permissions.";

    if(system("sudo chmod 666 /dev/ttyACM*")== -1)
        qDebug()<<"Can not change /dev/ttyACM* permissions.";

    if(system("sudo chmod 666 /dev/hidraw*")== -1)
        qDebug()<<"Can not change /dev/hidraw* permissions.";

    /* Configuring port_AT */
    port_AT->setPortName(AT);
    if(!port_AT->setBaudRate(QSerialPort::Baud9600))
        qDebug() << "Can not set port_AT->setBaudRate";
    if(!port_AT->setDataBits(QSerialPort::Data8))
        qDebug() << "Can not set port_AT->setDataBits";
    if(!port_AT->setParity(QSerialPort::NoParity))
        qDebug() << "Can not set port_AT->setParity";
   // if(!port_AT->setStopBits(QSerialPort::n))
     //   qDebug() << "Can not set port_AT->setStopBits";
    if(!port_AT->setFlowControl(QSerialPort::NoFlowControl))
        qDebug() << "Can not set port_AT->setFlowControl";
    if (port_AT->open(QIODevice::ReadWrite))
        qDebug() << "Connected to port_AT";
    else
    {
        show_message(QString("port_AT: ")+port_AT->errorString());
        port_AT->close();
        return;
    }

    /* configuring port_NMEA   */
    port_NMEA->setPortName(NMEA);
    if(!port_NMEA->setBaudRate(QSerialPort::Baud9600))
        qDebug() << "Can not set port_NMEA->setBaudRate";
    if(!port_NMEA->setDataBits(QSerialPort::Data8))
        qDebug() << "Can not set port_NMEA->setDataBits";
    if(!port_NMEA->setParity(QSerialPort::NoParity))
        qDebug() << "Can not set port_NMEA->setParity";
    if(!port_NMEA->setStopBits(QSerialPort::OneStop))
        qDebug() << "Can not set port_NMEA->setStopBits";
    if(!port_NMEA->setFlowControl(QSerialPort::NoFlowControl))
        qDebug() << "Can not set port_NMEA->setFlowControl";
    if (port_NMEA->open(QIODevice::ReadWrite))
        qDebug() << "Connected to port_NMEA";
    else
    {
        show_message(QString("port_NMEA: ")+port_NMEA->errorString());
        return;
    }

    /** Querying Quectel Module status to be fit for GPS Data output
     *  on port_NMEA by sending AT commands on port_AT */
    sendATCommand("AT+CMEE=2\r"); /* set error messages to verbose */
    sendATCommand("AT+QGPS?\r");
    sendATCommand("AT+QGPSEND\r");
    sendATCommand("AT+QGPS=1\r");
    sendATCommand("AT+QGPSCFG=\"gpsnmeatype\",2\r"); /* 2 for RMC GPSData */
    //sendATCommand("AT+QPOWD\r");
    simIdentity();

    initOK=true;
}

void LGPS::sendATCommand(QByteArray cmd)
{
    port_AT->write(cmd);
    port_AT->waitForBytesWritten(100);
    port_AT->waitForReadyRead(300);
}

void LGPS::readResponse()
{
   // qDebug()<<port_AT->readAll();
}

void LGPS::readGPS()
{
    port_NMEA->waitForReadyRead(100);
    QString filename = "/home/apaul/files/gps.txt";
    QFile file(filename);
    if(file.open( QFile::Append))
    {
        qDebug()<<"File opened..";
    }

    QTextStream stream(&file);
    GPSData =  port_NMEA->readLine();
    qDebug()<<"readGPS GPASData:"<<GPSData;
    /* Logging GPSData to the file */
    stream << GPSData;
    /* Calling gps.cpp function to update buffer */
    if(!GPSSimulation)
        update_gps_buffer(GPSData);
}

void LGPS::disableSimulation()
{
    GPSSimulation = false;
}

void LGPS::enableSimulation()
{
    GPSSimulation = true;
}

void LGPS::readOutputError(QSerialPort::SerialPortError e)
{
    if (e == QSerialPort::ResourceError)
    {
        qDebug()<<serial->errorString();
    }
}

/**
 * @brief GPS::simulateFromFile
 * @param gps_file
 *
 * This function simulate GPS triggered events, taking gps_file as argument.
 */
void LGPS::simulateFromFile(QString gps_file)
{
    if(!gps_file.isEmpty())
    {
        simulation_file.setFileName(gps_file);
        if(simulation_file.exists())
        {
            simulation_file.open(QIODevice::ReadOnly | QIODevice::Text);
            simulation_in_stream.setDevice(&simulation_file);
            connect(&simulation_timer,SIGNAL(timeout()),this,SLOT(gpsSimulation()));
            GPSSimulation=true;            /*local variable to detect GPS Simulation */
            simulation_timer.start(1000);  /*every one second */
        }
    }
    // simulation file should be in proper format
    // author's recommendations should not be ignored
}


void LGPS::gpsSimulation()
{
    if(GPSSimulation)
    {
        if(!simulation_in_stream.atEnd())
        {
            tempData = simulation_in_stream.readLine();
            update_gps_buffer(tempData);
            qDebug("GPS Simulation Active...");
        }
        else
        {
            disableSimulation();
        }
    }
}

void LGPS::simIdentity()
{
    port_AT->readAll();
    sendATCommand("AT+GSN\r");
    //port_AT->waitForBytesWritten(100);
    //port_AT->waitForReadyRead(100);
    IMEI = port_AT->readAll().toStdString().c_str();
    if(!IMEI.isEmpty())
    {
        IMEI= IMEI.left(17);              //'\r\n' two bytes or two characters
        IMEI=IMEI.right(15);
        qDebug()<<"imei:"<<IMEI;
    }

    sendATCommand("AT+CIMI\r");
    //port_AT->waitForBytesWritten(100);
    //port_AT->waitForReadyRead(100);
    SIM = port_AT->readAll().toStdString().c_str();
    if(!SIM.isEmpty())
    {
        SIM= SIM.left(17);                      //'\r\n' two bytes or two characters
        SIM= SIM.right(15);
        qDebug()<<"sim:"<<SIM;
    }

    sendATCommand("AT+QCCID\r");
    //port_AT->waitForBytesWritten(100);
    //port_AT->waitForReadyRead(100);
    SIMCARD = port_AT->readAll().toStdString().c_str();

    if(!SIMCARD.isEmpty())
    {
        SIMCARD = SIMCARD.split(':').at(1);
        SIMCARD = SIMCARD.left(21);
        SIMCARD = SIMCARD.right(20);
        qDebug()<<"simcard:"<<SIMCARD;
    }

    sendATCommand("AT+CSQ\r");
    SIGSTR = port_AT->readAll().toStdString().c_str();
    qDebug()<<"sigstr:"<<SIGSTR;

    if(!SIGSTR.isEmpty())
    {
        SIGSTR = SIGSTR.mid(8,2);
        qDebug()<<"sigstr:"<<SIGSTR;
    }
}

QString LGPS::getGPSLibVersion()
{
    return QString(LIB_VERSION);
}

QString LGPS::getLatitude()
{
    if(dataAccessible)
        return latLongToQString(gps_packet.data.cpu.latit);
    else
        return "0000.0000";
}

QString LGPS::getLongitude()
{
    if(dataAccessible)
        return latLongToQString(gps_packet.data.cpu.longit);
    else
        return "0000.0000";
}

QString LGPS::getModuleIMEI()
{
    if(IMEI.isEmpty())
        return QString("123123123123123");
    else
        return IMEI;
}

QString LGPS::getSIM_IMSI()
{
    if(SIM.isEmpty())
        return QString("123123123123123");
    else
        return SIM;
}

QString LGPS::getSIM_CCID()
{
    if(SIMCARD.isEmpty())
        return QString("12312312312312312312");
    else
        return SIMCARD;
}

QString LGPS::getSignalStrength()
{
    if(SIGSTR.isEmpty())
        return QString("00");
    else
        return SIGSTR;
}

QString LGPS::getSpeed()
{
    if(dataAccessible)
        return QString::number(gps_packet.data.cpu.speed);
    else return "000";
}

QString LGPS::latLongToQString(float latLong)
{
    unsigned int deg,min;
    float temp;
    deg=(latLong/600000);
    temp=(float)((float)latLong/10000 - (float)deg*60);
    deg*=100;
    deg+=temp;
    min=((temp-(unsigned int)temp)*10000);
    return QString::number(deg)+"."+QString::number(min);
}

void LGPS::show_message(QString message)
{
    QMessageBox box;
    box.setText(QString("GPS: ")+message);

    box.setStyleSheet("QMessageBox { background-color: cyan;\
                                     border-style: outset; \
                                     border-width: 4px;\
                                     border-color: blue;\
                                     font:28pt ubuntu;}"\
                                     "QMessageBox QPushButton {background-color: cyan;\
                                                               font:22pt ubuntu;\
                                                               border-width: 4px;\
                                                               border-color: black;}");
    box.setWindowFlags(Qt::WindowStaysOnTopHint|Qt::X11BypassWindowManagerHint | Qt::FramelessWindowHint);
    box.show();
}

void LGPS::checkGPSHealth()
{
    if(!initOK)
        initialiseUSBPort();
    else
        qDebug("GPS: Running OK");
}
