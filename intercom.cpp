#include "intercom.h"
#include "ui_intercom.h"

intercom::intercom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::intercom)
{
    ui->setupUi(this);
}

intercom::~intercom()
{
    delete ui;
}
