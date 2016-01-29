#include "etu.h"
#include "ui_etu.h"
void etu::paintEvent(QPaintEvent* /*event*/)
{
 QColor backgroundColor ;
 backgroundColor.setRgb(173, 216, 230);
 backgroundColor.setAlpha(180);
 QPainter customPainter(this);
 customPainter.fillRect(rect(),backgroundColor);
}
etu::etu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::etu)
{
    ui->setupUi(this);
    connect(ui->end_call_button,SIGNAL(clicked()),this,SLOT(end_current_call()));

}


etu::~etu()
{
    delete ui;
}

void etu::end_current_call()
{
    emit call_ended();
}

void etu::on_etu_back_button_clicked()
{
    emit back_clicked();
}
