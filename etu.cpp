#include "etu.h"
#include "ui_etu.h"
void etu::paintEvent(QPaintEvent* /*event*/)
{
 QColor backgroundColor = palette().light().color();
 backgroundColor.setAlpha(5);
 QPainter customPainter(this);
 customPainter.fillRect(rect(),backgroundColor);
}
etu::etu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::etu)
{
    ui->setupUi(this);
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
