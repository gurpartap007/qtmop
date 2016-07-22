#include "etu.h"
#include "ui_etu.h"
#include "skipbutton.h"
bool CallOutgoingRinging=false;
bool CallOutgoingEarlyMedia=false;
bool CallConnected=false;
bool CallStreamsRunning=false;
bool CallEnd=false;
bool CallError=false;
bool isIncomingCall= false;
LinphoneCall *call;
int call_id;
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
    timer->start(5);
}

void etu::incoming_call_handler()
{
    QPixmap green_answer_button(":/images/green_call_button.png");
    QPixmap red_terminate_button(":/images/red_stop_button.png");
    QIcon answer_button_icon(green_answer_button);
    QIcon terminate_button_icon(red_terminate_button);
    QPushButton *answer_button,*terminate_button;
    QLabel *station_name;
    QListWidgetItem *item;
    QWidget *widget;
    QHBoxLayout *widgetLayout;
    QSpacerItem *spacer_left,*spacer_right;
    station_name_font = new QFont;
    station_name_font->setFamily("Sans Serif");
    station_name_font->setPointSize(14);
    station_name_font->setBold(true);
    station_name_font->setCapitalization(QFont::SmallCaps);
    station_name = new QLabel ;
    widget = new QWidget(this);
    answer_button = new QPushButton();
    terminate_button = new QPushButton();
    widgetLayout = new QHBoxLayout;
    widgetLayout->setMargin(3);
    item = new QListWidgetItem();
    connect(answer_button,SIGNAL(clicked()),this,SLOT(on_accept_call_button_clicked()));
    connect(terminate_button,SIGNAL(clicked()),this,SLOT(on_end_call_button_clicked()));
    spacer_left = new QSpacerItem(1,1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    spacer_right = new QSpacerItem(1,1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    answer_button -> setMinimumSize(QSize(60,30));
    answer_button->setIcon(answer_button_icon);
    answer_button->setIconSize(QSize(50,50));
    terminate_button -> setMinimumSize(QSize(60,30));
    terminate_button->setIcon(terminate_button_icon);
    terminate_button->setIconSize(QSize(50,50));
    station_name-> setFont(*station_name_font) ;
    answer_button -> setStyleSheet("QPushButton{ background-color: rgba(0,179,0,50); }QPushButton:pressed{background-color: rgb(0, 100,0); }");
    terminate_button -> setStyleSheet("QPushButton{ background-color: rgba(179,0,0,50); }QPushButton:pressed{background-color: rgb(100,0,0); }");
    station_name-> setStyleSheet("color: rgb(255,255,255)");
    widgetLayout-> addWidget(answer_button)    ;
    widgetLayout-> addWidget(terminate_button)    ;
    widgetLayout-> addSpacerItem(spacer_left);
    widgetLayout-> addWidget(station_name)   ;
    widgetLayout-> addSpacerItem(spacer_right);
    widgetLayout-> setAlignment(answer_button,Qt::AlignLeft);
    widgetLayout-> setAlignment(terminate_button,Qt::AlignLeft);
    widgetLayout-> setAlignment(station_name,Qt::AlignRight);
    widget      -> setLayout(widgetLayout);
    widget      -> setStyleSheet("background-color: rgb(0,0,100);");
    station_name->setText("ETB ID: 1");
    ui->call_queue-> addItem(item);
    item-> setSizeHint(answer_button->minimumSizeHint());
    ui->call_queue -> setItemWidget(item,widget);
}

void qcall_state_changed(LinphoneCore *lc, LinphoneCall *call, LinphoneCallState cstate, const char *msg)
{

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
        emit new_incoming_call();
        isIncomingCall = false;
    }
}

void etu::on_accept_call_button_clicked()
{
    const MSList *multiple_calls;
    int id ;
    int nb=ms_list_size(linphone_core_get_calls(lc));
    id = nb ;
    linphone_core_enable_echo_cancellation(lc,1);
    linphone_core_enable_echo_limiter(lc,1);
    if(nb==1)
        linphone_core_accept_call(lc,NULL);
    else
    {
        multiple_calls =linphone_core_get_calls(lc);
        for (;multiple_calls!=NULL;multiple_calls=multiple_calls->next)
        {
            call=(LinphoneCall*)multiple_calls->data;
            if (linphone_call_get_user_pointer (call)==(void*)id){
                break;
            }
        }
        linphone_core_accept_call(lc,call);
    }
}

void etu::on_end_call_button_clicked()
{
    ui->call_queue->takeItem(0);
    linphone_core_terminate_all_calls(lc);
}

void etu::on_mute_call_button_clicked()
{
    //  qDebug() << "mute button clicked";
}

void etu::on_bar_call_button_clicked()
{
    //   qDebug() << "Current Call is barred";

}
