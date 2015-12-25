#ifndef USER_MODE_H
#define USER_MODE_H

#include <QWidget>
#include "header.h"
#include "keyboard.h"

namespace Ui {
class user_mode;
}

class user_mode : public QWidget
{
    Q_OBJECT

public:
    explicit user_mode(QWidget *parent = 0);
    ~user_mode();
    keyboard  *train_keyboard;

private:
    Ui::user_mode *ui;
};

#endif // USER_MODE_H
