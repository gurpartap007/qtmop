#include "webserver.h"
//FileLogger *logger;
   QString configFileName;
webserver::webserver(QObject *parent) : QObject(parent)
{
    configFileName="/home/apaul/apaul_projects/qtmop/etc/Demo2.ini";
    qDebug() << "CONFIG FILE " << configFileName;
    // Configure logging into a file
  //  QSettings* logSettings=new QSettings(configFileName,QSettings::IniFormat);
   // logSettings->beginGroup("logging");
  // logger=new FileLogger(logSettings,10000);
   // logger->installMsgHandler();

    // Configure and start the TCP listener
    qDebug("ServiceHelper: Starting service");
    QSettings* listenerSettings=new QSettings(configFileName,QSettings::IniFormat);
    listenerSettings->beginGroup("listener");
    requestHandler = new RequestHandler;
    new HttpListener(listenerSettings,requestHandler);
 }

QString webserver::searchConfigFile()
{
    QString binDir=QApplication::applicationDirPath();
    QString appName=QApplication::applicationName();
    QString fileName(appName+".ini");
    QStringList searchList;
    searchList.append(binDir);
    searchList.append(binDir+"/etc");
    searchList.append(binDir+"/../etc");
    searchList.append(binDir+"/../../etc"); // for development without shadow build
    searchList.append(binDir+"/../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../../../"+appName+"/etc"); // for development with shadow build
    searchList.append(QDir::rootPath()+"etc/opt");
    searchList.append(QDir::rootPath()+"etc");

    foreach (QString dir, searchList)
    {
        QFile file(dir+"/"+fileName);
        if (file.exists())
        {
            // found
            fileName=QDir(file.fileName()).canonicalPath();
            qDebug("Using config file %s",qPrintable(fileName));
            return fileName;
        }
    }
}

