#include "mpd.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Main Application Executed";
    mpd w;
    qDebug() << "Calling Constructor of mpd class";
    w.show();
    qDebug() << "Now showing Application as Fullscreen";
    return a.exec();
    qDebug() << "Enters the main Event loop and waits until exit() is called";
}
