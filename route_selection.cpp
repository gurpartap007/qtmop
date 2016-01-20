#include "route_selection.h"
#include "ui_route_selection.h"
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
    current_route = new train_route(&db);
    master_trains_model = new QSqlTableModel(this,db);
    slave_trains_model = new QSqlTableModel(this,db);
    proxyModel = new QSortFilterProxyModel;
    ui->stackedWidget->addWidget(current_route);
    ui->stackedWidget->addWidget(train_selection_keyboard);
    ui->stackedWidget->setCurrentWidget(train_selection_keyboard);
    connect(train_selection_keyboard,SIGNAL(value_changed(char)),this,SLOT(settext(char)));
    connect(this,SIGNAL(train_selected()),this,SLOT(route_window()));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(lineedit_filtering(QString)));
    connect(this, SIGNAL(lineedit_filter(QString)), proxyModel, SLOT(setFilterRegExp(QString)));
    train_selection_keyboard->on_pushButton_31_clicked();
    select_train_route_with_sorting();

}
route_selection::~route_selection()
{
    delete ui;
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
            ++route_count;
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
    master_trains_model->setTable("tbl_TrainNumber");
    master_trains_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    master_trains_model->select();
    proxyModel->setSourceModel(master_trains_model);
    ui->tableView->setModel(proxyModel);
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


