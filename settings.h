#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include "header.h"
#include "keyboard.h"
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
    keyboard *numeric_keypad;
    ~settings();
signals:
 void back_clicked();
protected:
    void paintEvent(QPaintEvent* event);
    virtual bool eventFilter( QObject * watched, QEvent * event );

private slots:
    void on_settings_back_button_clicked();
    void update_database();
    void on_system_config_clicked();
    void set_maximum_value_of_handicap_spinbox(int);

private:
    Ui::settings *ui;
    bool main_screen_available;
    QSize original_size_of_spacer;
      QDesktopWidget screen_size;
};

#endif // SETTINGS_H
