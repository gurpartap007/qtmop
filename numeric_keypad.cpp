#include "numeric_keypad.h"
#include "ui_numeric_keypad.h"
char input[20], *input_ptr;
numeric_keypad::numeric_keypad(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::numeric_keypad)
{
    ui->setupUi(this);
    memset(input,0,sizeof(input));
    input_ptr = &input[0];
    connect(this,SIGNAL(clear()),this,SLOT(clear_input()));
}

numeric_keypad::~numeric_keypad()
{
    delete ui;
}

void numeric_keypad::on_numeric_1_clicked()
{
    *input_ptr= '1';
    input_ptr ++;
    emit value_changed();
}

void numeric_keypad::on_numeric_2_clicked()
{
    *input_ptr= '2';
    input_ptr ++;
     emit value_changed();
}

void numeric_keypad::on_numeric_3_clicked()
{
    *input_ptr= '3';
    input_ptr ++;
     emit value_changed();
}

void numeric_keypad::on_numeric_4_clicked()
{
    *input_ptr= '4';
    input_ptr ++;
     emit value_changed();
}

void numeric_keypad::on_numeric_5_clicked()
{
    *input_ptr= '5';
    input_ptr ++;
     emit value_changed();
}

void numeric_keypad::on_numeric_6_clicked()
{
    *input_ptr= '6';
    input_ptr ++;
     emit value_changed();
}

void numeric_keypad::on_numeric_7_clicked()
{
    *input_ptr= '7';
    input_ptr ++;
     emit value_changed();
}

void numeric_keypad::on_numeric_8_clicked()
{
    *input_ptr= '8';
    input_ptr ++;
     emit value_changed();
}

void numeric_keypad::on_numeric_9_clicked()
{
    *input_ptr= '9';
    input_ptr ++;
    emit value_changed();
}

void numeric_keypad::on_numeric_0_clicked()
{
    *input_ptr= '0';
    input_ptr ++;
    emit value_changed();
}

void numeric_keypad::on_backspace_clicked()
{
if(&input[0] != input_ptr)
{
 -- input_ptr;
*input_ptr = '\0';
//qDebug() << input_ptr;
//qDebug() << input_ptr[1];
emit value_changed();
}
}

void numeric_keypad::on_enter_clicked()
{
qDebug() << QString::fromUtf8(input);
emit enter_clicked();
}

void numeric_keypad::clear_input()
{
    memset(input,0,sizeof(input));
    input_ptr = &input[0];
}
