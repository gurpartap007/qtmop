#include "skipbutton.h"

skipbutton::skipbutton(const QString & text,int id, QWidget* parent)
    :QPushButton(parent)
{
this->setText(text);
    qDebug() << "Id = " << id;
    button_id  = id;
    connect(this,SIGNAL(clicked()),this,SLOT(on_skip_clicked()));
}

void skipbutton::on_skip_clicked()
{
    emit this->skip_clicked(button_id);
    this->setText("Add");
}

