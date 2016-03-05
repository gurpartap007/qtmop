#include "etu.h"
#include "ui_etu.h"
bool CallOutgoingRinging=false;
bool CallOutgoingEarlyMedia=false;
bool CallConnected=false;
bool CallStreamsRunning=false;
bool CallEnd=false;
bool CallError=false;
bool isIncomingCall= false;
void etu::paintEvent(QPaintEvent* /*event*/)
{
    QColor backgroundColor ;
    backgroundColor.setRgb(173, 216, 230);
    backgroundColor.setAlpha(180);
    QPainter customPainter(this);
    customPainter.fillRect(rect(),backgroundColor);
}

bool etu::eventFilter(QObject *watched, QEvent *event)
{

    if (  event->type() == QEvent::MouseButtonPress )
    {
        ui->call_queue->clear();
        emit back_clicked();
    }


    return QObject::eventFilter(watched, event);
}
etu::etu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::etu)
{
    ui->setupUi(this);
    connect(ui->end_call_button,SIGNAL(clicked()),this,SLOT(end_current_call()));
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
    qDebug() << "Config file:" << config_file;
    LinphoneCoreVTable vtable = {0};
    vtable.call_state_changed = qcall_state_changed;
    lc = linphone_core_new(&vtable, config_file.toStdString().c_str() , NULL, this);
    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &etu::iterate);
    timer->start(5);
}

int etu::qlinphone_call(LinphoneCore *lc, char *ip_address)
{
    if ( ! ip_address || ! *ip_address )
    {
        return 0;
    }
    {
        LinphoneCallParams *cp=linphone_core_create_default_call_parameters (lc);

        if ( linphone_core_in_call(lc) )
        {
            qDebug() << "Terminate or hold on the current call first.\n";
            return 1;
        }

        if ( NULL == (call=linphone_core_invite_with_params(lc,ip_address,cp)) )
        {
            qDebug() << "Error from linphone_core_invite.\n";
        }
        else
        {
            qDebug() << "callee name " << ip_address;

        }

        linphone_call_params_destroy(cp);
    }
    return 0;
}

void qcall_state_changed(LinphoneCore *lc, LinphoneCall *call, LinphoneCallState cstate, const char *msg)
{

    switch(cstate){
    case LinphoneCallOutgoingRinging:
        qDebug() << "It is now ringing remotely";
        CallOutgoingRinging=true;

        break;
    case LinphoneCallOutgoingEarlyMedia:
        qDebug() << "Receiving some early media";
        CallOutgoingEarlyMedia=true;
        break;
    case LinphoneCallIncoming:
        qDebug() << "New Incoming Call";
        isIncomingCall = true;
        break;
    case LinphoneCallConnected:
        qDebug() << "We are connected ";
        CallConnected=true;
        break;
    case LinphoneCallStreamsRunning:
        qDebug() << "Media streams established ";
        CallStreamsRunning=true;
        break;
    case LinphoneCallEnd:
        qDebug() << "Call is terminated";
        CallEnd=true;
        break;
    case LinphoneCallError:
        qDebug() << "Call failure !";
        CallError=true;
        break;
    default:
        qDebug() << "Unhandled notification " << cstate;
    }
}

void etu::iterate()
{

    linphone_core_iterate(lc);
    if(CallConnected)
    {
        ui->call_queue->appendPlainText("Call Connected");
        CallConnected=false;
    }
    else if(CallOutgoingRinging)
    {
        ui->call_queue->appendPlainText("Call Outgoing ringing");
        CallOutgoingRinging=false;
    }
    else if(CallOutgoingEarlyMedia)
    {
        ui->call_queue->appendPlainText(("Call Outgoing Early Media"));
        CallOutgoingEarlyMedia=false;
    }
    else if(CallStreamsRunning)
    {
        ui->call_queue->appendPlainText("Call Streams Running");
        CallStreamsRunning=false;
    }
    else if(CallEnd)
    {
        ui->call_queue->appendPlainText("Call ended");
        CallEnd=false;
    }
    else if(CallError)
    {
       // ui->call_queue->appendPlainText("Call error");
        CallError=false;
    }
    else if(isIncomingCall)
    {
        QStringList caller_id;
        new_call=linphone_core_get_current_call(lc);
        emit new_incoming_call();
        caller_id = QString::fromUtf8(linphone_call_get_remote_address_as_string(new_call)).split('@');
        qDebug() << caller_id;
        qDebug() << linphone_call_get_remote_address_as_string(new_call);
        ui->call_queue->appendPlainText(caller_id.at(1));
        isIncomingCall = false;
    }
}

void etu::on_accept_call_button_clicked()
{
    int nb=ms_list_size(linphone_core_get_calls(lc));
    if(nb==1)
        linphone_core_accept_call(lc,NULL);
    else
        qlinphone_call(lc,(char *)"root@192.168.0.104");
}

void etu::on_end_call_button_clicked()
{
    linphone_core_terminate_call(lc,NULL);
}

void etu::on_mute_call_button_clicked()
{

}

void etu::on_bar_call_button_clicked()
{


}
