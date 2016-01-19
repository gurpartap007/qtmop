#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include "header.h"

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

private:
    Ui::settings *ui;
};

#endif // SETTINGS_H
