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
    this->setGeometry(100,100,this->width(),this->height());
    //qreal opacity_level=0;
    train_selection_keyboard = new keyboard(this);
    // train_selection_keyboard->setMaximumSize(ui->stackedWidget->size());
    // train_selection_keyboard->setLayout(ui->keyboard_layout);
    ui->stackedWidget->addWidget(train_selection_keyboard);
    ui->stackedWidget->setCurrentWidget(train_selection_keyboard);
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    //setParent(0); // Create TopLevel-Widget
    //setAttribute(Qt::WA_NoSystemBackground, true);
    //setAttribute(Qt::WA_TranslucentBackground, true);
    //setAttribute(Qt::WA_PaintOnScreen); // not needed in Qt 5.2 and up
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
    // input.append(QString::fromUtf8(&value));
    if(value == ENTER_CLICK)
    {
        QMessageBox::information(this, tr("Invalid Input"),
                                 tr("Entered Train Route Doesn't Exist "),
                                 QMessageBox::Ok);
        //  memset(display,0,sizeof(display));
        //  ui->lineEdit->clear();
    }
    else
        ui->lineEdit->setText(QString::fromUtf8(display));
}

void route_selection::on_pushButton_clicked()
{
    this->close();
}
