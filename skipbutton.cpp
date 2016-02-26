#include "skipbutton.h"
extern struct route_struct current_route_data;
skipbutton::skipbutton(const QString & text,int id,QLabel *label,QWidget *widget, QWidget* parent)
    :QPushButton(parent)
{
this->setText(text);
    button_id  = id;
    station_name_label= label;
    widget_reference = widget;
    skip_button=true;
    connect(this,SIGNAL(clicked()),this,SLOT(on_skip_clicked()));
}

void skipbutton::on_skip_clicked()
{
    if(skip_button)
    {
    emit this->skip_clicked(button_id);
    this->setText("Add");
    this->setStyleSheet("background-color: rgba(0,255,0,50)");
    station_name_label->setStyleSheet("color: rgb(150,0,0)");
    skip_button=false;
    current_route_data.stn[button_id].status.bits.station_skipped = true;
    }
    else
    {
        this->setText("Skip");
        this->setStyleSheet("QPushButton{ background-color: rgb(179, 179, 179); }QPushButton:pressed{background-color: rgb(100, 100, 100); }");
        station_name_label->setStyleSheet("color: rgb(0,0,0)");
        widget_reference->setStyleSheet("background-color: rgb(179,179,179);");
        skip_button=true;
        current_route_data.stn[button_id].status.bits.station_skipped = false;

    }
}

