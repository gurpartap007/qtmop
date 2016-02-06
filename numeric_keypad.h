#ifndef NUMERIC_KEYPAD_H
#define NUMERIC_KEYPAD_H

#include <QWidget>

namespace Ui {
class numeric_keypad;
}

class numeric_keypad : public QWidget
{
    Q_OBJECT

public:
    explicit numeric_keypad(QWidget *parent = 0);
    ~numeric_keypad();

private:
    Ui::numeric_keypad *ui;
};

#endif // NUMERIC_KEYPAD_H
