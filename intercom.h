#ifndef INTERCOM_H
#define INTERCOM_H

#include <QWidget>

namespace Ui {
class intercom;
}

class intercom : public QWidget
{
    Q_OBJECT

public:
    explicit intercom(QWidget *parent = 0);
    ~intercom();

private:
    Ui::intercom *ui;
};

#endif // INTERCOM_H
