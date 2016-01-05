#ifndef ROUTE_SELECTION_H
#define ROUTE_SELECTION_H

#include <QWidget>
#include "header.h"
#include "keyboard.h"
#include "train_route.h"


#include "database.h"

namespace Ui {
class route_selection;
}

class route_selection : public QWidget
{
    Q_OBJECT

public:
    explicit route_selection(QWidget *parent = 0);
    keyboard *train_selection_keyboard;
    QPushButton *errorbox;
    database *train_database;
    train_route *current_route;
    ~route_selection();
public slots:
    void settext(char value);
    void route_window();
private slots:
    void on_backButton_clicked();
signals:
    void train_selected();
private:
    Ui::route_selection *ui;
};

#endif // ROUTE_SELECTION_H
