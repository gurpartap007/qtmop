#ifndef MPD_H
#define MPD_H

#include <QMainWindow>
#include "header.h"
#include "etu.h"
#include "route_selection.h"
#include "settings.h"
#include "public_announcement.h"
#include "webserver.h"
#include "xml_writer.h"
#include "lgps.h"
#include "intercom.h"



/** @brief Main MOP Device CLASS

    Detailed description follows here.
    @author Gurpartap Singh
    @date December 23 2015
    */
/** @file
 *
 */

namespace Ui {
class mpd;
}

class mpd : public QMainWindow
{
    Q_OBJECT

public:
    explicit mpd(QApplication *app_ptr,QWidget *parent = 0);
    ~mpd();
    route_selection *select_route;/**< Route Selection of train based on database and User input**/
    etu *emergency_talkback;/**< Emergency Talkback class to handle calls in emergency conditions in Coaches**/
    public_announcement *announcement;
    intercom  * interCom ;
    settings *system_settings;
    LGPS *gps;
    QPropertyAnimation *m_animation ;
    QTimer *timer_fade_in,*timer_fade_out;
    webserver *WebServer;
    xml_writer *xmlWriter;
    QFile  *etu_updating_file;
    QTimer *selection_timer;
private slots:
void on_select_route_clicked();
void on_etu_clicked();
void show_train_route_selection();
void close_etu_popup();
void on_settings_clicked();
void close_settings_popup();
void on_pa_clicked();
void on_intercom_clicked();
void incoming_call_notification();
void fade_in();
void fade_out();
void volume_control_slot();
void update_xml(QString mode);
void call_ended_from_guard();
void show_active_call();
private:
    Ui::mpd *ui;
    bool intercom_running ;
    bool volume_muted;
    bool announcement_running;
};


#endif // MPD_H
