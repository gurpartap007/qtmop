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
signals:
    void write_train_routes(QString selected_train_route);
    void route_selection_menu(void);
    void change_pf_direction(QChar);
    void change_next_stop(QByteArray,QByteArray);
    void skip_stop(QByteArray);
    void accept_selected_call(QString);
    void disconnect_selected_call(QString);
    void hold_selected_call(QString);
    void resume_selected_call(QString);
    void intercom_clicked();
    void announcement_clicked() ;
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
