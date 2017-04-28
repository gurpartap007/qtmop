#include "prerecorded.h"

extern QSqlDatabase pis_db,db2,db3;
QString pre_recorded;

PreRecorded::PreRecorded(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreRecorded)
{
    ui->setupUi(this);
    qDebug("\nSetting PreRecorded user interface ...\n");
    this->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::X11BypassWindowManagerHint|Qt::FramelessWindowHint);

    QSqlTableModel *model = new QSqlTableModel(this, pis_db);
    model->setTable("tbl_msg_frame_list");
    model->setFilter("`language` = '0' GROUP BY `msg_id` ");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    proxyModel = new QSortFilterProxyModel;
    proxyModel->setSourceModel(model);
    /** SETTING UP DATA IN TABLEVIEW */
    ui->tableView->setModel(proxyModel);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->hide();
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(1);
    ui->tableView->hideColumn(2);
    ui->tableView->hideColumn(3);
    ui->tableView->hideColumn(4);
    ui->tableView->hideColumn(5);
    ui->tableView->hideColumn(6);
    ui->tableView->sortByColumn(7, Qt::AscendingOrder);
    ui->tableView->setColumnWidth(7,950);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    QWidget::move(QApplication::desktop()->screen()->rect().center() - QWidget::rect().center());
}

PreRecorded::~PreRecorded()
{
    delete ui;
}

void PreRecorded::on_play_clicked()
{
    ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->selectionModel()->currentIndex().row(),5)).toString() + "/" + ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->selectionModel()->currentIndex().row(),6)).toString();
    int data[2];
    data[0] = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->selectionModel()->currentIndex().row(),4)).toInt();
    data[1] = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->selectionModel()->currentIndex().row(),1)).toInt();
    emit playclicked(data);
}

void PreRecorded::on_pushButton_clicked()
{
    this->hide();
}

void PreRecorded::showEvent(QShowEvent *e)
{
    this->setFixedHeight(QApplication::desktop()->screenGeometry(-1).height()-150);
    this->setFixedWidth(QApplication::desktop()->screenGeometry(-1).width()-150);
    QWidget::move(QApplication::desktop()->screenGeometry(-1).center() - QWidget::rect().center());
}
