#ifndef MPD_H
#define MPD_H

#include <QMainWindow>
#include "header.h"
#include "etu.h"
#include "music_streamer.h"
#include "route_selection.h"
#include "settings.h"
#include "public_announcement.h"

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
    explicit mpd(QWidget *parent = 0);
    ~mpd();
    music_streamer *announcement_streamer;/**< mpdclient API based music streamer on localhost,port 6600S**/
    route_selection *select_route;
    etu *emergency_talkback;
    settings *system_settings;
    public_announcement *announcement;

private slots:
void on_select_route_clicked();
void on_etu_clicked();
void show_train_route_selection();
void close_etu_popup();
void on_settings_clicked();
void close_settings_popup();
void on_pa_clicked();
void close_announcement_popup();

private:
    Ui::mpd *ui;
};


#endif // MPD_H
