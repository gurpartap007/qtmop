#ifndef PUBLIC_ANNOUNCEMENT_H
#define PUBLIC_ANNOUNCEMENT_H

#include <QWidget>
#include "header.h"

namespace Ui {
class public_announcement;
}

class public_announcement : public QWidget
{
    Q_OBJECT

public:
    explicit public_announcement(QWidget *parent = 0);
    ~public_announcement();
signals:
    void back_clicked();
private slots:
    void on_announcement_back_button_clicked();
protected:
    void paintEvent(QPaintEvent* event);
private:
    Ui::public_announcement *ui;
};

#endif // PUBLIC_ANNOUNCEMENT_H
