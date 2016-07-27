#include "etu.h"
#include "ui_etu.h"
#include "etubutton.h"
bool CallOutgoingRinging=false;
bool CallOutgoingEarlyMedia=false;
bool CallConnected=false;
bool CallStreamsRunning=false;
bool CallEnd=false;
bool CallError=false;
bool isIncomingCall= false;
bool call_connected=false;
bool call_paused   =false;
long unique_call_id;
LinphoneCall *active_call;
int global_calls_count;
QList <QListWidgetItem *> call_reference;
QList <LinphoneCall *> Calls_list;
void etu::paintEvent(QPaintEvent* /*event*/)
{
    QColor backgroundColor ;
    backgroundColor.setRgb(173, 216, 230);
    backgroundColor.setAlpha(180);
    QPainter customPainter(this);
    customPainter.resetMatrix();
    customPainter.fillRect(rect(),backgroundColor);
}

bool etu::eventFilter(QObject *watched, QEvent *event)
{
    if (  event->type() == QEvent::MouseButtonPress )
    {
        //   ui->call_queue->clear();
        emit back_clicked();
    }
    return QObject::eventFilter(watched, event);
}

etu::etu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::etu)
{
    ui->setupUi(this);
    call_state_timer = new QTimer;
    call_state_timer->setInterval(2000);
    connect(this,SIGNAL(new_incoming_call()),this,SLOT(incoming_call_handler()));
    qlinphone_init();
    ui->left_area->installEventFilter(this);
    ui->right_area->installEventFilter(this);
    ui->bottom_area->installEventFilter(this);
}


etu::~etu()
{
    delete ui;
}

void etu::end_current_call()
{
    emit call_ended();
}

void etu::qlinphone_init()
{
    QDir confDir = QDir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
    confDir.mkdir("Linphone");
    QString config_file = confDir.absolutePath() + "/Linphone/.linphonerc";
    LinphoneCoreVTable vtable = {0};
    vtable.call_state_changed = qcall_state_changed;
    lc = linphone_core_new(&vtable, config_file.toStdString().c_str() , NULL, this);
    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &etu::iterate);
    timer->start(50);
    linphone_core_enable_echo_cancellation(lc,1);
    linphone_core_enable_echo_limiter(lc,1);
    linphone_core_set_inc_timeout(lc,60);
}

void etu::incoming_call_handler()
{
    qDebug() << "Timeout For Incoming Calls" << linphone_core_get_inc_timeout(lc);
    long call_id ;
    QStringList caller_ip;
    QPixmap green_answer_button(":/images/green_call_button.png");
    QPixmap red_terminate_button(":/images/red_stop_button.png");
    QPixmap pix_hold_button(":/images/hold_call.png");
    QIcon answer_button_icon(green_answer_button);
    QIcon terminate_button_icon(red_terminate_button);
    QIcon hold_button_icon(pix_hold_button);
    EtuButton *answer_button,*terminate_button,*hold_button;
    QLabel *station_name;
    QListWidgetItem *item;
    QWidget *widget;
    QHBoxLayout *widgetLayout;
    QSpacerItem *spacer_left,*spacer_right;
    call_id = ms_list_size(linphone_core_get_calls(lc));
    //   unique_call_id =  call_id;
    qDebug() << "Call Id in incoming_handler ->" << call_id;
    station_name_font = new QFont;
    station_name_font->setFamily("Sans Serif");
    station_name_font->setPointSize(14);
    station_name_font->setBold(true);
    station_name_font->setCapitalization(QFont::SmallCaps);
    station_name = new QLabel ;
    qDebug() << "Current Call Address = " << linphone_call_get_remote_address_as_string(call);
    caller_ip = QString::fromLatin1(linphone_call_get_remote_address_as_string(call)).split('@');
    station_name->setText(caller_ip.at(1));
    widget = new QWidget(this);
    answer_button = new EtuButton(call_id,answer);
    terminate_button = new EtuButton(call_id,terminate);
    hold_button = new EtuButton(call_id,hold);
    widgetLayout = new QHBoxLayout;
    widgetLayout->setMargin(3);
    item = new QListWidgetItem();
    connect(answer_button,&EtuButton::EtuButton_clicked,this,&etu::accept_call_slot);
    connect(this,SIGNAL(call_status(bool,bool,long)),answer_button,SLOT(check_call_status(bool,bool,long)));
    connect(terminate_button,SIGNAL(EtuButton_clicked(long)),this,SLOT(end_call_slot(long)));
    connect(this,SIGNAL(call_status(bool,bool,long)),hold_button,SLOT(check_call_status(bool,bool,long)));
    connect(hold_button,SIGNAL(EtuButton_clicked(long)),this,SLOT(hold_call_slot(long)));
    spacer_left = new QSpacerItem(1,1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    spacer_right = new QSpacerItem(1,1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    answer_button -> setMinimumSize(QSize(60,30));
    answer_button->setIcon(answer_button_icon);
    answer_button->setIconSize(QSize(50,50));
    terminate_button -> setMinimumSize(QSize(60,30));
    terminate_button->setIcon(terminate_button_icon);
    terminate_button->setIconSize(QSize(50,50));
    hold_button -> setMinimumSize(QSize(60,30));
    hold_button->setIcon(hold_button_icon);
    hold_button->setIconSize(QSize(50,50));
    station_name-> setFont(*station_name_font) ;
    //answer_button -> setStyleSheet("QPushButton{ background-color: rgba(0,179,0,50); }QPushButton:pressed{background-color: rgb(0, 100,0); }");
    terminate_button -> setStyleSheet("QPushButton{ background-color: rgba(179,0,0,50); }QPushButton:pressed{background-color: rgb(100,0,0); }");
    station_name-> setStyleSheet("color: rgb(255,255,255)");
    widgetLayout-> addWidget(answer_button);
    widgetLayout-> addWidget(terminate_button);
    widgetLayout-> addWidget(hold_button);
    widgetLayout-> addSpacerItem(spacer_left);
    widgetLayout-> addWidget(station_name)   ;
    widgetLayout-> addSpacerItem(spacer_right);
    widgetLayout-> setAlignment(answer_button,Qt::AlignLeft);
    widgetLayout-> setAlignment(terminate_button,Qt::AlignLeft);
    widgetLayout-> setAlignment(station_name,Qt::AlignRight);
    widget      -> setLayout(widgetLayout);
    widget      -> setStyleSheet("background-color: rgb(0,0,100);");
    ui->call_queue->insertItem(call_id-1,item);
    item-> setSizeHint(answer_button->minimumSizeHint());
    ui->call_queue -> setItemWidget(item,widget);
    global_calls_count = ui->call_queue->count();
    if(call_id == 1)
    {
        //call_reference.clear();
        // Calls_list.clear();
    }
    call_reference.append(item);
}

void qcall_state_changed(LinphoneCore *lc, LinphoneCall *call, LinphoneCallState cstate, const char *msg)
{
    qDebug() << "Checking Call State";
    qDebug() << "Call State: " << linphone_call_get_state(call);
    active_call = call;
    switch(cstate){
    case LinphoneCallOutgoingRinging:
        //   qDebug() << "It is now ringing remotely";
        CallOutgoingRinging=true;
        //    qDebug() << "CallOutgoingRinging" << CallOutgoingRinging;
        break;
    case LinphoneCallOutgoingEarlyMedia:
        //   qDebug() << "Receiving some early media";
        CallOutgoingEarlyMedia=true;
        break;
    case LinphoneCallIncoming:
        //    qDebug() << "New Incoming Call";
        isIncomingCall = true;
        Calls_list.append(call);
        break;
    case LinphoneCallConnected:
        //    qDebug() << "We are connected ";
        CallConnected=true;
        break;
    case LinphoneCallStreamsRunning:
        //    qDebug() << "Media streams established ";
        CallStreamsRunning=true;
        break;
    case LinphoneCallEnd:
        //    qDebug() << "Call is terminated";
        CallEnd=true;
        break;
    case LinphoneCallReleased:
        break;
    case LinphoneCallError:
        //  qDebug() << "Call failure !";
        CallError=true;
        break;
    default:
        qDebug() << "Unhandled notification " << cstate;
    }
}

void etu::iterate()
{
   /* if(!(ms_list_size(linphone_core_get_calls(lc))))
    {
        emit back_clicked();
        ui->call_queue->clear();
       // Calls_list.clear();
       // call_reference.clear();
    }*/
    linphone_core_iterate(lc);
    if(CallConnected)
    {
        //  ui->call_queue->appendPlainText("Call Connected");
        CallConnected=false;
        //     qDebug() << "Current Call Connected";
    }
    else if(CallOutgoingRinging)
    {
        //  ui->call_queue->appendPlainText("Call Outgoing ringing");
        CallOutgoingRinging=false;
        //      qDebug() << "Call Outgoing Ringing";
    }
    else if(CallOutgoingEarlyMedia)
    {
        //  ui->call_queue->appendPlainText(("Call Outgoing Early Media"));
        CallOutgoingEarlyMedia=false;
        //    qDebug() << "Call Outgoing to remote";
    }
    else if(CallStreamsRunning)
    {
        //   ui->call_queue->appendPlainText("Call Streams Running");
        CallStreamsRunning=false;
        //     qDebug() << "Call Streams Running";
    }
    else if(CallEnd)
    {
        //   ui->call_queue->appendPlainText("Call ended");
        CallEnd=false;
        check_call_state(active_call);
        //   qDebug() << "Current Call Ended";
    }
    else if(CallError)
    {
        // ui->call_queue->appendPlainText("Call error");
        CallError=false;
        //   qDebug() << "Error in establishing current Call";
    }
    else if(isIncomingCall)
    {
        const MSList *multiple_calls;
        unique_call_id = ms_list_size(linphone_core_get_calls(lc));
        multiple_calls = linphone_core_get_calls(lc);
        if(multiple_calls == NULL)
            qDebug() << "There Are No Calls" ;
        else
        {
            for (;multiple_calls!=NULL;multiple_calls=multiple_calls->next)
            {
                call=(LinphoneCall*)multiple_calls->data;
            }
        }
        linphone_call_set_user_pointer (call,(void*)unique_call_id);
        isIncomingCall = false;
        emit new_incoming_call();
        //   call_state_timer->start();
    }
}

void etu::accept_call_slot(long call_id)
{
    if(!linphone_core_accept_call(lc,get_call_id(call_id)))
        emit this->call_status(true,false,call_id);
}

void etu::end_call_slot(long call_id)
{
   // if(!ms_list_size(linphone_core_get_calls(lc)))
   //     ui->call_queue->clear();
   // else
   // {
        if(linphone_call_get_state(get_call_id(call_id)) == LinphoneCallStreamsRunning)
        {
            emit this->call_status(false,false,call_id);
        }
        linphone_core_terminate_call(lc,get_call_id(call_id));
   // }
}

void etu::hold_call_slot(long call_id)
{
    if(linphone_call_get_state(get_call_id(call_id)) == LinphoneCallPaused)
    {
        //qDebug() << "LinphoneCallPaused";
        linphone_core_resume_call(lc,get_call_id(call_id));
        emit this->call_status(true,false,call_id);
    }
    else if(linphone_call_get_state(get_call_id(call_id)) == LinphoneCallStreamsRunning)
    {
        // qDebug() << "LinphoneCallStreamsRunning";
        linphone_core_pause_call(lc,get_call_id(call_id));
        emit this->call_status(false,true,call_id);
    }
}

void etu::check_call_state(LinphoneCall *call)
{
    int counter=1;
    for (counter = 1;counter<Calls_list.size();counter++)
    {
        if(call == Calls_list.at(counter-1))
            break;
    }
     ui->call_queue->removeItemWidget(call_reference.at(counter-1));
    qDebug() << "Call with id = " << counter << "terminated";
    if(!(ms_list_size(linphone_core_get_calls(lc))))
    {
        emit back_clicked();
        ui->call_queue->clear();
        Calls_list.clear();
        call_reference.clear();
    }
}

LinphoneCall *etu::get_call_id(long call_id)
{
    LinphoneCall *current_call;
    const MSList *multiple_calls;
    multiple_calls = linphone_core_get_calls(lc);
    if(multiple_calls == NULL)
        qDebug() << "There Are No Calls" ;
    for (;multiple_calls!=NULL;multiple_calls=multiple_calls->next)
    {
        current_call=(LinphoneCall*)multiple_calls->data;
        // if(counter == call_id)
        if(linphone_call_get_user_pointer (current_call) == (void *)call_id )
        {
            return current_call;
        }
    }
}


