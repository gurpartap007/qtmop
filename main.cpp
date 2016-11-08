#include "mpd.h"
#include <QApplication>
mpd *w;
int main(int argc, char *argv[])
{
    QApplication *app = new QApplication(argc,argv) ;
    qDebug() << "Main Application Executed";
    w = new mpd(app);
    qDebug() << "Calling Constructor of mpd class";
    w->show();
    qDebug() << "Now showing Application as Fullscreen";

    /**************************************************************/
/*    qDebug() << "ADDRESS of App in webserver()" << app;
    QString configFileName="/home/apaul/apaul_projects/qtmop/etc/Demo2.ini";
    qDebug() << "CONFIG FILE " << configFileName;
    // Configure logging into a file
    QSettings* logSettings=new QSettings(configFileName,QSettings::IniFormat);
    logSettings->beginGroup("logging");
  //  logger=new FileLogger(logSettings,10000,app);
  //  logger->installMsgHandler();

    // Configure and start the TCP listener
    qDebug("ServiceHelper: Starting service");
    QSettings* listenerSettings=new QSettings(configFileName,QSettings::IniFormat,app);
    listenerSettings->beginGroup("listener");
    new HttpListener(listenerSettings,new RequestHandler(app),app);*/

    /**************************************************************/
    return app->exec();
    qDebug() << "Enters the main Event loop and waits until exit() is called";
}
