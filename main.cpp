#include "mpd.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mpd w;
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.showFullScreen();

    return a.exec();
}
