#ifndef SKIPBUTTON_H
#define SKIPBUTTON_H


/*class skipbutton
{
public:
    skipbutton();
    ~skipbutton();
};*/
#include<QDebug>
#include<QPushButton>
#include <QObject>
class skipbutton : public QPushButton

{
    Q_OBJECT

    public:
    skipbutton(const QString & text,int id,QWidget *parent=  0);
    int button_id;
 signals:
    void skip_clicked(int id);
public slots:
    void on_skip_clicked();

};


#endif // SKIPBUTTON_H
