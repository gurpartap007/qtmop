
#include "route_selection.h"

QSqlDatabase  pis_db,db2,db3;
//QString new_data; // RouteDBVersion

route_selection::route_selection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::route_selection)
{
    ui->setupUi(this);
    qDebug("\nSetting up Route Selection ...\n");
    this->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::X11BypassWindowManagerHint|Qt::FramelessWindowHint);
    ui->lineEdit->showNumKeysOnly();

//    triggersIndex=0;
//    QSettings settings("A. Paul Instruments Pvt. Ltd.","BUS_PIS");
//    logTimer = new QTimer;
//    connect(logTimer,SIGNAL(timeout()),this,SLOT(logData()));
//    logTimer->start(settings.value("LogFrequency").toInt()*1000*60);
 //dilip   ui->horizontalLayout_2->addWidget(keyWid);
    configure_database();
//    connect(&futureWatcher,SIGNAL(started()),this,SLOT(logThreadStatus()));
//    connect(&futureWatcher,SIGNAL(finished()),this,SLOT(logThreadStatus()));
//    connect(ui->lineEdit,SIGNAL(mouseReleased()),this,SLOT(updateLine()));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(lineedit_filtering(QString)));
    connect(this, SIGNAL(lineedit_filter(QString)), proxyModel, SLOT(setFilterRegExp(QString)));
    //connect(keyWid,SIGNAL(keyPressed(QString)),this,SLOT(key_process(QString)));
   //d connect(keyPad,SIGNAL(value_changed(char)),this,SLOT(key_process(char)));
    QSettings pissettings("A_Paul_Instruments","PIS");
    QString Route = pissettings.value("ROUTE").toString();
//    route_path.Header.Route = pissettings.value("ROUTE").toString().toStdString().c_str();
    QSqlQuery query1(QSqlDatabase::database("Connection1"));
    query1.exec("SELECT * FROM `tbl_TrainMaster` where `train_Number` = '" + Route + "'");
    qDebug() << query1.lastQuery();
    if(query1.next())
    {
        memcpy(route_path.Header.Route,pissettings.value("ROUTE").toString().toStdString().c_str(),pissettings.value("ROUTE").toString().size());
        create_working_route_log();
    }
//    //connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(combobox_filtering(QString)));
//    //connect(this, SIGNAL(combobox_filter(QString)), proxyModel, SLOT(setFilterRegExp(QString)));
 //   connect(&keyWid, SIGNAL(value_changed(char)), this, SLOT(key_process(char)));

    //QtConcurrent::run(threadPool,this,&route_selection::connectRemoteDatabase);
    updateDatabaseVersion();
}

route_selection::~route_selection()
{
    delete ui;
}

void route_selection::updateLine()
{

}

//void route_selection::showEvent(QShowEvent *event)
//{
//    emit this->stopCamera();
//   // QTimer::singleShot(100,this,SLOT(askForDriverID()));
//   // event->accept();
//}

//void route_selection::askForDriverID()
//{
//   ID.centreDialog(this->width()/2,100);
//    ID.exec();
//}
//QWidget::move(QApplication::desktop()->screen()->rect().center() - QWidget::rect().center());


void route_selection::configure_database()
{
    qDebug("\nConfiguring Database ...\n");
    QString old_data,new_data;
    QString old_file = "/home/apaul/files/database_version.txt.old";
    QString new_file = "/home/apaul/files/database_version.txt";
    QFile file(old_file);
    QTextStream in(&file);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "could not open /home/apaul/files/database_version.txt.old file for reading";
        old_data = "0.0";
    }
    else
    {
        old_data = in.readLine();
        file.close();
    }
   QFile file2(new_file);
   QTextStream in2(&file2);
   if(!file2.open(QIODevice::ReadOnly | QIODevice::Text))
   {
        qDebug() << "could not open /home/apaul/files/database_version.txt file for reading";
        new_data = "1.0";
   }
   else
   {
      new_data = in2.readLine();
      file2.close();
   }

    /** CONNECTING TO DATABASE BUS_PIS */
    pis_db = QSqlDatabase::addDatabase("QMYSQL","Connection1");
    pis_db.setHostName("localhost");
    pis_db.setDatabaseName("PIS_WEB");
    pis_db.setUserName("root");
    pis_db.setPassword("apaul");
    bool ok = pis_db.open();
    qDebug() << "database" << ok;

    /** CHECK DATABASE VERSION */
    if(old_data.toFloat() < new_data.toFloat())
    {
        QFile file3 ("/home/apaul/working_route.txt");
        //upload_database_file(file3);
        file.remove();
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "could not open /home/apaul/database_version.txt.old file for reading";
            return;
        }
        QTextStream out(&file);
        out << new_data;         /** writting new version no to old file */
        file.close();

        /** Calling the same function again so that it may connect to newly updated database correctly */
        route_selection::configure_database();
    }

    /** QSQlTableModel offers a read-write model that works on a single SQL table at a time. */
    QSqlTableModel *model = new QSqlTableModel(this, pis_db);
    model->setTable(PATH_MASTER_TABLE);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    proxyModel = new QSortFilterProxyModel;
    proxyModel->setSourceModel(model);
    /** SETTING UP DATA IN TABLEVIEW */
    ui->tableView->setModel(proxyModel);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->hide();
    ui->tableView->hideColumn(2);
    ui->tableView->hideColumn(1);
    ui->tableView->hideColumn(3);
    ui->tableView->hideColumn(4);
    ui->tableView->hideColumn(5);
    ui->tableView->hideColumn(7);
    ui->tableView->hideColumn(8);
    ui->tableView->hideColumn(9);
    ui->tableView->hideColumn(6);
    ui->tableView->hideColumn(11);
    ui->tableView->hideColumn(12);
    ui->tableView->hideColumn(13);
    ui->tableView->hideColumn(14);
    ui->tableView->hideColumn(15);
    ui->tableView->hideColumn(16);
    ui->tableView->hideColumn(17);
    ui->tableView->hideColumn(18);
    ui->tableView->hideColumn(19);
    ui->tableView->hideColumn(31);
//    ui->tableView->setShowGrid(false);
    ui->tableView->sortByColumn(0, Qt::AscendingOrder);
//
//    ui->tableView->setColumnWidth(10,760);
//    ui->tableView->resizeColumnToContents(0);
//    ui->tableView->resizeColumnToContents(10);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setColumnWidth(0,200);
    ui->tableView->verticalHeader()->setDefaultSectionSize(80);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

//void route_selection::connectRemoteDatabase()
//{
//    /** CONNECTING TO DATABASE BUS_PIS_LOG */

//    qDebug()<<"Trying to connect to local and remote database for BUS_PIS_LOG";
//    db2 = QSqlDatabase::addDatabase("QMYSQL","Connection2");
//    db2.setHostName("localhost");
//    db2.setDatabaseName("BUS_PIS_LOG");
//    db2.setUserName("root");
//    db2.setPassword("apaul");

//    bool ok = db2.open();
//    if(ok)
//        qDebug("Opened BUS-PIS_LOG database successfully.");
//    else
//    {
//        qDebug("Can not BUS-PIS_LOG database. Trying to create a new one.");
//    }

//        /** CONNECTING TO DATABASE BUS_PIS_LOG ON SQL SERVER */
//        db3 = QSqlDatabase::addDatabase("QTDS","Connection3");
//        db3.setHostName("192.168.0.14");
//        db3.setDatabaseName("test");
//        db3.setUserName("sa");
//        db3.setPassword("apaul@2003");

//        ok = db3.open();
//        if(ok)
//            qDebug("Opened remote BUS-PIS_LOG  server database successfully.");
//        else
//        {
//            qDebug("Can not open remote BUS-PIS_LOG database. Trying to create a new one.");
//        }
//}

void route_selection::upload_database_file(QString filePath)
{
    QFile file(filePath);
    QTextStream in(&file);
    QString file_data;
    qDebug("\nUpdating Database...\n");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Could not open"<<filePath<<"for reading";
        return;
    }

    while(!in.atEnd())
    {
        file_data = in.readLine();
        QSqlQuery query(file_data,pis_db);
    }
    file.close();
}

void route_selection::create_working_route_log(void)
{
       qDebug("Route.cpp forming database ..");
       qint16 stop_number = 0;
       QStringList datalist;
       route_path.params.start_time.hrs = QTime::currentTime().hour();
       route_path.params.start_time.min = QTime::currentTime().minute();
       route_path.params.start_time.sec = QTime::currentTime().second();
       route_path.params.start_date.day = QDate::currentDate().day();
       route_path.params.start_date.mon = QDate::currentDate().month();
       int year = QDate::currentDate().year();
       route_path.params.start_date.yrs = QDate::currentDate().year()%100;

       QSqlQuery query1(QSqlDatabase::database("Connection1"));
       query1.exec(GET_PATH_CODE_DATA_FROM_PATH_ROUTE_TABLE_FOR_ROUTE(QString::fromLatin1(route_path.Header.Route),QString::fromLatin1(route_path.Header.Route)));
       qDebug() << query1.lastQuery();
       while(query1.next())
       {
           datalist.clear();
           QSqlRecord record = query1.record();
           for(int i=0; i < record.count(); i++)
               datalist << record.value(i).toString();


           route_path.Header.distance = datalist[JOURNEY_DISTANCE].toFloat();
           uword temp_lat_long1, temp_lat_long2;

           memset(route_path.Stops[stop_number].info.Code, '\0', DIG_STN_CODE);
           memcpy(route_path.Stops[stop_number].info.Code, datalist[STOP_CODE].toStdString().c_str(), datalist[STOP_CODE].size());
           route_path.Stops[stop_number].info.distance_frm_src = datalist[DISTANCE_FROM_SOURCE].toFloat();

           route_path.Stops[stop_number].info.latit = datalist[LAT].toFloat();
           temp_lat_long1 = (uword)(route_path.Stops[stop_number].info.latit*10000);
           temp_lat_long2 = (temp_lat_long1/1000000)*60*10000;
           temp_lat_long2 += (temp_lat_long1%1000000);
           route_path.Stops[stop_number].info.latit = (float)temp_lat_long2;

           route_path.Stops[stop_number].info.longit = datalist[LONG].toFloat();
           temp_lat_long1 = (uword)(route_path.Stops[stop_number].info.longit*10000);
           temp_lat_long2 = (temp_lat_long1/1000000)*60*10000;
           temp_lat_long2 += (temp_lat_long1%1000000);
           route_path.Stops[stop_number].info.longit = (float)temp_lat_long2;
           route_path.Stops[stop_number].info.entry_peri = datalist[ENTRY_PERI].toInt();
           route_path.Stops[stop_number].info.exit_peri = datalist[EXIT_PERI].toInt();
           route_path.Stops[stop_number].info.approaching_peri = 1000;
           QString str = datalist[INCLUDED_IN_VIA];
           QByteArray str_b(str.toStdString().c_str());
           route_path.Stops[stop_number].info.included_in_via_list = str_b[0];
           memset(route_path.Stops[stop_number].info.station_name[0], '\0', DIG_STN_NAME);
           memcpy(route_path.Stops[stop_number].info.station_name[0], datalist[STOP_NAME_ENG].toStdString().c_str(), datalist[STOP_NAME_ENG].size());
           memset(route_path.Stops[stop_number].info.station_name[1], '\0', DIG_STN_NAME);
           memcpy(route_path.Stops[stop_number].info.station_name[1], datalist[STOP_NAME_HIN].toStdString().c_str(), datalist[STOP_NAME_HIN].size());
           memset(route_path.Stops[stop_number].info.station_name[2], '\0', DIG_STN_NAME);
           memcpy(route_path.Stops[stop_number].info.station_name[2], datalist[STOP_NAME_REG1].toStdString().c_str(), datalist[STOP_NAME_REG1].size());
           memset(route_path.Stops[stop_number].info.station_name[3], '\0', DIG_STN_NAME);
           memcpy(route_path.Stops[stop_number].info.station_name[3], datalist[STOP_NAME_REG2].toStdString().c_str(), datalist[STOP_NAME_REG2].size());
           memset(route_path.Stops[stop_number].info.station_name[4], '\0', DIG_STN_NAME);
           memcpy(route_path.Stops[stop_number].info.station_name[4], datalist[STOP_NAME_REG3].toStdString().c_str(), datalist[STOP_NAME_REG3].size());
           route_path.Stops[stop_number].info.regional_lngugage = datalist[REGIONAL_LANG].toInt();
           memset(route_path.Header.Description[0], '\0', DIG_MAX_PATH_DESC_LEN);
           memcpy(route_path.Header.Description[0], datalist[TRAIN_NAME_ENG].toStdString().c_str(),datalist[TRAIN_NAME_ENG].size());
           memset(route_path.Header.Description[1], '\0', DIG_MAX_PATH_DESC_LEN);
           memcpy(route_path.Header.Description[1], datalist[TRAIN_NAME_HIN].toStdString().c_str(),datalist[TRAIN_NAME_HIN].size());
           memset(route_path.Header.Description[2], '\0', DIG_MAX_PATH_DESC_LEN);
           memcpy(route_path.Header.Description[2], datalist[TRAIN_NAME_REG1].toStdString().c_str(),datalist[TRAIN_NAME_REG1].size());
           memset(route_path.Header.Description[3], '\0', DIG_MAX_PATH_DESC_LEN);
           memcpy(route_path.Header.Description[3], datalist[TRAIN_NAME_REG2].toStdString().c_str(),datalist[TRAIN_NAME_REG2].size());
           stop_number++;
       }
       strcpy(route_path.Header.comma[0],",");
       strcpy(route_path.Header.comma[1],",");
       strcpy(route_path.Header.comma[2],",");
       strcpy(route_path.Header.comma[3],",");
       strcpy(route_path.Header.to[0]," TO ");
       strcpy(route_path.Header.to[1]," TO ");
       strcpy(route_path.Header.to[2]," TO ");
       strcpy(route_path.Header.to[3]," TO ");
       strcpy(route_path.Header.via[0]," VIA ");
       strcpy(route_path.Header.via[1]," VIA ");
       strcpy(route_path.Header.via[2]," VIA ");
       strcpy(route_path.Header.via[3]," VIA ");
       strcpy(route_path.Header.welcome_message[0],"Welcome to Indian Railways");
       strcpy(route_path.Header.welcome_message[1],"Welcome to Indian Railways");
       strcpy(route_path.Header.welcome_message[2],"Welcome to Indian Railways");
       strcpy(route_path.Header.welcome_message[3],"Welcome to Indian Railways");
       strcpy(route_path.Header.Source_station_name[0],route_path.Stops[0].info.station_name[0]);
       strcpy(route_path.Header.Source_station_name[1],route_path.Stops[0].info.station_name[1]);
       strcpy(route_path.Header.Source_station_name[2],route_path.Stops[0].info.station_name[2]);
       strcpy(route_path.Header.Source_station_name[3],route_path.Stops[0].info.station_name[3]);
       strcpy(route_path.Header.Destination_station_name[0],route_path.Stops[stop_number - 1].info.station_name[0]);
       strcpy(route_path.Header.Destination_station_name[1],route_path.Stops[stop_number - 1].info.station_name[1]);
       strcpy(route_path.Header.Destination_station_name[2],route_path.Stops[stop_number - 1].info.station_name[2]);
       strcpy(route_path.Header.Destination_station_name[3],route_path.Stops[stop_number - 1].info.station_name[3]);
       strcpy(route_path.Header.Source_Stop, route_path.Stops[stop_number - 1].info.Code);
       strcpy(route_path.Header.Destination_Stop, route_path.Stops[0].info.Code);
       route_path.Header.no_of_stns = stop_number;
       route_path.Curr_stop = 0;
       route_path.Next_stop = 0;
       route_path.Prev_stop = -1;
       route_path.status.bits.route_info_avail = 1;
       QString link_trains;
        QSqlQuery query2(QSqlDatabase::database("Connection1"));
       query2.exec("SELECT * FROM `tbl_train_link`");
       qDebug() << query2.lastQuery();
       while(query2.next())
       {
           int i;
           QSqlRecord record = query2.record();
           link_trains = record.value(0).toString();
           qDebug()<<link_trains;
           QStringList list = link_trains.split("/");
           for(i=0;i<list.size();i++)
           {
               if(list[i] == QString::fromLatin1(route_path.Header.Route))
               {
                   qDebug()<<list[i]<<list.size();
                   memset(route_path.Header.LinkRoute, '\0', DIG_MAX_ROUTE_NUM_LEN);
                   if(i != (list.size()-1))
                       memcpy(route_path.Header.LinkRoute, list[i+1].toStdString().c_str(), list[i+1].size());
                   else
                       memcpy(route_path.Header.LinkRoute, list[0].toStdString().c_str(), list[0].size());
                   return;
               }
           }
       }
}

void route_selection::key_process(QString key_text)
{
    if(key_text == "Ent")
    {

    }
    else if(key_text == "Del")
    {
        QString sr(ui->lineEdit->text());
        sr.chop(1);
        ui->lineEdit->setText(sr);
    }
    else if(key_text == "Esc")
    {

    }
    else
    {
        ui->lineEdit->setText(ui->lineEdit->text()+key_text);
    }
}

void route_selection::lineedit_filtering(QString value)
{
    qDebug("route_selection: filtering data ...");
    proxyModel->setFilterKeyColumn(0);
    emit this->lineedit_filter(value);
}

//void route_selection::combobox_filtering(QString value)
//{
//    proxyModel->setFilterKeyColumn(5);
//    QString temp_value = value.right(5);
//    emit this->combobox_filter(temp_value);
//}

//void route_selection::logData()
//{
//    qDebug()<<"Ruunning logData()...";
//    // futureWatcher.setFuture(QtConcurrent::run(threadPool,this,&route_selection::localRun,QString("Periodic")));

//    localRun("Periodic");
//}

//void route_selection::localRun(QString trigger)
//{
//    QSqlQuery query( QSqlDatabase::database("Connection2"));
//    if(query.exec(CREATE_BUS_PIS_LOG))
//        qDebug("opened database...");
//    if(query.exec("USE BUS_PIS_LOG;"))
//        qDebug("created table");
//    if(query.exec(CREATE_TABLE))
//        qDebug("created table");
//    qDebug()<<query.executedQuery();

//    QString Id="0",BusNo="3456",DriverId="RT5678",DepartureTime="10:20",ArrivalTime="10:50";
//    QString lat,llong;
//    lat = latLongToQString(gps_packet.data.cpu.latit);
//    llong = latLongToQString(gps_packet.data.cpu.longit);
//    /* GMT unix timeStamp */
//    uint date = (QDateTime::currentMSecsSinceEpoch()/1000);

//    qDebug()<<"lat:"<<lat<<"long:"<<llong;

//    QString cmd=QString("INSERT INTO log(")+"BusNo,"+"DriverId,"+"Route,"\
//            +"RouteDBVersion,"+"SourceStop,"+"DestinationStop,"+"DepartureTime,"\
//            +"ArrivalTime,"+"NextStop,"+"CurrentTime,"+"CurrentLatitude,"+"CurrentLongitude,"\
//            +"CurrentSpeed,"+"Input_1,"+"Input_2,"+"Input_3,"+"Input_4,"\
//            +"Output_1,"+"Output_2,"+"Slave_1,"+"Slave_2,"+"Slave_3,"+"Slave_4,"\
//            +"Slave_5,"+"Slave_6,"+"Slave_7,"+"Slave_8,"+"Slave_9,"+"Slave_10,"\
//            +"Event) VALUES ("+"\'"
//    +BusNo+"','"+DriverId\
//    +"','"+route_path.Header.Route+"','"+new_data\
//    +"','"+route_path.Header.Source_Stop\
//    +"','"+route_path.Header.Destination_Stop\
//    +"','"+DepartureTime+"','"+ArrivalTime\
//    +"','"+route_path.Stops[route_path.Next_stop].info.station_name[0]\
//    +"','"+QString::number(date)\
//    +"','"+lat\
//    +"','"+llong\
//    +"','"+QString::fromUtf16((ushort*)gps_packet.data.speed)\
//    +"','"+VHS.revCam\
//    +"','"+VHS.frontDoor\
//    +"','"+VHS.backDoor\
//    +"','"+VHS.emerDoor\
//    +"','"+VHS.emerDoor\
//    +"','"+VHS.emerDoor\
//    +"','"+VHS.slave[0]+"','"+VHS.slave[1]+"','"+VHS.slave[2]+"','"+VHS.slave[3]+"','"+VHS.slave[4]+"','"+VHS.slave[5]\
//    +"','"+VHS.slave[6]+"','"+VHS.slave[7]+"','"+VHS.slave[8]+"','"+VHS.slave[9]+"','"+trigger+"\');";

//    qDebug()<<"Log Command:"<<cmd;
//    query.exec(cmd);

//    /*****************SQL server*******************/

//    QSqlQuery querym( QSqlDatabase::database("Connection3"));
//    qDebug()<<"server:"<<CREATE_BUS_PIS_LOG_SERVER;

//    if(querym.exec(CREATE_BUS_PIS_LOG_SERVER))
//        qDebug("opened database...");

//    if(querym.exec("USE BUS_PIS_LOG;"))
//        qDebug("created table");

//    qDebug()<<"server:"<<CREATE_SERVER_TABLE;
//    if(querym.exec(CREATE_SERVER_TABLE))
//        qDebug("created table");
    
//    querym.exec(cmd);
//}

//QString route_selection::latLongToQString(float latLong)
//{
//    unsigned int deg,min;
//    float temp;
//    deg=(latLong/600000);
//    temp=(float)((float)latLong/10000 - (float)deg*60);
//    deg*=100;
//    deg+=temp;
//    min=((temp-(unsigned int)temp)*10000);
//    return QString::number(deg)+"."+QString::number(min);
//}

//void route_selection::logThreadStatus()
//{
//    if(futureWatcher.isRunning())
//        qDebug()<<"Logging Started...";
//    if(futureWatcher.isFinished())
//        qDebug()<<"Logging Done...";
//}

//void route_selection::changeLogFrequency(int i)
//{
//    if(i>4)
//    {
//        logTimer->stop();
//        logTimer->start(i*1000*60);
//    }
//}

void route_selection::on_lineEdit_returnPressed()
{
    qDebug("Route Selected ...");
    if(ui->tableView->currentIndex().row() == -1)
    {
        qDebug("No Route Selected ...");
        ui->tableView->selectRow(0);
    }
    if(ui->tableView->selectionModel()->currentIndex().row() >= 0)
    {
        /*********************************************************Route header parameters*********************************************************************************************************/
        memset(route_path.Header.Route, '\0', DIG_MAX_ROUTE_NUM_LEN);
        memcpy(route_path.Header.Route, ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->selectionModel()->currentIndex().row(),PIS_DB_ROUTE_NUM_INDEX)).toString().toStdString().c_str(), ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->selectionModel()->currentIndex().row(),PIS_DB_ROUTE_NUM_INDEX)).toString().size());

        /***********************************************ROUTE INFORMATION(WORKING LOG)***********************************************************/
        create_working_route_log();
        emit route_selected(ROUTE_SELECTED,NULL);
    }
}

void route_selection::on_tableView_doubleClicked(const QModelIndex &index)
{
    if(ui->tableView->selectionModel()->currentIndex().row() >= 0)
    {
        /*********************************************************Route header parameters*********************************************************************************************************/
        memset(route_path.Header.Route, '\0', DIG_MAX_ROUTE_NUM_LEN);
        memcpy(route_path.Header.Route, ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->selectionModel()->currentIndex().row(),PIS_DB_ROUTE_NUM_INDEX)).toString().toStdString().c_str(), ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->selectionModel()->currentIndex().row(),PIS_DB_ROUTE_NUM_INDEX)).toString().size());

        /***********************************************ROUTE INFORMATION(WORKING LOG)***********************************************************/
        create_working_route_log();
        emit route_selected(ROUTE_SELECTED,NULL);
    }
}

int route_selection::selectCurrentRoute(QString trainNo)
{
    int i=0;
    QString trains;
    QSqlRecord record;
    QSqlQuery query(QSqlDatabase::database("Connection1"));  //connection for PIS_WEB
    query.exec("SELECT `train_Number` FROM `tbl_TrainMaster`");
    qDebug() << query.lastQuery();
    while(query.next())
    {
       record = query.record();
       i=record.count();
       for(int j=0;j<i;j++)
       {
            trains = record.value(j).toString();
            qDebug()<<"Train Routes ........:"<<trains;
            if(trains == trainNo)
            goto select;
       }
    }

    return 1; //No existing route matched

    select:
    memset(route_path.Header.Route, '\0', DIG_MAX_ROUTE_NUM_LEN);
    memcpy(route_path.Header.Route,trainNo.toStdString().c_str(),trainNo.size());

    /****ROUTE INFORMATION(WORKING LOG)*********/

    create_working_route_log();
    emit route_selected(ROUTE_SELECTED,NULL);

    return 0; //Route selected successfully
}

void route_selection::updateDatabaseVersion()
{
    QSqlQuery query(pis_db);
    query.exec("SELECT database_version FROM `tbl_pis_route` WHERE train_number=12049 order by database_version desc limit 1");
    if(query.next())
            selRouteDBVersion = query.value(0).toString();
    qDebug() << "Database Version for current Route:" << selRouteDBVersion;
}
