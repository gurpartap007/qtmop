#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <QObject>
#include <QApplication>
#include <QDir>
#include "requesthandler.h"
#include "headers/httplistener.h"

class webserver : public QObject
{
    Q_OBJECT
public:
    explicit webserver(QObject *parent = 0);
     RequestHandler *httpserver;
         HttpListener* listener;
signals:

public slots:
     QString searchConfigFile();
};

#endif // WEBSERVER_H
