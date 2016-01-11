#include "etu.h"
#include "ui_etu.h"

etu::etu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::etu)
{
    ui->setupUi(this);
    this->setGeometry(300,0,1000,1200);
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(end_current_call()));

}


etu::~etu()
{
    delete ui;
}

void etu::end_current_call()
{
    emit call_ended();
}
