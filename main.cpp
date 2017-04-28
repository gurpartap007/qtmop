#include "mpd.h"
#include <QApplication>
mpd *w;
int main(int argc, char *argv[])
{
    QApplication *app = new QApplication(argc,argv) ;
    w = new mpd(app);
    w->showFullScreen();
    qDebug() << "Now showing Application as Fullscreen";
    return app->exec();
}
