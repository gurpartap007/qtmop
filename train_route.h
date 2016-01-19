#ifndef TRAIN_ROUTE_H
#define TRAIN_ROUTE_H

#include <QWidget>
#include "header.h"

namespace Ui {
class train_route;
}

class train_route : public QWidget
{
    Q_OBJECT

public:
    explicit train_route(QSqlDatabase *emu_database, QWidget *parent = 0);
    ~train_route();

private:
    Ui::train_route *ui;
};

#endif // TRAIN_ROUTE_H
