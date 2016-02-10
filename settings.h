#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include "header.h"
#include "numeric_keypad.h"
#include "a.out.h"
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
enum
{
    COACH_COUNT_INPUT,
    HANDICAP_COACH1_INPUT,
    HANDICAP_COACH2_INPUT
};
namespace Ui {
class settings;
}

class settings : public QWidget
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = 0);
    numeric_keypad *keypad;
    int coach_count;
    int input_box;
    int handicap_coach1;
    int handicap_coach2;
    int max_limit;
    bool keypad_enabled = false;

    ~settings();
signals:
 void back_clicked();
 void enable_keypad();
protected:
    void paintEvent(QPaintEvent* event);
    virtual bool eventFilter( QObject * watched, QEvent * event );

private slots:
    void on_settings_back_button_clicked();
    void update_database();
    void on_system_config_clicked();
    void display_numeric_keypad();
    void settext_in_input();
    void setvalue();
    void coach_count_input_clicked();
    void handicap_coach1_input_clicked();
    void handicap_coach2_input_clicked();


private:
    Ui::settings *ui;
    bool main_screen_available;
    QSize original_size_of_spacer;
      QDesktopWidget screen_size;
};

#endif // SETTINGS_H
