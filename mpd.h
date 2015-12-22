#ifndef MPD_H
#define MPD_H

#include <QMainWindow>
#include "header.h"

namespace Ui {
class mpd;
}

class mpd : public QMainWindow
{
    Q_OBJECT

public:
    explicit mpd(QWidget *parent = 0);
    ~mpd();

    char *command;
    struct mpd_status * status;
    struct mpd_song *song;

    const struct mpd_audio_format *audio_format;

public slots:
    void on_next_clicked();
    void print_tag(const struct mpd_song *, enum mpd_tag_type ,const char *);

private slots:
    void on_prev_clicked();

    void on_play_clicked();

    void on_pause_clicked();

    void on_song_info_clicked();

private:
    Ui::mpd *ui;
};


#endif // MPD_H
