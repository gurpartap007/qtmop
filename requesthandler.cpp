/**
  @file
  @author Stefan Frings
*/

#include <logging/filelogger.h>
#include "requesthandler.h"


/** Logger class */
extern FileLogger* logger;
extern QString configFileName;
bool routeRunFlag = true;
RequestHandler::RequestHandler(QObject* parent)
    :HttpRequestHandler(parent)
{
  //  qDebug("RequestHandler: created");
    QFileInfo configFile(configFileName);
    docroot= configFile.absolutePath();
    docroot = docroot + "/docroot";
    file.setFileName(docroot);
    encoding = "UTF-8";

}

RequestHandler::~RequestHandler()
{
    //qDebug("RequestHandler: deleted");
}

void RequestHandler::service(HttpRequest& request, HttpResponse& response)
{
    QByteArray path=request.getPath();
    if (path.startsWith("/RouteRun") && routeRunFlag)
    {
        QByteArray train_number = request.getParameter("trainumber");
     //   qDebug() << "Selected route" << train_number ;
        emit  write_train_routes(QString::fromLatin1(train_number));
        routeRunFlag = false;
    }

    else if(path.startsWith("/ETUSelection.html"))
    {
        QByteArray  accept_caller_ip = request.getParameter(("CALL"));
        QByteArray  disconnect_caller_ip = request.getParameter(("DISCONNECT"));
        QByteArray  hold_caller_ip = request.getParameter(("HOLD"));
        QByteArray  resume_caller_ip = request.getParameter(("RESUME"));
        if(accept_caller_ip.length())
        {
           qDebug() << "######### ACCEPT CALL selected ######### ";
           emit accept_selected_call(accept_caller_ip);
        }
        else  if(disconnect_caller_ip.length())
        {
            qDebug() << "######### DISCONNECT CALL selected ######### ";
            emit disconnect_selected_call(disconnect_caller_ip);
        }
        else  if(hold_caller_ip.length())
        {
            qDebug() << "######### HOLD CALL selected ######### ";
             emit hold_selected_call(hold_caller_ip);
        }
        else if(resume_caller_ip.length())
        {
            qDebug() << "######### RESUME CALL selected ######### ";
             emit resume_selected_call(resume_caller_ip);
        }
        return;
    }
    else if(path.startsWith("/ModeSelection.html"))
    {
    QByteArray selected_mode = request.getParameter("Mode");
    if(selected_mode == "PA")
        qDebug() << "######### PA MODE selected ######### ";
    else if(selected_mode == "CR")
        qDebug() << "######### CR MODE selected ######### ";
   else if(selected_mode == "CC")
        qDebug() << "######### CC MODE selected ######### ";
    else if(selected_mode == "ETU")
        qDebug() << "######### ETU MODE selected ######### ";
    }
    else if(path.startsWith("/RouteRunResponse"))
    {
        QByteArray pfd = request.getParameter("PF");
        QByteArray Nxt = request.getParameter("Next");
        QByteArray peri = request.getParameter("Peri");
        QByteArray skip = request.getParameter("Skip");
        if(pfd.length())
            emit change_pf_direction(QChar(pfd[0]));
        if(Nxt.length())
            emit change_next_stop(Nxt,peri);
        if(skip.length())
            emit skip_stop(skip);
        response.write("Success");
        return;
    }
    else if(path.startsWith("/SelectRoute"))
    {
        emit route_selection_menu();
    }
    else if (QFileInfo(docroot+path).isDir())
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
     // qDebug("RequestHandler: finished request");
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
    else if (fileName.endsWith(".xml") )
    {
        response.setHeader("Content-Type", qPrintable("text/xml; charset="+encoding));
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
       // qDebug("StaticFileController: unknown MIME type for filename '%s'", qPrintable(fileName));
    }
}

