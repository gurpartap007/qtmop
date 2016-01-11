#ifndef MPD_H
#define MPD_H

#include <QMainWindow>
#include "header.h"
#include "etu.h"
#include "music_streamer.h"
#include "route_selection.h"

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

private slots:
void on_menu_clicked();
void on_select_route_clicked();
void on_etu_clicked();

private:
    Ui::mpd *ui;
};


#endif // MPD_H
