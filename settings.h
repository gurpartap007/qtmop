#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include "header.h"
/** @brief All Settings related to device like volume control,System configuration
 * Data Transfer and system Update.
 *

    Detailed description follows here.
    @author Gurpartap Singh
    @date December 23 2015
    */
/** @file
 *
 */
namespace Ui {
class settings;
}

class settings : public QWidget
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = 0);
    ~settings();
signals:
 void back_clicked();
protected:
    void paintEvent(QPaintEvent* event);
private slots:
    void on_settings_back_button_clicked();

    void on_system_config_clicked();

private:
    Ui::settings *ui;
    bool main_screen_available;
};

#endif // SETTINGS_H
