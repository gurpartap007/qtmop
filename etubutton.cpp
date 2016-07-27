#include "etubutton.h"
extern bool call_connected;
EtuButton::EtuButton(long id,int recieved_button_type)
{
    paused_state = false;
    button_id = id;
    type_of_button = recieved_button_type;
    connect(this,SIGNAL(clicked()),this,SLOT(custom_clicked_slot()));
}

EtuButton::~EtuButton()
{

}

void EtuButton::custom_clicked_slot()
{
    emit this->EtuButton_clicked(button_id);
}

void EtuButton::check_call_status(bool call_connected,bool call_paused,long call_id)
{
    qDebug() << "TYPE OF BUTTON -->" << type_of_button;
    if (call_connected && !call_paused)
    {
        if(this->type_of_button == answer && button_id != call_id)
            this->setDisabled(true);
        else if(this->type_of_button == hold && button_id == call_id)
        {
            qDebug() << "TYPE OF BUTTON -->" << type_of_button;
            qDebug() << "Call is Resumed ";
            QPixmap pix_pause_button(":/images/hold_call.png");
            QIcon pause_button_icon(pix_pause_button);
            this->setIcon(pause_button_icon);
            this -> setMinimumSize(QSize(60,30));
            this->setIconSize(QSize(50,50));
        }
    }
    else if(!call_connected && call_paused)
    {
        if(this->type_of_button == hold && button_id == call_id)
        {
            qDebug() << "TYPE OF BUTTON -->" << type_of_button;
            qDebug() << "Call Paused";
            QPixmap pix_resume_button(":/images/start_announce.png");
            QIcon resume_button_icon(pix_resume_button);
            this->setIcon(resume_button_icon);
            this -> setMinimumSize(QSize(60,30));
            this->setIconSize(QSize(50,50));
        }
        else
            this->setEnabled(true);
    }
     else if(!call_connected && !call_paused)
    {
        if(this->type_of_button == answer)
        this->setEnabled(true);
    }
    else
    {
        if(this->type_of_button == answer && button_id != call_id)
        this->setDisabled(true);
    }
}

