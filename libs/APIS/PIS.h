
#ifndef PIS_H
#define PIS_H
#include "PIS_global.h"
#include "ui_PIS.h"
#include "qt_headers.h"
#include "route_selection.h"
#include "running_route.h"
#include "lgps.h"
#include "pis_settings.h"
#include "prerecorded.h"
#include "PIS_Structs.h"

#include "sqlqueries.h"
#include "route_selection.h"
#include "running_route.h"
#include "externs.h"
#include <QMutex>

//#######################################################################################
//				GPS RELATED STRUCTURES
//#######################################################################################
extern uinteger track_dist_bn_stns[MAX_STNS_PER_BUS];
extern sinteger mul_factor[MAX_STNS_PER_BUS];


namespace Ui {
class PIS_VIEW;
}

class PIS_VIEWSHARED_EXPORT PIS_VIEW : public QWidget
{
    Q_OBJECT

public:
    explicit PIS_VIEW(QWidget *parent = 0);
    ~PIS_VIEW();
    route_selection  *route_sel;
    running_route  *run_route;
    LGPS *gps;
    PIS_SETTINGS *pis_settings;
    PreRecorded *prerecord;
    QTimer *curr_log_timer;
    QStringList get_event_data(void);
    QStringList get_fault_data(void);
    QStringList getKilometerFields(void);
    QStringList getKilometerData(void);
    void close_timer(void);
    void server_acknowledge(void);

public slots:
    QStringList getEventFields();
    void pis_event_handler(qint64 event,void *data);
    void save_current_log(void);
    void kilometrage_Calculator(qint64 event,void *data);
    void on_setts_clicked();
    int restoreKilometerage();
    QString getPISLibVersion();
private slots:
    void changeLoggingFreq(int);
    void on_prerecord_clicked();
    void on_routesel_clicked();
    void selectPISRoute(QString);

private:
    Ui::PIS_VIEW *ui;
    QMutex m_mutex;
protected:
    void mouseReleaseEvent(QMouseEvent * e);
};

#endif // PIS_H


