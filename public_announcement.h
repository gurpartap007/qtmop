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
    music_streamer *announcement_streamer;/**< mpdclient API based music streamer on localhost,port 6600S**/
    ~public_announcement();

signals:
    void back_clicked();

protected:
    void paintEvent(QPaintEvent* event);
    virtual bool eventFilter( QObject * watched, QEvent * event );

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::public_announcement *ui;
};

#endif // PUBLIC_ANNOUNCEMENT_H
