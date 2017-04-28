#ifndef PUBLIC_ANNOUNCEMENT_H
#define PUBLIC_ANNOUNCEMENT_H

#include <QWidget>
#include "header.h"
#include "music_streamer.h"
/** @brief Announcements for public from driver cabin.Consists of start and end announcement
 *  functions.

    Detailed description follows here.
    @author Gurpartap Singh
    @date December 23 2015
    */
/** @file
 *
 */
namespace Ui {
class public_announcement;
}

class public_announcement : public QWidget
{
    Q_OBJECT

public:
    explicit public_announcement(QWidget *parent = 0);
   // music_streamer *announcement_streamer;/**< mpdclient API based music streamer on localhost,port 6600S**/
    QProcess *gstreamer;
     QUdpSocket *command_channel;
    ~public_announcement();

signals:
    void back_clicked();

public slots:
    void start_gstreamer();
    void on_start_announcement_clicked();
    void on_end_announcement_clicked();

};

#endif // PUBLIC_ANNOUNCEMENT_H
