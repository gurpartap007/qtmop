#include "user_mode.h"
#include "ui_user_mode.h"


user_mode::user_mode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::user_mode)
{
    ui->setupUi(this);
    train_keyboard = new keyboard;
    ui->stackedWidget->setCurrentIndex(1);

}

user_mode::~user_mode()
{
    delete ui;
}
