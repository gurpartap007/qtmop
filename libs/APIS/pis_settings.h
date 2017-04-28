#ifndef PIS_SETTINGS_H
#define PIS_SETTINGS_H
#include "PIS_global.h"
#include "qt_headers.h"
#include "route_selection.h"
#include "lgps.h"
#include "crc_lib.h"
#include "ui_pis_settings.h"
#include "externs.h"
#include "admin.h"
#include <QMutex>

#define LIB_VERSION "1.0.0"

namespace Ui {
class PIS_Settings;
}

class PIS_VIEWSHARED_EXPORT PIS_SETTINGS : public QWidget
{
    Q_OBJECT

public:
    explicit PIS_SETTINGS(QWidget *parent = 0);
    ~PIS_SETTINGS();

    QString UnitID;
    QString CoachID;
    QString ServerIP;
    QString ServerPortSync;
    QString ServerPortASync;
    int loggingFrequency;
    int loggingFrequencyTime;
    QTime announcement_on_time;
    QTime announcement_off_time;
    bool en_speed_display;
    bool en_safety_slogans;
    bool en_logging;
    bool en_announcement;
    bool en_destination_board;
    QString CoachAbbr,displayParameters,CoachAbbrb;
    int CoachAbbrIndex;
    QSettings *unitsettings;
    QSettings *coachsettings;
    Ui::PIS_SETTINGS *ui;
signals:
    void StartSimulation(QString);
    void changeLogFreq(int);
    void selectRoute(QString);

public slots:
    void on_pushButton_clicked();
    void tab_changed(int);
    void on_pushButton_2_clicked();
    void text_edited(QString);
    void resize_and_show_keywidget();

    /*Writes coach configuration to .conf file*/
    int updateCoach(QStringList);
    QStringList getPISInfoList();
    QStringList getPISInfoData();

private slots:
    void on_save_clicked();
    void on_close_clicked();

    void on_comboBox_2_currentIndexChanged(int index);

protected:
    void showEvent(QShowEvent*);

private:
    LGPS *gpsData;
    admin *admn;
    QMutex m_mutex;
};

#endif // PIS_SETTINGS_H
