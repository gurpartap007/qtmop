#ifndef INTERCOM_H
#define INTERCOM_H

#include <QWidget>
#include "header.h"


void qcall_state_changed(LinphoneCore *lc, LinphoneCall *call, LinphoneCallState cstate, const char *msg);
class intercom : public QWidget
{
    Q_OBJECT

public:
    explicit intercom(QWidget *parent = 0);
    ~intercom();
    void qlinphone_init();
    LinphoneCore       *lc;
    QTimer *iteration_timer ;
signals:
    void CallEnded();
    void talking_with_driver();
public slots:
    void iterate();
    int qlinphone_call(LinphoneCore *lc, char * ipaddr);
    void talk_to_guard();
    void end_intercom_call();
protected:
    friend void qcall_state_changed(LinphoneCore *lc, LinphoneCall *call, LinphoneCallState cstate, const char *msg);

private slots:
};

#endif // INTERCOM_H
