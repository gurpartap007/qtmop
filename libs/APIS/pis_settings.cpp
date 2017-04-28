#include "pis_settings.h"

PIS_SETTINGS::PIS_SETTINGS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PIS_SETTINGS)
{
    ui->setupUi(this);
    qDebug("Setting up PIS_Setting ....");
    this->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::X11BypassWindowManagerHint|Qt::FramelessWindowHint);
    setFocusPolicy(Qt::NoFocus);

    ui->lineEdit->showNumKeysOnly();
    ui->lineEdit_2->showNumKeysOnly();
    ui->lineEdit_3->showNumKeysOnly();
    ui->lineEdit_4->showNumKeysOnly();
    ui->lineEdit_5->showAlphaNumKeys();

    gpsData = new LGPS;
    admn = new admin(this);
    QStringList gps_files;
    QSettings unitsettings("A_Paul_Instruments","UNITID");
    QSettings coachsettings("A_Paul_Instruments","COACHID");
    QSettings pissettings("A_Paul_Instruments","PIS");
    pissettings.sync();
    UnitID = unitsettings.value("unitID").toString();
    CoachID = coachsettings.value("coachID").toString();
    CoachAbbrIndex = coachsettings.value("CoachAbbrIndex").toInt();
    CoachAbbr = coachsettings.value("CoachAbbrNum").toString();
    CoachAbbrb = coachsettings.value("CoachAbbr").toString();
    en_speed_display = pissettings.value("Speed").toBool();
    en_destination_board = pissettings.value("DestinationBoard").toBool();
    en_logging = pissettings.value("logging").toBool();
    en_safety_slogans = pissettings.value("SafetySlogans").toBool();
    en_announcement = pissettings.value("Announcement").toBool();
    ui->checkBox->setChecked(en_speed_display);
    ui->checkBox_8->setChecked(en_destination_board);
    ui->checkBox_3->setChecked(en_logging);
    ui->checkBox_4->setChecked(en_safety_slogans);
    ui->checkBox_6->setChecked(en_announcement);
    ServerIP = pissettings.value("ServerIP").toString();
    ServerPortASync = pissettings.value("ServerPortAsync").toString();
    ServerPortSync = pissettings.value("ServerPortSync").toString();
    announcement_on_time = pissettings.value("AnnouncementOntime").toTime();
    announcement_off_time = pissettings.value("AnnouncementOfftime").toTime();
    displayParameters = pissettings.value("DisplayParams").toString();
    loggingFrequency = pissettings.value("loggingFrequency").toInt();
    loggingFrequencyTime = ui->comboBox_2->itemText(loggingFrequency).toInt();
    ui->comboBox_2->setCurrentIndex(loggingFrequency);
    ui->timeEdit_2->setTime(announcement_on_time);
    ui->timeEdit_3->setTime(announcement_off_time);
    ui->lineEdit->setText(ServerIP);
    ui->lineEdit_2->setText(ServerPortASync);
    ui->lineEdit_3->setText(ServerPortSync);

    QDate current = QDate::currentDate();
    ui->dateEdit->setDate(current);
    ui->timeEdit->setTime(QTime::currentTime());
    QDirIterator it("/home/apaul/SIM",QDir::Files,QDirIterator::Subdirectories);
    while(it.hasNext())
        gps_files<<it.next();
    ui->comboBox_3->addItems(gps_files);
    ui->comboBox->setCurrentIndex(CoachAbbrIndex);
    ui->lineEdit_4->setText(CoachAbbr);
    ui->lineEdit_5->setText(CoachID);
    //d keyWid->setWindowFlags(Qt::WindowDoesNotAcceptFocus);
    //keyWid->setFocusPolicy(Qt::NoFocus);
    //keyWid->hide();
    //dilip ui->verticalLayout_11->addWidget(keyWid);
    //connect(keyWid,SIGNAL(keyPressed(QString)),this,SLOT(text_edited(QString)));

    //d
    //connect(ui->lineEdit_4,SIGNAL(focussed(bool)),this,SLOT(resize_and_show_keywidget(bool)));
    //connect(ui->lineEdit_4,SIGNAL(focussed(bool)),keyWid,SLOT(disable_alpha_sym_keys(bool)));

    connect(ui->lineEdit_4,SIGNAL(mouseReleased()),this,SLOT(resize_and_show_keywidget()));
    connect(ui->lineEdit_5,SIGNAL(mouseReleased()),this,SLOT(resize_and_show_keywidget()));

    //connect(ui->lineEdit_5,SIGNAL(focussed(bool)),this,SLOT(resize_and_show_keywidget(bool)));
    //connect(ui->lineEdit_5,SIGNAL(focussed(bool)),keyWid,SLOT(disable_sym_keys(bool)));
    //connect(ui->lineEdit_2,SIGNAL(focussed(bool)),this,SLOT(resize_and_show_keywidget(bool)));
    //connect(ui->lineEdit_2,SIGNAL(focussed(bool)),keyWid,SLOT(enable_all_keys(bool)));
    //connect(ui->lineEdit_3,SIGNAL(focussed(bool)),this,SLOT(resize_and_show_keywidget(bool)));
    //connect(ui->lineEdit_3,SIGNAL(focussed(bool)),keyWid,SLOT(enable_all_keys(bool)));
    //connect(ui->lineEdit,SIGNAL(focussed(bool)),this,SLOT(resize_and_show_keywidget(bool)));
    //connect(ui->lineEdit,SIGNAL(focussed(bool)),keyWid,SLOT(enable_all_keys(bool)));
    connect(ui->Settings,SIGNAL(currentChanged(int)),this,SLOT(tab_changed(int)));
    //QWidget::adjustSize();
    //QWidget::move(QApplication::desktop()->screen()->rect().center() - QWidget::rect().center());
}

PIS_SETTINGS::~PIS_SETTINGS()
{
    delete ui;
}

int PIS_SETTINGS::updateCoach(QStringList info)
{
    QSettings coachsettings("A_Paul_Instruments","COACHID");
    QSettings pissettings("A_Paul_Instruments","PIS");

    coachsettings.setValue("coachID",info.at(0));  // 0-coachID
    pissettings.setValue("ROUTE",info.at(1)); //1-routeNo
    pissettings.setValue("logging",info.at(2)); // 2-gprsLogFrequency

    QString temp = info.at(3);
    QString temp2 = temp.left(2);
    QString temp3 = temp.remove(0,2);

    coachsettings.setValue("CoachAbbrIndex",temp3); //3-coachAbbr eg. 6
    coachsettings.value("CoachAbbrNum",temp2); // coachAbbr eg. CC
    pissettings.value("AnnouncementOntime",info.at(4));
    pissettings.value("AnnouncementOfftime",info.at(5));
    pissettings.value("DisplayParams",info.at(6));
    coachsettings.deleteLater();
    pissettings.deleteLater();

    emit this->selectRoute(info.at(1));
}

void PIS_SETTINGS::on_pushButton_clicked()
{
    this->hide();
}

void PIS_SETTINGS::tab_changed(int index)
{
    if((index > 1))
    {
        //keyWid->hide();
        QWidget::adjustSize();
        QWidget::move(QApplication::desktop()->screen()->rect().center() - QWidget::rect().center());
    }
}

void PIS_SETTINGS::resize_and_show_keywidget()
{
    /*numpad->centerDialogWindow(200,200);
    numpad->show();
    numpad->getData();*/

    //keyWid->move(200,200);
    //keyWid->show();
    //QWidget::adjustSize();
    //1QWidget::move(QApplication::desktop()->screen()->rect().center() - QWidget::rect().center());
}

void PIS_SETTINGS::on_pushButton_2_clicked()
{
    emit StartSimulation(ui->comboBox_3->currentText());
}

void PIS_SETTINGS::text_edited(QString data)
{
    QLineEdit *ex;
    ex = (QLineEdit *)(QApplication::focusWidget());
    QString sr(ex->text());
    if(data == "Del")
    {
        sr.chop(1);
        ex->setText(sr);
    }
    else if(data == "Ent")
    {

    }
    else if(data == "Esc")
    {

    }
    else if(data != "Ent")
    {
        int cursor = ex->cursorPosition();
        sr.insert(cursor,data);
        ex->setText(sr);
    }
}

void PIS_SETTINGS::showEvent(QShowEvent *e)
{
    this->setFixedHeight(QApplication::desktop()->screenGeometry(-1).height()-150);
    this->setFixedWidth(QApplication::desktop()->screenGeometry(-1).width()-150);
    QWidget::move(QApplication::desktop()->screenGeometry(-1).center() - QWidget::rect().center());

    admn->centreDialog();
}

QStringList PIS_SETTINGS::getPISInfoList()
{
    m_mutex.lock();
    QStringList logFields; //25 fields
    logFields.clear();
    logFields.append("Unit_Id");
    logFields.append("Device_Id");
    logFields.append("Coach_Id");
    logFields.append("Train_Id");
    logFields.append("Date");
    logFields.append("Time");
    logFields.append("SIM_Number");
    logFields.append("IMEI_Number");
    logFields.append("Phone_Number");
    logFields.append("IMSI_Number");
    logFields.append("Signal_Strength");
    logFields.append("IP_Address");
    logFields.append("GPRS_Version");
    logFields.append("Software_Version");
    logFields.append("DB_Version");
    logFields.append("Total_Routes_Databse");
    logFields.append("Selected_Route");
    logFields.append("StartJonury_Date");
    logFields.append("StartJonury_Time");
    logFields.append("Logging_Delay");
    logFields.append("Announcement_OnTime");
    logFields.append("Announcement_OffTime");
    logFields.append("Display_Perameters_Info");
    logFields.append("CoachAbbrevition");
    logFields.append("Extra");
    m_mutex.unlock();
    return logFields;

}

QStringList PIS_SETTINGS::getPISInfoData()
{
    m_mutex.lock();
    QStringList logData;
    logData.clear();
    logData.append(UnitID);
    logData.append(CoachID);
    logData.append(CoachID);
    logData.append(QString::fromLatin1(route_path.Header.Route));
    logData.append(QDate::currentDate().toString("dd-MM-yyyy"));
    logData.append(QTime::currentTime().toString("hh:mm:ss"));
    logData.append(gpsData->getSIM_CCID());
    logData.append(gpsData->getModuleIMEI());
    logData.append("1234567890");
    logData.append(gpsData->getSIM_IMSI());
    logData.append(gpsData->getSignalStrength());                       //signal strength
    logData.append("000.000.000.000");        //IP
    logData.append(gpsData->getGPSLibVersion());
    logData.append(LIB_VERSION);
    logData.append(selRouteDBVersion);
    logData.append("00");            //total database routes
    logData.append(QString::fromLatin1(route_path.Header.Route)); //selected route
    logData.append(QString::number(route_path.params.start_date.day).rightJustified(2,'0')+"-"+QString::number(route_path.params.start_date.mon).rightJustified(2,'0')+"-20"+QString::number(route_path.params.start_date.yrs).rightJustified(2,'0'));     //Journey start date
    logData.append(QString::number(route_path.params.start_time.hrs).rightJustified(2,'0')+":"+QString::number(route_path.params.start_time.min).rightJustified(2,'0')+":"+QString::number(route_path.params.start_time.sec).rightJustified(2,'0'));
    logData.append(QString::number(loggingFrequency));
    logData.append(QString::number(announcement_on_time.hour()));
    logData.append(QString::number(announcement_off_time.hour()));
    logData.append("10");      //display parameters
    logData.append(CoachAbbrb);
    logData.append("0");
    m_mutex.unlock();
    return logData;

}

void PIS_SETTINGS::on_save_clicked()
{
    qDebug("Save clicked ");
    QSettings coachsettings("A_Paul_Instruments","COACHID");
    QSettings pissettings("A_Paul_Instruments","PIS");
    QDate date;
    QTime time;
    QString date_update;
    switch(ui->Settings->currentIndex())
    {
        case 0:
            CoachID = coachsettings.value("coachID").toString();
            CoachAbbrIndex = coachsettings.value("CoachAbbrIndex").toInt();
            CoachAbbr = coachsettings.value("CoachAbbrNum").toString();
            //if(button->text() == "Save")
            {
                coachsettings.setValue("coachID",ui->lineEdit_5->text());
                coachsettings.setValue("CoachAbbrIndex",QString::number(ui->comboBox->currentIndex()));
                coachsettings.setValue("CoachAbbrNum",ui->lineEdit_4->text());
                coachsettings.setValue("CoachAbbr",ui->comboBox->currentText() + ui->lineEdit_4->text());
                coachsettings.sync();
            }
            /*else
            {
                ui->comboBox->setCurrentIndex(CoachAbbrIndex);
                ui->lineEdit_4->setText(CoachAbbr);
                ui->lineEdit_5->setText(CoachID);
            }*/
            break;
        case 1:
            ServerIP = pissettings.value("ServerIP").toString();
            ServerPortASync = pissettings.value("ServerPortAsync").toString();
            ServerPortSync = pissettings.value("ServerPortSync").toString();
            //if(button->text() == "Save")
            {
                pissettings.setValue("ServerIP",ui->lineEdit->text());
                pissettings.setValue("ServerPortAsync",ui->lineEdit_2->text());
                pissettings.setValue("ServerPortSync",ui->lineEdit_3->text());
                pissettings.sync();
            }
            /*else
            {
                ui->lineEdit->setText(ServerIP);
                ui->lineEdit_2->setText(ServerPortASync);
                ui->lineEdit_3->setText(ServerPortSync);
            }*/
            break;
        case 3:
            date = ui->dateEdit->date();
            time = ui->timeEdit->time();
            date_update = "sudo date -u "+ QString::number(date.month()).rightJustified(2,'0') + QString::number(date.day()).rightJustified(2,'0')+QString::number(time.hour()).rightJustified(2,'0')+QString::number(time.minute()).rightJustified(2,'0')+QString::number(date.year()).rightJustified(4,'0')+"."+QString::number(time.second()).rightJustified(2,'0');
            system(date_update.toStdString().c_str());
            break;
        case 4:
            en_speed_display = pissettings.value("Speed").toBool();
            en_destination_board = pissettings.value("DestinationBoard").toBool();
            en_logging = pissettings.value("logging").toBool();
            en_safety_slogans = pissettings.value("SafetySlogans").toBool();
            en_announcement = pissettings.value("Announcement").toBool();
            //if(button->text() == "Save")
            {
                pissettings.setValue("Speed",ui->checkBox->isChecked());
                pissettings.setValue("DestinationBoard",ui->checkBox_8->isChecked());
                pissettings.setValue("logging",ui->checkBox_3->isChecked());
                pissettings.setValue("SafetySlogans",ui->checkBox_4->isChecked());
                pissettings.setValue("Announcement",ui->checkBox_6->isChecked());
                pissettings.sync();
            }
            /*else
            {
                ui->checkBox->setChecked(en_speed_display);
                ui->checkBox_8->setChecked(en_destination_board);
                ui->checkBox_3->setChecked(en_logging);
                ui->checkBox_4->setChecked(en_safety_slogans);
                ui->checkBox_6->setChecked(en_announcement);
            }*/
            break;
        case 5:
            announcement_on_time = pissettings.value("AnnouncementOntime").toTime();
            announcement_off_time = pissettings.value("AnnouncementOfftime").toTime();
            loggingFrequency = pissettings.value("loggingFrequency").toInt();
            //if(button->text() == "Save")
            {
                pissettings.setValue("AnnouncementOntime",ui->timeEdit_2->time());
                pissettings.setValue("AnnouncementOfftime",ui->timeEdit_3->time());
                pissettings.setValue("loggingFrequency",ui->comboBox_2->currentIndex());
                pissettings.sync();
                loggingFrequencyTime = ui->comboBox_2->itemText(loggingFrequency).toInt();
            }
           /* else
            {
                ui->comboBox_2->setCurrentIndex(loggingFrequency);
                ui->timeEdit_2->setTime(announcement_on_time);
                ui->timeEdit_3->setTime(announcement_off_time);
            }*/
            break;
    }
}

void PIS_SETTINGS::on_close_clicked()
{
    qDebug("Closing Window");
    this->close();
}

void PIS_SETTINGS::on_comboBox_2_currentIndexChanged(int index)
{
    emit this->changeLogFreq(index);
}
