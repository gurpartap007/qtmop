/**
  @file
  @author Stefan Frings
*/

#include <logging/filelogger.h>
#include "requesthandler.h"


/** Logger class */
extern FileLogger* logger;
extern QString configFileName;
RequestHandler::RequestHandler(QObject* parent)
    :HttpRequestHandler(parent)
{
    qDebug("RequestHandler: created");
    QFileInfo configFile(configFileName);
    docroot= configFile.absolutePath();
    docroot = docroot + "/docroot";
    file.setFileName(docroot);
    encoding = "UTF-8";
}


RequestHandler::~RequestHandler()
{
    qDebug("RequestHandler: deleted");
}


void RequestHandler::service(HttpRequest& request, HttpResponse& response)
{
    QByteArray path=request.getPath();
    if (path.startsWith("/RouteRun"))
    {
        QByteArray train_number = request.getParameter("trainumber");
        qDebug() << "Selected route" << train_number ;
    }
    if (QFileInfo(docroot+path).isDir())
    {
        path+="/index.html";
    }
    QFile file(docroot+path);
    if (file.open(QIODevice::ReadOnly))
    {
        // Set a response header
        setContentType(path,response) ;
        while (!file.atEnd() && !file.error())
        {
            QByteArray buffer=file.read(65536);
            response.write(buffer);
            qDebug("RequestHandler: finished request");
        }
    }
}
void RequestHandler::setContentType(QString fileName, HttpResponse& response) const
{
    if (fileName.endsWith(".png"))
    {
        response.setHeader("Content-Type", "image/png");
    }
    else if (fileName.endsWith(".jpg"))
    {
        response.setHeader("Content-Type", "image/jpeg");
    }
    else if (fileName.endsWith(".gif"))
    {
        response.setHeader("Content-Type", "image/gif");
    }
    else if (fileName.endsWith(".pdf"))
    {
        response.setHeader("Content-Type", "application/pdf");
    }
    else if (fileName.endsWith(".txt"))
    {
        response.setHeader("Content-Type", qPrintable("text/plain; charset="+encoding));
    }
    else if (fileName.endsWith(".html") || fileName.endsWith(".htm"))
    {
        response.setHeader("Content-Type", qPrintable("text/html; charset="+encoding));
    }
    else if (fileName.endsWith(".css"))
    {
        response.setHeader("Content-Type", "text/css");
    }
    else if (fileName.endsWith(".js"))
    {
        response.setHeader("Content-Type", "text/javascript");
    }
    else if (fileName.endsWith(".svg"))
    {
        response.setHeader("Content-Type", "image/svg+xml");
    }
    else if (fileName.endsWith(".woff"))
    {
        response.setHeader("Content-Type", "font/woff");
    }
    else if (fileName.endsWith(".woff2"))
    {
        response.setHeader("Content-Type", "font/woff2");
    }
    else if (fileName.endsWith(".ttf"))
    {
        response.setHeader("Content-Type", "application/x-font-ttf");
    }
    else if (fileName.endsWith(".eot"))
    {
        response.setHeader("Content-Type", "application/vnd.ms-fontobject");
    }
    else if (fileName.endsWith(".otf"))
    {
        response.setHeader("Content-Type", "application/font-otf");
    }
    // Todo: add all of your content types
    else
    {
        qDebug("StaticFileController: unknown MIME type for filename '%s'", qPrintable(fileName));
    }
}

