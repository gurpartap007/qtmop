#ifndef ETUBUTTON_H
#define ETUBUTTON_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QPushButton>
enum
 {
    answer,
    terminate,
    hold
 };

class EtuButton : public QPushButton
{
    Q_OBJECT

public:
    EtuButton(long id,int button_type ) ;
    ~EtuButton();
    bool button_clicked;
    long button_id;
signals:
   void EtuButton_clicked(long id);
public slots:
   void custom_clicked_slot();
   void check_call_status(bool call_connected,bool call_paused,long call_id);
private:
bool paused_state;
int type_of_button;

};

#endif // ETUBUTTON_H
