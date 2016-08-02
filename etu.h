#ifndef ETU_H
#define ETU_H

#include <QWidget>
#include "header.h"
/** @brief Emergency Talkback class which involves handling of Calls like picking
 * call,holding a call,end a call and barring a user call.Call Queue from different coaches
 * is shown and driver can select the most important call first.

    Detailed description follows here.
    @author Gurpartap Singh
    @date December 23 2015
    */
/** @file
 *
 */
namespace Ui {
class etu;
}
void qcall_state_changed(LinphoneCore *lc, LinphoneCall *call, LinphoneCallState cstate, const char *msg);
void qlinphone_text_recieved(LinphoneCore *lc, LinphoneChatRoom *cr,const LinphoneAddress *from, const char *msg);
class etu : public QWidget
{
    Q_OBJECT

public:
    explicit etu(QWidget *parent = 0);
    void hello();
    ~etu();

public slots:
    void qlinphone_init();
    void incoming_call_handler();
    void iterate();
    void accept_call_slot(long call_id);
    void end_call_slot(long call_id);
    void hold_call_slot(long call_id);
    LinphoneCall *get_call_pointer(long call_id);
    void mute_microphone(bool mic_mute);
    void bar_call_slot(long call_id);

signals:
    void call_ended();
    void back_clicked();
    void new_incoming_call();
    void inialize_rabb_nu_lekha_server();
    void call_status(bool,bool,long);
    void mute_mic(bool);

protected:
     void paintEvent(QPaintEvent* event);
    virtual bool eventFilter( QObject * watched, QEvent * event );

private:
    Ui::etu *ui;
    QTimer *call_state_timer;
    LinphoneCall *call;
    QFont *station_name_font;
    LinphoneCore       *lc;
    const MSList       *call_logs;
    void check_call_state(LinphoneCall *call);
    friend void qcall_state_changed(LinphoneCore *lc, LinphoneCall *call, LinphoneCallState cstate, const char *msg);
    friend void qlinphone_text_recieved(LinphoneCore *lc, LinphoneChatRoom *cr,const LinphoneAddress *from, const char *msg);

};

#endif // ETU_H
