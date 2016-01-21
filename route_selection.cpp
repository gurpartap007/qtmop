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
    current_route = new train_route(&db,master_trains_model);
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
    int loop_count=0;
    QFont header_font;
    header_font.setPointSize(20);
    header_font.setFamily("Garuda");
    master_trains_model->setTable("tbl_TrainNumber");
    slave_trains_model->setTable("tbl_slave_route");
    slave_trains_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    slave_trains_model->select();
    slave_trains_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    master_trains_model->select();
    // proxyModel->setSourceModel(master_trains_model);
    // proxyModel->setSourceModel(slave_trains_model);
    QStringList labels;
    QStringList datalist;



    QSqlQuery query1("SELECT `train_no`,`tran_name_english` FROM `tbl_TrainNumber`");
    while(query1.next()){
        datalist.clear();
        QSqlRecord record = query1.record();
        for(int i=0; i < record.count(); i++)
            datalist << record.value(i).toString();
        dummy_model->insertRecord(0,record);

        qDebug() << datalist;
        loop_count++;
    }
    /*    QStandardItemModel dummy_model1;
    dummy_model1.setRowCount(5);
    dummy_model1.setColumnCount(5);
                QStandardItem *item = new QStandardItem("Hello1");
                dummy_model1.setItem(0,0,item);
                dummy_model1.setHorizontalHeaderItem(0, new QStandardItem(tr("Time")));
    //dummy_model1.insertRow(0,&row1);*/
    model= new QStandardItemModel(0,0);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setFont(header_font);
    int row = 0;
    //for (int row = 0; row < 4; ++row)
    //  {
    QList <QStandardItem *> rowData;
    QList <QStandardItem *> ColumnData;
    labels.append("Train_no");
    labels.append("Train_name");
    //////////////////// Inserting New Rows ///////////////////////////

    rowData << new QStandardItem(QString("1001"));
    rowData << new QStandardItem(QString("1002"));
    rowData << new QStandardItem(QString("1003"));
    // model->appendRow(rowData);

    //////////////////// Inserting New Rows ///////////////////////////
    for(loop_count=0;loop_count<master_trains_model->rowCount();loop_count++)
    {

        //ColumnData << new QStandardItem(QString("1001"));
        ColumnData << new QStandardItem(master_trains_model->data(master_trains_model->index(loop_count,TABLE_TRAIN_NUMBER::TRAIN_NO)).toString());
        qDebug() << master_trains_model->data(master_trains_model->index(loop_count,TABLE_TRAIN_NUMBER::TRAIN_NO)).toString();
    }
    for(loop_count=0;loop_count<slave_trains_model->rowCount();loop_count++)
    {

        //ColumnData << new QStandardItem(QString("1001"));
        ColumnData << new QStandardItem(slave_trains_model->data(slave_trains_model->index(loop_count,TABLE_TRAIN_NUMBER::TRAIN_NO)).toString());
        qDebug() << slave_trains_model->data(slave_trains_model->index(loop_count,TABLE_TRAIN_NUMBER::TRAIN_NO)).toString();
    }
    model->insertColumn(0,ColumnData);
    ColumnData.clear();
    for(loop_count=0;loop_count<master_trains_model->rowCount();loop_count++)
    {

        //ColumnData << new QStandardItem(QString("1001"));
        ColumnData << new QStandardItem(master_trains_model->data(master_trains_model->index(loop_count,TABLE_TRAIN_NUMBER::TRAIN_NAME_ENG)).toString());
        qDebug() << master_trains_model->data(master_trains_model->index(loop_count,TABLE_TRAIN_NUMBER::TRAIN_NAME_ENG)).toString();
    }
    model->insertColumn(1,ColumnData);
    ColumnData.clear();

    //model->insertColumn(0,ColumnData);
    model->setHorizontalHeaderLabels(labels);
    //  rowData << new QStandardItem(QString("row %1, column %2").arg(row).arg(1));
    //  rowData << new QStandardItem(QString("row %1, column %2").arg(row).arg(2));
    //  rowData << new QStandardItem(QString("row %1, column %2").arg(row).arg(3));

    //  }
    //QSqlRecord dummy_record=dummy_model->record();
    //dummy_record.setValue(0,QVariant("hello1"));
    //dummy_model->insertRecord(0,dummy_record);
    //dummy_model->insertRow(0);
    //  dummy_model->insertRecord(0,)
    proxyModel->setSourceModel(model);
    //ui->tableWidget->setModel(proxyModel);
    ui->tableView->setModel(proxyModel);
    //item1->setText("New Delhi");
    // ui->tableWidget->setItem(0,0,new QTableWidgetItem("Item1"));
    // ui->tableWidget->setItem(1,1,new QTableWidgetItem("Item2"));
    // ui->tableWidget->setItem(0,2,new QTableWidgetItem("Item3"));
    //ui->tableWidget->setRowCount(2);
     /*  ui->tableView->setModel(proxyModel);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->hideColumn(1);
    ui->tableView->hideColumn(2);
    ui->tableView->hideColumn(3);
    ui->tableView->hideColumn(4);
    ui->tableView->hideColumn(5);
    ui->tableView->hideColumn(6);
    ui->tableView->hideColumn(7);
    ui->tableView->hideColumn(8);
    ui->tableView->hideColumn(9);
    ui->tableView->hideColumn(10);
    ui->tableView->hideColumn(12);
    ui->tableView->hideColumn(13);
    ui->tableView->hideColumn(14);
    ui->tableView->hideColumn(15);
    ui->tableView->hideColumn(16);
    ui->tableView->hideColumn(17);
    ui->tableView->hideColumn(18);
    ui->tableView->hideColumn(19);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    QHeaderView *verticalHeader = ui->tableView->verticalHeader();
    verticalHeader->sectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(40);*/
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
    selected_train = ui->tableView->selectionModel()->currentIndex().row();
    qDebug() << "selected train no = " << selected_train;
    selected_train_no = master_trains_model->data(master_trains_model->index(selected_train,0)).toString();
    qDebug() << "train no. = " << selected_train_no;
    train_name = master_trains_model->data(master_trains_model->index(selected_train,11)).toString();
    qDebug() << "Train name = " << train_name;
    ui->tableView->hide();
    ui->lineEdit->hide();
    ui->select_route_label->hide();
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->addWidget(current_route);
    ui->stackedWidget->setCurrentWidget(current_route);
    //current_route->setParent(this);
    emit train_selected();
}
