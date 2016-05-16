#ifndef MUSIC_STREAMER_H
#define MUSIC_STREAMER_H

#include <QWidget>
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
    QString data_set_name;

public slots:
    void on_next_clicked();    /**< Start streaming Next song in current playlist********/
    void mplayer_start();      /**< start mp3-player in background  2 seconds of delay**/
    void on_prev_clicked();    /**< Start streaming Previous song in current playlist */
    void on_play_clicked();    /**<Start streaming Current song in current playlist **/
    void on_pause_clicked();   /**<Pause stream of Current song in current playlist**/
    void on_playlist_clicked();/**<Show Playlist retrieved from Sql Database********/
    void close_streaming();

/*
    *MY LIFE*
        #akhaan charriaan te mushaan kharriaan, rakhde aa shoki sardar ni#
        #groomed and look smart to girls and other people#
        #People impressed by technical knowledge and brilliant technical skills of mine#
        #mere pind de log mainu projects bnaun nu te koi navi technique develop karan nu kehange#
        #Main ohnaa vaaste koi eho jehi device invent karooga jo ohna nu help karegi te oh mere electronics engineer hon te maan karange#
        #Mere maa baap nu log pushange ki jo eh akhbaar vich new technology baare khabar lagi hai ke eh tuhada munda hai... my mummy-papa proudly say- YES#
        #Mere dost jadon meri gal karnge te oh kehange... gurpartap te mere naal parrdaa reha hai... asi ikathe match khelde rahe haan... chacha bhinda will proud of me#
        #meri body v darshany hovegi te oh hairaan honge ke delhi varge shehar vich rehke naal job te baaki saare kam karde hoye body kiven bnaa layi..#
        #Oh maithon body te lal rang da secret pushange te main iko gal kahanga..#
        #What your mind can believe or concieve, it can achieve#
        #meri impressive speech naal har koi mere naal apniaan problems discuss karega... main kise da vi dil nahi torraanga te jini help possibly ho sakdi hai.. oh krangaa#
        #Sports ne mere sareer nu fit-faat rakheyaa hovegaa te main ghode varga jatt lagangaa... doojiaan nu thakavat jaldi hovegi but I will not stop by small and unusual problems or blind circumstances#
        #Zindagi vich kite v koi aukhi ghadi ban jaave taan main gurbani da sahara lvangaa te parmatma nu ardas karanga ke hun tu hi kuj kar sakda hai... eh hun mere vas ton baahar hai#
        #main apne motive nu saari umar nahi bhulanga.. main steve jobs di traah hatke sochangaa te apne motive nu achieve karan layi kise hadd tak chlaa javangaa#
        #Apne aap nu new ideas naal bharan layi te self improvement di paurri charrde rehan layi motivational books parraangaa#
        #Apni khuraak poori vadiaa te healthy rakhangaa te ohde vich eni energy hoya karegi ke poora din main taro tazaa rahangaa#
        #Example of my persistent or regularity is followed by my neighborers and friends... main jis kam baare sochdaa haaan ousnu kise v keemat te khatam karke hi dum lainda haan.. and this is my PEHCHAAN#
*/

private:
    Ui::music_streamer *ui;

protected:

};

#endif // MUSIC_STREAMER_H
