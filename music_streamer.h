#ifndef MUSIC_STREAMER_H
#define MUSIC_STREAMER_H

#include <QWidget>
#include "header.h"
#include "database.h"
/** @brief Music streaming using mpdclient Api,MPD and ICECAST2 server

    Detailed description follows here.
    @author Gurpartap Singh
    @date December 23 2015
    */
/** @file
 *
 */
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
public slots:
    void on_next_clicked();/**< Start streaming Next song in current playlist**/
    void mplayer_start();/**< start mp3-player in background after 2 seconds of delay**/
    void on_prev_clicked();/**< Start streaming Previous song in current playlist **/
    void on_play_clicked();/**<Start streaming Current song in current playlist **/
    void on_pause_clicked();/**<Pause stream of Current song in current playlist**/
    void on_playlist_clicked();/**<Show Playlist retrieved from Sql Database**/
    void close_streaming();

private:
    Ui::music_streamer *ui;

};

#endif // MUSIC_STREAMER_H
