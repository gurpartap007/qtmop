#include "intercom.h"

static bool CallOutgoingRinging       = false;
static bool CallOutgoingEarlyMedia = false;
static bool CallConnected                 = false;
static bool CallStreamsRunning       = false;
static bool CallEnd                           = false;
static bool CallError                        = false;
static bool isIncomingCall               = false;
static bool call_connected               = false;
static bool call_paused                    = false;
static bool call_running                   = false;
LinphoneCall *active_call;
intercom::intercom(QWidget *parent) :
    QWidget(parent)
{
    active_call = NULL;
    lc = NULL;
   qlinphone_init();
}

intercom::~intercom()
{
}
void intercom::qlinphone_init()
{
    const char **dev;
    int i=0;
    QDir confDir = QDir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
    confDir.mkdir("Linphone");
    QString config_file = confDir.absolutePath() + "/Linphone/.linphonerc";
    LinphoneCoreVTable vtable = {0};
    vtable.call_state_changed = qcall_state_changed; // Calls State Call Back function
    lc = linphone_core_new(&vtable, config_file.toStdString().c_str() , NULL, this);
    iteration_timer = new QTimer(); // Timer to iterate linphone core and check call states at interval of 50 milli-seconds
    connect(iteration_timer,SIGNAL(timeout()), this, SLOT(iterate()));
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
void intercom::iterate()
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
        emit CallEnded();
        active_call = NULL;
        // check_call_state(active_call);
    }
    else if(CallError)
        CallError=false;
    else if(isIncomingCall)
    {
        linphone_core_accept_call(lc,active_call);
        emit talking_with_driver();
        isIncomingCall = false;
        /*   const MSList *multiple_calls;
        unique_call_id = ms_list_size(linphone_core_get_calls(lc));// get calls total count, it will be unique_id for new call
        multiple_calls = linphone_core_get_calls(lc); // get all calls from linphone core
        for (;multiple_calls!=NULL;multiple_calls=multiple_calls->next)
        {
            call=(LinphoneCall*)multiple_calls->data;
        }
        linphone_call_set_user_pointer (call,(void*)unique_call_id);// set unique_id to last call found in linklist, it is our new incoming call
        isIncomingCall = false;
        emit new_incoming_call();// signal to incoming_call_handler() function*/
    }
}

void intercom::talk_to_guard()
{
     if ( -1 ==   qlinphone_call(lc,"root@192.168.0.26"))
         qDebug() << "Unable to connect to Guard";
}

void intercom::end_intercom_call()
{
    linphone_core_terminate_call(lc,active_call);
}

int intercom::qlinphone_call(LinphoneCore *lc, char *ip_address)
{
    LinphoneCall *call1 = NULL;
    if ( ! ip_address || ! *ip_address )
       {
           return -1;

       }
          LinphoneCallParams *cp=linphone_core_create_call_params(lc,call1);

           if ( linphone_core_in_call(lc) )
           {
               qDebug() << "Terminate or hold on the current call first.\n";
               return 1;
           }
//		linphone_call_params_enable_audio_multicast(cp,true);
//		        linphone_core_set_audio_multicast_addr(lc,"root@224.0.0.1");
           if ( NULL == (active_call=linphone_core_invite_with_params(lc,ip_address,cp)) )
           {
               qDebug() << "Error from linphone_core_invite.\n";
           }
           else
           {
               linphone_call_enable_echo_cancellation(active_call,true);
           //   linphone_call_enable_echo_limiter(call,true);
               qDebug() << "callee name " << ip_address;
           }

           linphone_call_params_destroy(cp);
    return 0;
}
 void qcall_state_changed(LinphoneCore *lc, LinphoneCall *call, LinphoneCallState cstate, const char *msg)
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
      //  CallEnd = true;
        break;
    case LinphoneCallError:
        CallError=true;
        break;
    default:
        break;
    }
}
