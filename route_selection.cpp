#include "route_selection.h"
#include "ui_route_selection.h"
QString input;
extern char display[20];
extern char *ptr;
route_selection::route_selection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::route_selection)
{
    ui->setupUi(this);
    //qreal opacity_level=0;
    train_selection_keyboard = new keyboard(this);
    // train_selection_keyboard->setMaximumSize(ui->stackedWidget->size());
    // train_selection_keyboard->setLayout(ui->keyboard_layout);
    ui->stackedWidget->addWidget(train_selection_keyboard);
    ui->stackedWidget->setCurrentWidget(train_selection_keyboard);
    this->setGeometry(100,120,this->width(),this->height());
    // Create TopLevel-Widget
    setAttribute(Qt::WA_NoSystemBackground, false);
    setAttribute(Qt::WA_TranslucentBackground, false);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    //  setAttribute(Qt::WA_PaintOnScreen); // not needed in Qt 5.2 and up
    //setWindowOpacity(opacity_level);
    connect(train_selection_keyboard,SIGNAL(value_changed(char)),this,SLOT(settext(char)));
    train_selection_keyboard->on_pushButton_31_clicked();


}
route_selection::~route_selection()
{
    delete ui;
}

void route_selection::settext(char value)
{
    ui->lineEdit->clear();
    errorbox = new  QPushButton(this) ;
    //errorbox.setParent(this);
    errorbox->setWindowFlags(Qt::WindowStaysOnTopHint);
    // input.append(QString::fromUtf8(&value));
    if(value == ENTER_CLICK)
    {
        ui->lineEdit->clear();
        ui->lineEdit->setText("Invalid Train Route");
        ui->lineEdit->setStyleSheet("QLineEdit { background-color: rgb(255,0,0); }");
       // memset(display,'\0',sizeof(display));
        while(ptr != &display[0])
        {
            ptr--;	//decrementing write pointer
            *ptr = '\0';
        }
    }
    else
    {
        ui->lineEdit->setStyleSheet("QLineEdit { background-color: rgb(235,235,235); }");
        ui->lineEdit->setText(QString::fromUtf8(display));

    }
}

void route_selection::on_pushButton_clicked()
{
    while(ptr != &display[0])
    {
        ptr--;	//decrementing write pointer
        *ptr = '\0';
    }
    ui->lineEdit->setText(QString::fromUtf8(display));
    this->close();
}
