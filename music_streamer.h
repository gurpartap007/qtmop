#ifndef MUSIC_STREAMER_H
#define MUSIC_STREAMER_H

#include <QWidget>
#include <QUdpSocket>
#include <QThread>
#include "header.h"
#include "database.h"
#include <QString>
/** @brief Music streaming using mpdclient Api,MPD and ICECAST2 server

    Detailed description follows here.
    @author Gurpartap Singh
    @date December 23 2015
    */
/** @file
 *
 */
class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};
namespace Ui {
class music_streamer;
}

class music_streamer : public QWidget
{
    Q_OBJECT

public:

    explicit music_streamer(QWidget *parent = 0);
    ~music_streamer();
    database *bus_database;/**< database connection to BUS_PIS Database in sql**/
    mpd_connection *conn;/**< connection to mpd server**/
    struct mpd_status * status;/**< MPD daemon connection status and to fetch various information from mpd**/
    struct mpd_song *song;/**< Structure to store song information returned from MPD daemon**/
    QTimer *player_timer;/**< Timer to delay the execution of mp3 player because stream is not availble for first 1-2 seconds **/
    const struct mpd_audio_format *audio_format;/**< Structure to store format of currently played song returned by MPD**/
    QProcess *player;/**< MP3 player used to play stream(mp3-decoder)...very fast playback with minimum latency**/
    QString mpd_music_path;/**<MPD music path for storing songs,playlists **/
    bool player_started;
    QTimer *mpd_timer;
    QString data_set_name;
    QStringList eng_playlist,hindi_playlist,reg_playlist;
    QStringList  replace_voice_delimiters_eng(QString original_string);
    QStringList  replace_voice_delimiters_hindi(QString original_string);
    QStringList  replace_voice_delimiters_reg(QString original_string);
    QUdpSocket *command_channel;
    QUdpSocket *playlists_channel;
    QByteArray command_data;
    QByteArray playlists_data;

public slots:
    void on_next_clicked();    /**< Start streaming Next song in current playlist********/
    void mplayer_start();      /**< start mp3-player in background  2 seconds of delay**/
    void on_prev_clicked();    /**< Start streaming Previous song in current playlist */
    void on_play_clicked();    /**<Start streaming Current song in current playlist **/
    void on_pause_clicked();   /**<Pause stream of Current song in current playlist**/
    void on_playlist_clicked();/**<Show Playlist retrieved from Sql Database********/
    void close_streaming();
    void create_announcement_playlist(QString func_code);
    void check_mpd_status();
    void send_command_to_player(int command);
    void send_playlists_to_player();


private:
    Ui::music_streamer *ui;

protected:

};

#endif // MUSIC_STREAMER_H
