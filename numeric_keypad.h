#ifndef NUMERIC_KEYPAD_H
#define NUMERIC_KEYPAD_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class numeric_keypad;
}

class numeric_keypad : public QWidget
{
    Q_OBJECT

public:
    explicit numeric_keypad(QWidget *parent = 0);
    ~numeric_keypad();

signals:
    void value_changed();
    void enter_clicked();
    void clear();
private slots:
    void on_numeric_1_clicked();

    void on_numeric_2_clicked();

    void on_numeric_3_clicked();

    void on_numeric_4_clicked();

    void on_numeric_5_clicked();

    void on_numeric_6_clicked();

    void on_numeric_7_clicked();

    void on_numeric_8_clicked();

    void on_numeric_9_clicked();

    void on_numeric_0_clicked();

    void on_backspace_clicked();

    void on_enter_clicked();
    void clear_input();

private:
    Ui::numeric_keypad *ui;
};

#endif // NUMERIC_KEYPAD_H
