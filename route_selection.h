#ifndef ROUTE_SELECTION_H
#define ROUTE_SELECTION_H

#include <QWidget>
#include "header.h"
#include "keyboard.h"

namespace Ui {
class route_selection;
}

class route_selection : public QWidget
{
    Q_OBJECT

public:
    explicit route_selection(QWidget *parent = 0);
    keyboard *train_selection_keyboard;
    ~route_selection();
public slots:
    void settext(char value);
private slots:
    void on_pushButton_clicked();

private:
    Ui::route_selection *ui;
};

#endif // ROUTE_SELECTION_H
