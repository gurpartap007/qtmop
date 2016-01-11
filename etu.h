#ifndef ETU_H
#define ETU_H

#include <QWidget>
#include "header.h"

namespace Ui {
class etu;
}

class etu : public QWidget
{
    Q_OBJECT

public:
    explicit etu(QWidget *parent = 0);
    ~etu();
    QPushButton *accept_call;
    QPushButton *hold_call;
    QPushButton *end_call;
    QHBoxLayout *buttons_layout;
public slots:
    void end_current_call();
signals:
    void call_ended();
protected:
     void paintEvent(QPaintEvent* event);
private:
    Ui::etu *ui;
};

#endif // ETU_H
