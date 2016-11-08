#ifndef SKIPBUTTON_H
#define SKIPBUTTON_H


/*class skipbutton
{
public:
    skipbutton();
    ~skipbutton();
};*/
#include "route_struct.h"
#include <QDebug>
#include <QPushButton>
#include <QObject>
#include <QLabel>
class skipbutton : public QPushButton

{
    Q_OBJECT

    public:
    skipbutton(const QString & text,int id,QLabel *label,QWidget *widget,QWidget *parent=  0);
    int button_id;
    QLabel *station_name_label;
    QWidget *widget_reference;
    bool skip_button;
 signals:
    void skip_clicked(int id);
public slots:
    void on_skip_clicked();

};


#endif // SKIPBUTTON_H
