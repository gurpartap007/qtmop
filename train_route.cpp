#include "train_route.h"
#include "ui_train_route.h"
extern QString selected_train_no;
extern int selected_train;
train_route::train_route(QSqlDatabase *emu_database,QSqlTableModel *master_trains_model,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::train_route)
{
    ui->setupUi(this);
    master_train_model = master_trains_model;
   // current_selected_train = selected_train_no;
}

train_route::~train_route()
{
    delete ui;
}

void train_route::current_selected_train_info()
{
qDebug() << "Selected train in train route = " << selected_train_no;
source_destination_name = master_train_model->data(master_train_model->index(selected_train,11)).toString();
qDebug() << "Source Destination in train route = " << source_destination_name;
source_destination_list = source_destination_name.split(" TO");
qDebug() << "Source Station in train route = " << source_destination_list;
ui->source_station_name->setText(source_destination_list[SOURCE_NAME]);
ui->destination_station_name->setText(source_destination_list[DESTINATION_NAME]);
/*QString query_text = "select * from stop_master_table where stop_code = '" + destination_code + "'" ;
QSqlQuery query(query_text);
query.first();
ui->label_4->setText(query.value(0).toString());*/
}
