#include "etu.h"
#include "ui_etu.h"
#include "etubutton.h"
bool CallOutgoingRinging    = false;
bool CallOutgoingEarlyMedia = false;
bool CallConnected          = false;
bool CallStreamsRunning     = false;
bool CallEnd                = false;
bool CallError              = false;
bool isIncomingCall         = false;
bool call_connected         = false;
bool call_paused            = false;
bool call_running           = false;
long unique_call_id;
static LinphoneCall *active_call;
QList <QListWidgetItem *> call_reference; // List of Call Notification widget item which includes call control buttons and caller name
QList <LinphoneCall *> Calls_list;// List of incoming calls
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
        emit back_clicked();
    }
    return QObject::eventFilter(watched, event);
}

etu::etu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::etu)
{
    ui->setupUi(this);
    int i=0;
    connect(this,SIGNAL(new_incoming_call()),this,SLOT(incoming_call_handler()));
    connect(this,SIGNAL(mute_mic(bool)),this,SLOT(mute_microphone(bool)));
    qlinphone_init();
    ui->left_area->installEventFilter(this);
    ui->right_area->installEventFilter(this);
    ui->bottom_area->installEventFilter(this);
    /************************************ mcu_stat.xml file Updation ***************************************/
    etu_updating_file = new QFile("/home/apaul/apaul_projects/qtmop/etc/docroot/mcu_stat.xml");
    if (!etu_updating_file->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "unable to open xml file";
        return;
    }
    QByteArray xmlData(etu_updating_file->readAll());
    QDomDocument doc("mcu_stat");
    QDomNodeList n;
    doc.setContent(xmlData);
    QDomElement root = doc.firstChildElement("CATALOG");
    QDomElement statheader = root.firstChildElement("STATHEADER");
    statheader.setAttribute("Mode","IDLE");
    statheader.setAttribute("GSMSTAT","Online");
    QDomElement ETUSTAT = root.firstChildElement("ETUSTAT");
    ETUSTAT.setAttribute("EtuOnline","0");
    ETUSTAT.setAttribute("EtuSelected","0");
    ETUSTAT.setAttribute("EtuState","standby");
    /*  for(i=0;i<10;i++)
    {
    QDomElement elem = doc.createElement("ETUS");
    elem.setAttribute("IP", "255.255.255.255");
     elem.setAttribute("NAME", "ETU 2");
      elem.setAttribute("COACH", QString::number(i));
       elem.setAttribute("STATUS", "OK");
    ETUSTAT.appendChild(elem);
    }*/
    n = ETUSTAT.childNodes();
    /*   for(i=0;i<n.size();i++)
     ETUSTAT.removeChild(n.at(1));*/
    while(!n.isEmpty())
    {
        QDomNode node = n.at(0);
        node.parentNode().removeChild(node);
    }
    etu_updating_file->resize(0);
    QTextStream stream(etu_updating_file);
    stream.setDevice(etu_updating_file);
    doc.save(stream, 4);
    etu_updating_file->close();


    /*******************************************************************************************************/
}

void etu::hello()
{

}


etu::~etu()
{
    delete ui;
}
//******************************************************************************************************************/
//                        INITIALIZE THE NEW LINPHONE CORE AND SET DIFFERENT SETTINGS                                  /
//******************************************************************************************************************/
void etu::qlinphone_init()
{
    const char **dev;
    int i=0;
    QDir confDir = QDir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
    confDir.mkdir("Linphone");
    QString config_file = confDir.absolutePath() + "/Linphone/.linphonerc";
    LinphoneCoreVTable vtable = {0};
  //  vtable.call_state_changed = qcall_state_changed; // Calls State Call Back function
    vtable.text_received = qlinphone_text_recieved;
    lc = linphone_core_new(&vtable, config_file.toStdString().c_str() , NULL, this);
    QTimer *iteration_timer = new QTimer(); // Timer to iterate linphone core and check call states at interval of 50 milli-seconds
    connect(iteration_timer, &QTimer::timeout, this, &etu::iterate);
    iteration_timer->start(50);
    dev=linphone_core_get_sound_devices(lc);
    for(i=0; dev[i]!=NULL; ++i)
    {
        qDebug() << i << dev[i];
    }
    linphone_core_set_ringer_device(lc,dev[1]);
    linphone_core_set_playback_device(lc,dev[1]);
    linphone_core_set_capture_device(lc,dev[1]);
    qDebug() << "Ringer device: " << linphone_core_get_ringer_device(lc);
    qDebug() << "Playback device: " << linphone_core_get_playback_device(lc);
    qDebug() << "Capture device: " << linphone_core_get_capture_device(lc);
    linphone_core_enable_echo_cancellation(lc,1);// Enable Echo Cancellation
    linphone_core_enable_echo_limiter(lc,1);// Enable Echo Limiter
    linphone_core_set_inc_timeout(lc,60);// Set automatic termination of incoming Call to 1 minute
}
//*********************************************************************************************************************/
//    HANDLE NEW INCOMING CALLS AND DO FOLLOWING TASKS:                                                                           /
//    1. Create New Notification Widget of Each New Call With Answer,Terminate,Hold and Bar Call Controls button  /
//    2. Set Caller Name or ETB Unit Id in Each Call Notification.                                                                                    /
//    3. Save reference of Calls Notification widget pointer for further operations                                                          /
//******************************************************************************************************************* /
void etu::incoming_call_handler()
{
    QStringList caller_ip;
    QPixmap green_answer_button(":/images/green_call_button.png");// image for answer button
    QPixmap red_terminate_button(":/images/red_stop_button.png"); // image for terminate button
    QPixmap pix_hold_button(":/images/hold_call.png"); // image for hold button
    QPixmap pix_bar_button(":/images/end_call.png"); // image for bar button
    QIcon answer_button_icon(green_answer_button);
    QIcon terminate_button_icon(red_terminate_button);
    QIcon bar_button_icon(pix_bar_button);
    QIcon hold_button_icon(pix_hold_button);
    EtuButton *answer_button,*terminate_button,*hold_button,*bar_button;
    QLabel *station_name;
    QListWidgetItem *item;
    QWidget *widget;
    QHBoxLayout *widgetLayout;
    QSpacerItem *spacer_left,*spacer_right;
    station_name_font = new QFont;
    station_name_font -> setFamily("Sans Serif");
    station_name_font -> setPointSize(12);
    station_name_font -> setBold(false);
    station_name_font -> setCapitalization(QFont::SmallCaps);
    station_name      = new QLabel ;
    caller_ip = QString::fromLatin1(linphone_call_get_remote_address_as_string(call)).split('@');// get caller Ip Address for current Call
    station_name->setText(caller_ip.at(1));
    call_history_lookup.insert(caller_ip.at(1),(long)unique_call_id);
    widget            = new QWidget(this);
    answer_button     = new EtuButton(unique_call_id,answer);
    terminate_button  = new EtuButton(unique_call_id,terminate);
    hold_button       = new EtuButton(unique_call_id,hold);
    bar_button        = new EtuButton(unique_call_id,bar);
    widgetLayout      = new QHBoxLayout;
    item              = new QListWidgetItem();
    connect(answer_button,&EtuButton::EtuButton_clicked,this,&etu::accept_call_slot);
    connect(this,SIGNAL(call_status(bool,bool,long)),answer_button,SLOT(check_call_status(bool,bool,long)));
    connect(terminate_button,SIGNAL(EtuButton_clicked(long)),this,SLOT(end_call_slot(long)));
    connect(this,SIGNAL(call_status(bool,bool,long)),hold_button,SLOT(check_call_status(bool,bool,long)));
    connect(hold_button,SIGNAL(EtuButton_clicked(long)),this,SLOT(hold_call_slot(long)));
    connect(bar_button,SIGNAL(EtuButton_clicked(long)),this,SLOT(bar_call_slot(long)));
    spacer_left       = new QSpacerItem(1,1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    spacer_right      = new QSpacerItem(1,1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    widgetLayout     -> setMargin(3);
    answer_button    -> setMinimumSize(QSize(60,30));
    answer_button    -> setIcon(answer_button_icon);
    answer_button    -> setIconSize(QSize(50,50));
    terminate_button -> setMinimumSize(QSize(60,30));
    terminate_button -> setIcon(terminate_button_icon);
    terminate_button -> setIconSize(QSize(50,50));
    hold_button      -> setMinimumSize(QSize(60,30));
    hold_button      -> setIcon(hold_button_icon);
    hold_button      -> setIconSize(QSize(50,50));
    bar_button       -> setMinimumSize(QSize(60,30));
    bar_button       -> setIcon(bar_button_icon);
    bar_button       -> setIconSize(QSize(50,50));
    station_name     -> setFont(*station_name_font) ;
    answer_button   -> setStyleSheet("QPushButton{ background-color: rgba(0,230,0,50); }QPushButton:pressed{background-color: rgb(100,0,0); }");
    terminate_button -> setStyleSheet("QPushButton{ background-color: rgba(179,0,0,50); }QPushButton:pressed{background-color: rgb(100,0,0); }");
    bar_button       -> setStyleSheet("QPushButton{ background-color: rgba(230,230,230,50); }QPushButton:pressed{background-color: rgb(100,0,0); }");
    station_name     -> setStyleSheet("color: rgb(255,255,255)");
    if(call_running)
    {
        answer_button-> setDisabled(true);
        answer_button   -> setStyleSheet("QPushButton{ background-color: rgba(230,230,230,50); }QPushButton:pressed{background-color: rgb(100,0,0); }");
    }
    widgetLayout     -> addWidget(answer_button);
    widgetLayout     -> addWidget(terminate_button);
    widgetLayout     -> addWidget(hold_button);
    widgetLayout     -> addWidget(bar_button);
    widgetLayout     -> addSpacerItem(spacer_left);
    widgetLayout     -> addWidget(station_name)   ;
    widgetLayout     -> addSpacerItem(spacer_right);
    widgetLayout     -> setAlignment(answer_button,Qt::AlignLeft);
    widgetLayout     -> setAlignment(terminate_button,Qt::AlignLeft);
    widgetLayout     -> setAlignment(station_name,Qt::AlignRight);
    widgetLayout     -> setAlignment(bar_button,Qt::AlignLeft);
    widget                -> setLayout(widgetLayout);
    widget                -> setStyleSheet("background-color: rgb(0,0,100);");
    item                    -> setSizeHint(answer_button->minimumSizeHint());
    ui->call_queue->insertItem(unique_call_id-1,item); // Insert Current Call Notification along with buttons and ETB no in window
    ui->call_queue -> setItemWidget(item,widget);
    call_reference.append(item); //get Current Call notification window reference in QList call_reference
    /****************************** UPDATE WEB USER INTERFACE *******************************/

    if (!etu_updating_file->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "unable to open xml file";
        return;
    }
    QByteArray xmlData(etu_updating_file->readAll());
    QDomDocument doc("mcu_stat");
    QDomNodeList n;
    doc.setContent(xmlData);
    QDomElement root = doc.firstChildElement("CATALOG");
    QDomElement statheader = root.firstChildElement("STATHEADER");
    statheader.setAttribute("Mode","ETU");
    QDomElement ETUSTAT = root.firstChildElement("ETUSTAT");
    ETUSTAT.setAttribute("EtuOnline",QString::number( unique_call_id));
    ETUSTAT.setAttribute("EtuSelected","0");
    ETUSTAT.setAttribute("EtuState","standby");
    QDomElement elem = doc.createElement("ETUS");
    elem.setAttribute("IP", caller_ip.at(1));
    elem.setAttribute("NAME", caller_ip.at(1));
    elem.setAttribute("COACH",caller_ip.at(1));
    elem.setAttribute("STATUS", "OK");
    ETUSTAT.appendChild(elem);
    etu_updating_file->resize(0);
    QTextStream stream(etu_updating_file);
    stream.setDevice(etu_updating_file);
    doc.save(stream, 4);
    etu_updating_file->close();
    /************************************************************************************************/
}

/*void qcall_state_changed(LinphoneCore *lc, LinphoneCall *call, LinphoneCallState cstate, const char *msg)
{
    active_call = call;
    switch(cstate)
    {
    case LinphoneCallOutgoingRinging:
        CallOutgoingRinging=true;
        break;
    case LinphoneCallOutgoingEarlyMedia:
        CallOutgoingEarlyMedia=true;
        break;
    case LinphoneCallIncoming:
        isIncomingCall = true;
        Calls_list.append(call);
        break;
    case LinphoneCallConnected:
        CallConnected=true;
        break;
    case LinphoneCallStreamsRunning:
        CallStreamsRunning=true;
        break;
    case LinphoneCallEnd:
        CallEnd=true;
        break;
    case LinphoneCallReleased:
        break;
    case LinphoneCallError:
        CallError=true;
        break;
    default:
        break;
    }
}*/
//*************************************************************************************************************/
//            ITERATE EVERY 50 MILLI-SECONDS TO GET NOTIFICATIONS ABOUT CALLS AND CHECK FOR NEW CALLS          /
//            STATES OF CALLS AS SET BY LINPHONECORE                                                          /
// ************************************************************************************************************/
void etu::iterate()
{
    linphone_core_iterate(lc); // Poll linphone main core
    if(CallConnected)
        CallConnected=false;
    else if(CallOutgoingRinging)
        CallOutgoingRinging=false;
    else if(CallOutgoingEarlyMedia)
        CallOutgoingEarlyMedia=false;
    else if(CallStreamsRunning)
        CallStreamsRunning=false;
    else if(CallEnd)
    {
        CallEnd=false;
        check_call_state(active_call);
    }
    else if(CallError)
        CallError=false;
    else if(isIncomingCall)
    {
        const MSList *multiple_calls;
        unique_call_id = ms_list_size(linphone_core_get_calls(lc));// get calls total count, it will be unique_id for new call
        multiple_calls = linphone_core_get_calls(lc); // get all calls from linphone core
        for (;multiple_calls!=NULL;multiple_calls=multiple_calls->next)
        {
            call=(LinphoneCall*)multiple_calls->data;
        }
        linphone_call_set_user_pointer (call,(void*)unique_call_id);// set unique_id to last call found in linklist, it is our new incoming call
        isIncomingCall = false;
        emit new_incoming_call();// signal to incoming_call_handler() function
    }
}
//**********************************************************************************************/
//                                     ACCEPT CURRENT CALL                                      /
//**********************************************************************************************/
void etu::accept_call_slot(long call_id)
{
    if(!linphone_core_accept_call(lc,get_call_pointer(call_id)))//accept call with call_id
    {
        emit this->call_status(true,false,call_id);// signal to set disable accept buttons of all other calls
        call_running = true;
    }
}

//**********************************************************************************************/
//           END CURRENT CALL WHETHER IT IS PAUSED, CONNECTED OR INCOMING                       /
//**********************************************************************************************/
void etu::end_call_slot(long call_id)
{

    if(linphone_call_get_state(get_call_pointer(call_id)) == LinphoneCallStreamsRunning)
    {
        emit this->call_status(false,false,call_id);// signal to set states of buttons accordingly
    }
    linphone_core_terminate_call(lc,get_call_pointer(call_id));// terminate call with call_id
    call_running = false;

}
//**********************************************************************************************/
//                                HOLD CURRENT CALL IF IT IS CONNECTED                          /
// HOLD BUTTON HAS TWO STATES :                                                                 /
// 1.PAUSE CALL                                                                                 /
// 2.RESUME CALL                                                                                /
//**********************************************************************************************/
void etu::hold_call_slot(long call_id)
{
    if(linphone_call_get_state(get_call_pointer(call_id)) == LinphoneCallPaused)
    {
        //qDebug() << "LinphoneCallPaused";
        linphone_core_resume_call(lc,get_call_pointer(call_id));// resume call with Call_id
        emit this->call_status(true,false,call_id);
    }
    else if(linphone_call_get_state(get_call_pointer(call_id)) == LinphoneCallStreamsRunning)
    {
        // qDebug() << "LinphoneCallStreamsRunning";
        linphone_core_pause_call(lc,get_call_pointer(call_id));// pause call with Call_id
        emit this->call_status(false,true,call_id);
    }
}
//********************************************************************************************* *                                        /
//                                CHECK CALL STATE CONTINOUSLY                                                                                                 /
// IF CALL IS TERMINATED MANUALLY OR AUTOMATICALLY AFTER TIMEOUT :                                                          /
// 1.CLEAR CALL NOTIFICATION FROM CALLS WINDOW                                                                                                 /
// 2.IF TERMINATED CALL IS LAST CALL AMONG MULTIPLE CALLS, THEN CLEAR CALLS_LIST QLIST AND CLOSE /
//   ETU POPUP.                                                                                                                                                                      /
//************************************************************************************************************************/
void etu::check_call_state(LinphoneCall *call)
{
    int counter=1;
    QDomNodeList n;
    for (counter = 1;counter<Calls_list.size();counter++)  // iterate over total no. of simultenous calls
    {
        if(call == Calls_list.at(counter-1))
            break;
    }

    /***********************************  XML UPDATION OF TERMINATED CALL *******************************/
    if (!etu_updating_file->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "unable to open xml file";
        return;
    }
    QByteArray xmlData(etu_updating_file->readAll());
    QDomDocument doc("mcu_stat");
    doc.setContent(xmlData);
    QDomElement root = doc.firstChildElement("CATALOG");
    QDomElement ETUSTAT = root.firstChildElement("ETUSTAT");
    ETUSTAT.setAttribute("EtuOnline",QString::number(ms_list_size(linphone_core_get_calls(lc))));
    ETUSTAT.setAttribute("EtuState","standby");
    n = ETUSTAT.childNodes();
    ETUSTAT.removeChild(n.at(counter-1));
    etu_updating_file->resize(0);
    QTextStream stream(etu_updating_file);
    stream.setDevice(etu_updating_file);
    doc.save(stream, 4);
    etu_updating_file->close();



    /**************************************************************************************************************/
    qDebug() << "CALL ID OF TERMINATED CALL -----> " << counter;
    ui->call_queue->removeItemWidget(call_reference.at(counter-1));// clear call notification from calls window
    qDebug() << "Call with id = " << counter << "terminated";
    if(!(ms_list_size(linphone_core_get_calls(lc))))// If there are no calls
    {
        emit back_clicked(); // Close Etu Popup
        ui->call_queue->clear();//Clear Calls Notification Window
        Calls_list.clear(); // Clear Calls Pointer List
        call_reference.clear(); // Clear Calls NOTIFICATION WIDGETS List
        unique_call_id = 0;
    }
}

void qlinphone_text_recieved(LinphoneCore *lc, LinphoneChatRoom *cr, const LinphoneAddress *from, const char *msg)
{
    //     qDebug() <<  "Message received from " << linphone_address_as_string(from) <<  recieved_msg;
}
//********************************************************************************************* */
// GET CALL REFERENCE POINTER REQUESTED BY ANSWER,TERMINATE,HOLD OR BAR BUTTON                   /
// PARAMETER:                                                                                    /          /
// 1.CALL ID OF THE REQUESTED CALL                                                               /
//                                                                                               /
// RETURN: CALL POINTER (LinphoneCall * POINTER)                                                 /                                                                                   /
//***********************************************************************************************/
LinphoneCall *etu::get_call_pointer(long call_id)
{
    LinphoneCall *current_call;
    const MSList *multiple_calls;
    multiple_calls = linphone_core_get_calls(lc);// Get all calls from LINPHONECORE
    if(multiple_calls == NULL)
        qDebug() << "There Are No Calls" ;
    for (;multiple_calls!=NULL;multiple_calls=multiple_calls->next)//Iterate over all calls LINK-LIST
    {
        current_call=(LinphoneCall*)multiple_calls->data;
        if(linphone_call_get_user_pointer (current_call) == (void *)call_id )// Check whether Call ID MATCHED
        {
            return current_call;// This is Required Call
        }
    }
}

//*************************************************************************************************************/
//  MUTE OR UNMUTE MICROPHONE FOR ALL CALLS ACCORDING TO Volume_control on bottom right corner of Application  /
//*************************************************************************************************************/
void etu::mute_microphone(bool mic_mute)
{
    LinphoneInfoMessage *msg;
    msg = linphone_core_create_info_message(lc);
    if(mic_mute)
        linphone_core_mute_mic(lc,true);// Mute MicroPhone
    else
        linphone_core_mute_mic(lc,false);// Unmute MicroPhone
}

void etu::bar_call_slot(long call_id)
{
    LinphoneChatRoom *cr;
    cr = linphone_core_get_chat_room(lc,linphone_call_get_remote_address(get_call_pointer(call_id)));
    linphone_chat_room_send_message(cr,"barred,30");
    usleep(1000);
    end_call_slot(call_id);
}

void etu::accept_call_by_ip_address(QString ipaddr)
{
    long selected_call_id = call_history_lookup.value(ipaddr);
    if (!etu_updating_file->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "unable to open xml file";
        return;
    }
    QByteArray xmlData(etu_updating_file->readAll());
    QDomDocument doc("mcu_stat");
    doc.setContent(xmlData);
    QDomElement root = doc.firstChildElement("CATALOG");
    QDomElement ETUSTAT = root.firstChildElement("ETUSTAT");
    ETUSTAT.setAttribute("EtuSelected",QString::number( selected_call_id));
    ETUSTAT.setAttribute("EtuState","standby");
    etu_updating_file->resize(0);
    QTextStream stream(etu_updating_file);
    stream.setDevice(etu_updating_file);
    doc.save(stream, 4);
    etu_updating_file->close();
    accept_call_slot(selected_call_id);
}
void etu::terminate_call_by_ip_address(QString ipaddr)
{
    long selected_call_id = call_history_lookup.value(ipaddr);
    QDomNodeList n;
    end_call_slot(selected_call_id);
    if (!etu_updating_file->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "unable to open xml file";
        return;
    }
    QByteArray xmlData(etu_updating_file->readAll());
    QDomDocument doc("mcu_stat");
    doc.setContent(xmlData);
    QDomElement root = doc.firstChildElement("CATALOG");
    QDomElement ETUSTAT = root.firstChildElement("ETUSTAT");
    ETUSTAT.setAttribute("EtuOnline",QString::number(ms_list_size(linphone_core_get_calls(lc))));
    ETUSTAT.setAttribute("EtuState","standby");
    ETUSTAT.setAttribute("EtuSelected","0");
    n = ETUSTAT.childNodes();
    ETUSTAT.removeChild(n.at(selected_call_id-1));
    etu_updating_file->resize(0);
    QTextStream stream(etu_updating_file);
    stream.setDevice(etu_updating_file);
    doc.save(stream, 4);
    etu_updating_file->close();

}

void etu::hold_resume_call_by_ip_address(QString ipaddr)
{
    long selected_call_id = call_history_lookup.value(ipaddr);
    hold_call_slot(selected_call_id);
}


