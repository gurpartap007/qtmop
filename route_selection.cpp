#include "route_selection.h"
#include "ui_route_selection.h"
QString selected_train_no,master_train_no,slave_train_no;
QStringList train_routes;
QString filter_string;
extern char display[20];
extern char *ptr;
extern QSqlDatabase db;
route_selection::route_selection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::route_selection)
{
    ui->setupUi(this);
    train_selection_keyboard =  new keyboard(this);
    train_database           =  new database(this);
    master_trains_model      =  new QSqlTableModel(this,db);
    slave_trains_model       =  new QSqlTableModel(this,db);
    proxyModel               =  new QSortFilterProxyModel;
    current_route            =  new train_route();
    ui->stackedWidget->addWidget(train_selection_keyboard);
    ui->stackedWidget->setCurrentWidget(train_selection_keyboard);
    connect(train_selection_keyboard,SIGNAL(value_changed(char)),this,SLOT(settext(char)));
    connect(this,SIGNAL(train_selected(bool)),current_route,SLOT(structure_filling(bool)));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(lineedit_filtering(QString)));
    connect(this,SIGNAL(change_numeric_keypad()),train_selection_keyboard,SLOT(on_pushButton_31_clicked()));
    emit select_train_route_with_sorting();
    emit train_selection_keyboard->change_to_numeric();
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
    if(value == ENTER_CLICK )
    {
        qDebug() << train_routes;
        while(train_routes[route_count]!=NULL)
        {
            if(strcmp(display,train_routes[route_count].toUtf8().constData()))
            {
                ui->lineEdit->clear();
                ui->lineEdit->setAlignment(Qt::AlignCenter);
                ui->lineEdit->setText("Invalid Train Route");
                ui->lineEdit->setStyleSheet("QLineEdit { background-color: rgb(255,0,0); }");
            }
            else
            {
                break;
            }
            ++route_count;
        }
        while(ptr != &display[0])
        {
            ptr--      ; //decrement user input pointer
            *ptr = '\0'; //write null to current memory location of user input pointer
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
    ui->backButton->autoDefault();
    ui->lineEdit->hide();
    ui->select_route_label->hide();
    ui->backButton->isActiveWindow();
    ui->stackedWidget->setCurrentWidget(current_route);
}

void route_selection::select_train_route_with_sorting()
{
    int loop_count=0;
    int train_count;
    QFont header_font;
    QStringList master_train_no_for_current_slave_train;
    QStringList labels,slave_train_no,master_train_names;
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
    QList <QStandardItem *> ColumnData;

    //////////////////// Inserting Master Train numbers ///////////////////////////
    for(loop_count=0;loop_count<master_trains_model->rowCount();loop_count++)
    {
        ColumnData << new QStandardItem(master_trains_model->data(master_trains_model->index(loop_count,TrainNumber::TRAIN_NO)).toString());
    }
    //---------------------------------------------------------------------------//

    //////////////////// Inserting Slave Train numbers ////////////////////////////

    for(loop_count=0;loop_count<slave_trains_model->rowCount();loop_count++)
    {
        ColumnData << new QStandardItem(slave_trains_model->data(slave_trains_model->index(loop_count,TrainNumber::TRAIN_NO)).toString());
    }

    model->insertColumn(0,ColumnData);
    ColumnData.clear();

    //----------------------------------------------------------------------------//
    ///////////////////// Finding Master Trains for Slave Trains ///////////////////
    for(train_count=0;train_count<slave_trains_model->rowCount();train_count++)
    {
        slave_train_no << slave_trains_model->data(slave_trains_model->index(train_count,TrainNumber::TRAIN_NO)).toString();
        QSqlQuery find_master_train("SELECT `master_route` FROM `tbl_slave_route` where `train_number`='"+ slave_train_no.at(train_count) + "'");
        find_master_train.next();
        master_train_no_for_current_slave_train.append(find_master_train.value(0).toString());
        find_master_train.clear();
    }

    //-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --//

    //////////////////////////// Extract master train Name from Master Train Number //////////////////////////////
    for(train_count=0;train_count<master_train_no_for_current_slave_train.size();train_count++)
    {
        QSqlQuery find_master_train_name("SELECT `tran_name_english` FROM `tbl_TrainNumber` where `train_no`='"+ master_train_no_for_current_slave_train.at(train_count) + "'");
        find_master_train_name.next();
        master_train_names.append(find_master_train_name.value(0).toString());
    }

    //-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --//

    ///////////////////////////////////////// Inserting Master Train Names ////////////////////////////////////////

    for(loop_count=0;loop_count<master_trains_model->rowCount();loop_count++)
    {
        ColumnData << new QStandardItem(master_trains_model->data(master_trains_model->index(loop_count,TrainNumber::TRAN_NAME_ENGLISH)).toString());
    }

    for(loop_count=0;loop_count<master_train_names.size();loop_count++)
    {
        ColumnData << new QStandardItem(master_train_names.at(loop_count));
    }

    //-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --//

    model->insertColumn(1,ColumnData);
    ColumnData.clear();
    model->setHorizontalHeaderLabels(labels);
    proxyModel->setSourceModel(model);
    proxyModel->setFilterKeyColumn(0);
    ui->tableView->setModel(proxyModel);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    QHeaderView *verticalHeader = ui->tableView->verticalHeader();
    verticalHeader->sectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(40);
    ui->backButton->hide();
}

void route_selection::route_data_to_relevant_channels()
{
    int route_lines_depth;
    route_lines_depth = 20;
    ui->lineEdit->displayText();
    ui->lineEdit->fontInfo();
    ui->lineEdit->blockSignals(false);
    route_lines_depth = ui->lineEdit->depth();

  /*  "khuda bhi aasmaan se jab zameen par dekhta hoga"
    "mere mehboob ko kisne bnayaa sochtaa hoga"

    "musavir khud pareshaan hai ke yeh tasveer kiski hai"
    "banogi jis ki tum aisi  haseen taqdeer kiski hai"
    "kabhi wo jal raha hoga kabhi khush ho raha hoga"

    "zamaane bhar ki masti ko nigahon mein sameta hai"
    "kali se jism ko kitni baharon me lapeta hai"
    "hua tum sa koi pehle na koi doosra hoga"

    "farishte bhi jahaan raaton ko aakar ghumte honge"
    "jahan rakhti ho tum paoon jageh wo chumte honge"
    "kiske dil pe kya guzari ye wohi jaantaa hoga"*/
}


void route_selection::on_backButton_clicked()
{
    while(ptr != &display[0] && ptr!=NULL)
    {
        ptr--;	   //decrementing write pointer
        *ptr ='\0';//write NULL in current memory location
    }

    ui->lineEdit->setText(QString::fromUtf8(display));
    ui->stackedWidget->setCurrentWidget(train_selection_keyboard);
    this->close();
}


void route_selection::on_linedit_clicked()
{
    qDebug() << "Line Edit Clicked";
    ui->lineEdit->setAlignment(Qt::AlignCenter);
    ui->lineEdit->setAlignment(Qt::AlignRight);
}

void route_selection::lineedit_filtering(QString value)
{
    qDebug() << "prepending value ^ which means start with";
    value.prepend("^");
    proxyModel->setFilterRegExp(value);
}

void route_selection::on_tableView_clicked()
{
    int selected_train;
    bool slave_train = false;

    selected_train = ui->tableView->selectionModel()->currentIndex().row();
    selected_train_no = ui->tableView->model()->data(ui->tableView->model()->index(selected_train,0)).toString();
    ///////////////////////////////// Determine Slave Or Master train Selected ///////////////////////////////
    QSqlQuery query_determine_slave_train("SELECT `tran_name_english` FROM `tbl_TrainNumber` where `train_no`='"+ selected_train_no+"'");
    if(!query_determine_slave_train.next())
    {
        slave_train_no = selected_train_no;
        qDebug() << "Slave train no " << slave_train_no;
        QSqlQuery find_master_train("SELECT `master_route` FROM `tbl_slave_route` where `train_number`='"+ selected_train_no + "'");
        find_master_train.next();
        master_train_no = find_master_train.value(0).toString();
        qDebug() << "Master train no " << master_train_no;
        qDebug() << "Master Train Route" << master_trains_model->data(model->index(0,0));
        slave_train=true;
    }
    else
    {
        master_train_no = selected_train_no;
        qDebug() << "Master train no " << master_train_no;
    }

    ui->tableView->hide();
    ui->lineEdit->hide();
    ui->select_route_label->hide();
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->addWidget(current_route);
    ui->stackedWidget->setCurrentWidget(current_route);
    emit train_selected(slave_train);
}
