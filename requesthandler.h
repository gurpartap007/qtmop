/**
  @file
  @author Stefan Frings
*/

#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <headers/httprequesthandler.h>
#include <QFileInfo>

/**
  The request handler receives incoming HTTP requests and generates responses.
*/

class RequestHandler : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(RequestHandler)
public:

    /**
      Constructor.
      @param parent Parent object
    */
    RequestHandler(QObject* parent=0);
    QString docroot;
    QFile file;
    QString encoding;

    /**
      Destructor
    */
    ~RequestHandler();
public slots:
    void setContentType(QString fileName, HttpResponse& response) const;
    /**
      Process an incoming HTTP request.
      @param request The received HTTP request
      @param response Must be used to return the response
    */
    void service(HttpRequest& request, HttpResponse& response);

};

#endif // REQUESTHANDLER_H
