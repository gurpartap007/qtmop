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
public slots:
    void end_current_call();
signals:
    void call_ended();
    void back_clicked();
protected:
     void paintEvent(QPaintEvent* event);
    virtual bool eventFilter( QObject * watched, QEvent * event );
private:
    Ui::etu *ui;
};

#endif // ETU_H
