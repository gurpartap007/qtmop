#include "numeric_keypad.h"
#include "ui_numeric_keypad.h"

numeric_keypad::numeric_keypad(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::numeric_keypad)
{
    ui->setupUi(this);
}

numeric_keypad::~numeric_keypad()
{
    delete ui;
}
