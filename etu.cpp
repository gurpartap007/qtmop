#include "etu.h"
#include "ui_etu.h"
void etu::paintEvent(QPaintEvent* /*event*/)
{
    QColor backgroundColor ;
    backgroundColor.setRgb(173, 216, 230);
    backgroundColor.setAlpha(180);
    QPainter customPainter(this);
    customPainter.fillRect(rect(),backgroundColor);
}

bool etu::eventFilter(QObject *watched, QEvent *event)
{

    if (  event->type() == QEvent::MouseButtonPress )
    {
        emit back_clicked();
    }


    return QObject::eventFilter(watched, event);
}
etu::etu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::etu)
{
    ui->setupUi(this);
    connect(ui->end_call_button,SIGNAL(clicked()),this,SLOT(end_current_call()));
    //this->installEventFilter(this->window());
    ui->left_area->installEventFilter(this);
    ui->right_area->installEventFilter(this);
    ui->bottom_area->installEventFilter(this);
}


etu::~etu()
{
    delete ui;
}

void etu::end_current_call()
{
    emit call_ended();
}

