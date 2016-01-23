#include "route_selection.h"
#include "ui_route_selection.h"
QString selected_train_no;
int selected_train;
QStringList train_routes;
extern char display[20];
extern char *ptr;
extern QSqlDatabase db;
route_selection::route_selection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::route_selection)
{
    ui->setupUi(this);
    train_selection_keyboard = new keyboard(this);
    train_database = new database(this);
    // current_route->hide();
    master_trains_model = new QSqlTableModel(this,db);
    slave_trains_model = new QSqlTableModel(this,db);
    dummy_model = new QSqlTableModel;
    proxyModel = new QSortFilterProxyModel;
    current_route = new train_route(&db);
    ui->stackedWidget->addWidget(train_selection_keyboard);
    ui->stackedWidget->setCurrentWidget(train_selection_keyboard);
    connect(train_selection_keyboard,SIGNAL(value_changed(char)),this,SLOT(settext(char)));
    connect(this,SIGNAL(train_selected()),current_route,SLOT(current_selected_train_info()));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(lineedit_filtering(QString)));
    connect(this, SIGNAL(lineedit_filter(QString)), proxyModel, SLOT(setFilterRegExp(QString)));
    train_selection_keyboard->on_pushButton_31_clicked();
    select_train_route_with_sorting();

}
route_selection::~route_selection()
{
    delete ui;
    delete train_selection_keyboard;
    delete train_database;
    delete master_trains_model;
    delete slave_trains_model;
    delete proxyModel;

}
void route_selection::settext(char value)
{
    int route_count=0;
    if(value == ENTER_CLICK)
    {
        qDebug() << train_routes;
        while(train_routes[route_count]!=NULL)
        {
            if(strcmp(display,train_routes[route_count].toUtf8().constData()))
            {
                ui->lineEdit->clear();
                ui->lineEdit->setText("Invalid Train Route");
                ui->lineEdit->setStyleSheet("QLineEdit { background-color: rgb(255,0,0); }");
            }
            else
            {
                emit train_selected();
                break;
            }
            ++route_count; extern QString selected_train_no;
        }
        while(ptr != &display[0])
        {
            ptr--;
            *ptr = '\0';
        }

    }
    else
    {
        ui->lineEdit->setStyleSheet("QLineEdit { background-color: rgb(235,235,235); }");
        ui->lineEdit->setText(QString::fromUtf8(display));

    }
}

void route_selection::route_window()
{
    ui->backButton->hide();
    ui->lineEdit->hide();
    ui->select_route_label->hide();
    ui->stackedWidget->setCurrentWidget(current_route);
}

void route_selection::select_train_route_with_sorting()
{
    int loop_count=0,
            train_count;
    QFont header_font;
    QStringList master_train_no_for_current_slave_train;
    QStringList labels,datalist,slave_train_no,master_trains_for_slave_trains,master_train_names;
    //QSqlRecord record_master_train_for_slave_trian,record_master_train_name;
    model= new QStandardItemModel(0,0);
    header_font.setPointSize(20);
    header_font.setFamily("Garuda");
    master_trains_model->setTable("tbl_TrainNumber");
    slave_trains_model->setTable("tbl_slave_route");
    slave_trains_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    slave_trains_model->select();
    slave_trains_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    master_trains_model->select();

    labels.append("Train_no");
    labels.append("Train_name");
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setFont(header_font);
    QList <QStandardItem *> rowData;
    QList <QStandardItem *> ColumnData;


    //////////////////// Inserting Master Train numbers ///////////////////////////
    for(loop_count=0;loop_count<master_trains_model->rowCount();loop_count++)
    {

        //ColumnData << new QStandardItem(QString("1001"));
        ColumnData << new QStandardItem(master_trains_model->data(master_trains_model->index(loop_count,TABLE_TRAIN_NUMBER::TRAIN_NO)).toString());
        // qDebug() << master_trains_model->data(master_trains_model->index(loop_count,TABLE_TRAIN_NUMBER::TRAIN_NO)).toString();
    }
    //---------------------------------------------------------------------------//

    //////////////////// Inserting Slave Train numbers ////////////////////////////

    for(loop_count=0;loop_count<slave_trains_model->rowCount();loop_count++)
    {

        //ColumnData << new QStandardItem(QString("1001"));
        ColumnData << new QStandardItem(slave_trains_model->data(slave_trains_model->index(loop_count,TABLE_TRAIN_NUMBER::TRAIN_NO)).toString());
        //qDebug() << slave_trains_model->data(slave_trains_model->index(loop_count,TABLE_TRAIN_NUMBER::TRAIN_NO)).toString();
    }
    model->insertColumn(0,ColumnData);
    ColumnData.clear();
    //---------------------------------------------------------------------------//

    ///////////////////// Finding Master Trains for Slave Trains ///////////////////
    for(train_count=0;train_count<slave_trains_model->rowCount();train_count++)
    {
        slave_train_no << slave_trains_model->data(slave_trains_model->index(train_count,TABLE_TRAIN_NUMBER::TRAIN_NO)).toString();
        QSqlQuery find_master_train("SELECT `master_route` FROM `tbl_slave_route` where `train_number`='"+ slave_train_no.at(train_count) + "'");
        find_master_train.next();
     //   record_master_train_for_slave_trian = find_master_train.record();
        master_train_no_for_current_slave_train.append(find_master_train.value(0).toString());
        // qDebug() << "MASTER TRAIN NAME" <<  master_train_no_for_current_slave_train << "of slave train: " << slave_train_no.at(train_count) ;
        find_master_train.clear();
        //record_master_train_for_slave_trian.clear();
    }
    qDebug() << slave_train_no;
    qDebug() << master_train_no_for_current_slave_train;
    //-------------------------------------------------------------------------------------//
    //////////// Extract master train Name from Master Train Number /////////////////////////
    for(train_count=0;train_count<master_train_no_for_current_slave_train.size();train_count++)
    {
        QSqlQuery find_master_train_name("SELECT `tran_name_english` FROM `tbl_TrainNumber` where `train_no`='"+ master_train_no_for_current_slave_train.at(train_count) + "'");
        find_master_train_name.next();
        //record_master_train_name = find_master_train_name.record();
        master_train_names.append(find_master_train_name.value(0).toString());
    }
    //-------------------------------------------------------------------------------------//

    //////////////////// Inserting Master Train Names //////////////////////////////

    for(loop_count=0;loop_count<master_trains_model->rowCount();loop_count++)
    {

        //ColumnData << new QStandardItem(QString("1001"));
        ColumnData << new QStandardItem(master_trains_model->data(master_trains_model->index(loop_count,TABLE_TRAIN_NUMBER::TRAIN_NAME_ENG)).toString());
        // qDebug() << master_trains_model->data(master_trains_model->index(loop_count,TABLE_TRAIN_NUMBER::TRAIN_NAME_ENG)).toString();
    }
    for(loop_count=0;loop_count<master_train_names.size();loop_count++)
    {
        ColumnData << new QStandardItem(master_train_names.at(loop_count));

    }
    qDebug() << "LEEENGTHHHHH...." << master_train_names;
    model->insertColumn(1,ColumnData);
    ColumnData.clear();
    model->setHorizontalHeaderLabels(labels);
    proxyModel->setSourceModel(model);
    ui->tableView->setModel(proxyModel);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    QHeaderView *verticalHeader = ui->tableView->verticalHeader();
    verticalHeader->sectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(40);
    ui->backButton->hide();

}
void route_selection::on_backButton_clicked()
{
    while(ptr != &display[0])
    {
        ptr--;	//decrementing write pointer
        *ptr = '\0';
    }
    ui->lineEdit->setText(QString::fromUtf8(display));
    ui->stackedWidget->setCurrentWidget(train_selection_keyboard);
    this->close();
}
void route_selection::lineedit_filtering(QString value)
{
    //SEARCH FILTERING FOR DESTINATION
    proxyModel->setFilterKeyColumn(0);
    emit this->lineedit_filter(value);
}

void route_selection::on_tableView_clicked(const QModelIndex &index)
{
    QStringList source_destination_station_codes;
    QString source_station_name;
    QString destination_station_name;
   // QSqlRecord record_destination_station_name;
    bool train_is_slave=false;
    selected_train = ui->tableView->selectionModel()->currentIndex().row();
    qDebug() << "selected train no = " << selected_train;
    qDebug() << "NAME........" << ui->tableView->selectionModel()->currentIndex().column();
    selected_train_no = ui->tableView->model()->data(ui->tableView->model()->index(selected_train,0)).toString();
    qDebug() << "train no. = " << selected_train_no;
    train_name = ui->tableView->model()->data(ui->tableView->model()->index(selected_train,11)).toString();
    qDebug() << "Train name = " << train_name;
    /////////////////// Determine Slave Or Master train Selected //////////////////////
    QSqlQuery query_determine_slave_train("SELECT `tran_name_english` FROM `tbl_TrainNumber` where `train_no`='"+ selected_train_no+"'");
    if(!query_determine_slave_train.next())
    {
        QSqlQuery find_master_train("SELECT `master_route` FROM `tbl_slave_route` where `train_number`='"+ selected_train_no + "'");
        find_master_train.next();
        selected_train_no = find_master_train.value(0).toString();
        train_is_slave = true;
    }
    qDebug() << "Train is slave -" << train_is_slave;
    qDebug() << "Master Train Number ------> " << selected_train_no;

    //------------------------------------------------------------------------------//
    /////////////////////////////  FINDING SOURCE/DESTINATION STATIONS ///////////////////////
    qDebug() << "SELECT `src_stn_sno`,`dest_stn_sno` FROM `tbl_TrainNumber` where `train_no`='"+ selected_train_no+"'";
    QSqlQuery query1("SELECT `src_stn_sno`,`dest_stn_sno` FROM `tbl_TrainNumber` where `train_no`='"+ selected_train_no+"'");
    while(query1.next()){
        source_destination_station_codes.clear();
        QSqlRecord record = query1.record();
        for(int i=0; i < record.count(); i++)
            source_destination_station_codes << record.value(i).toString();
    }
    qDebug() << source_destination_station_codes;

    ///////////////////////////// FINDING SOURCE STATION NAME  ////////////////////
    QSqlQuery query_find_source_station("SELECT `station_name` FROM `tbl_StationName` where `station_code`='"+ source_destination_station_codes.at(0) +"' and `stn_LangId`='English'");
    query_find_source_station.next();
    //QSqlRecord record_source_station_name= query_find_source_station.record();
    source_station_name = query_find_source_station.value(0).toString();
    qDebug()  << "SOURCE STATION NAME = " << source_station_name;

    /////////////////////////////////////////////////////////////////////////////////
    /////////////////////////// FINDING DESTINATION STATION NAME  ///////////////////
    QSqlQuery query_find_destination_station("SELECT `station_name` FROM `tbl_StationName` where `station_code`='"+ source_destination_station_codes.at(1) +"' and `stn_LangId`='English'");
    query_find_destination_station.next();
   // record_destination_station_name = query_find_destination_station.record();
    destination_station_name = query_find_destination_station.value(0).toString();
    qDebug() << "DESTINATION STATION NAME" << destination_station_name;
    /////////////////////////////////////////////////////////////////////////////////
    ui->tableView->hide();
    ui->lineEdit->hide();
    ui->select_route_label->hide();
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->addWidget(current_route);
    ui->stackedWidget->setCurrentWidget(current_route);
    //current_route->setParent(this);
    emit train_selected();
}
