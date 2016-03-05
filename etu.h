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

class etu : public QWidget
{
    Q_OBJECT

public:
    explicit etu(QWidget *parent = 0);
    ~etu();

    QPushButton *accept_call;
    QPushButton *hold_call;
    QPushButton *end_call;
    QHBoxLayout *buttons_layout;
    QPropertyAnimation *m_animation ;
    LinphoneCore* lc;
    const MSList *call_logs;
public slots:
    void end_current_call();
    void qlinphone_init();
    int qlinphone_call(LinphoneCore *lc, char *ip_address);
    void iterate();
signals:
    void call_ended();
    void back_clicked();
    void new_incoming_call();
protected:
     void paintEvent(QPaintEvent* event);
    virtual bool eventFilter( QObject * watched, QEvent * event );
private slots:
     void on_accept_call_button_clicked();

     void on_end_call_button_clicked();

     void on_mute_call_button_clicked();

     void on_bar_call_button_clicked();

private:
    Ui::etu *ui;
    LinphoneCall *call,*incoming_call,*new_call;
    friend void qcall_state_changed(LinphoneCore *lc, LinphoneCall *call, LinphoneCallState cstate, const char *msg);

};

#endif // ETU_H
