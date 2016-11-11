#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <QObject>
#include <QApplication>
#include <QDir>
#include "requesthandler.h"
#include "headers/httplistener.h"
#include "logging/filelogger.h"

class webserver : public QObject
{
    Q_OBJECT
public:
    explicit webserver(QObject *parent = 0);
     RequestHandler *httpserver;
         HttpListener* listener;
        RequestHandler *requestHandler ;
signals:
         void write_train_routes(QString selected_train_route);

public slots:
     QString searchConfigFile();
};

#endif // WEBSERVER_H
