#include "train_route.h"
#include "ui_train_route.h"

train_route::train_route(QSqlDatabase *emu_database,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::train_route)
{
    ui->setupUi(this);
    QSqlTableModel *model = new QSqlTableModel(this,*emu_database);
    model->setTable("tbl_slave_route");
    ui->route_info_table->setModel(model);
    model->select();
    ui->route_info_table->verticalHeader()->hide();
    ui->route_info_table->hideColumn(0);
    ui->route_info_table->hideColumn(7);
    ui->route_info_table->hideColumn(6);
}

train_route::~train_route()
{
    delete ui;
}
