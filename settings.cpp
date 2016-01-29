#include "settings.h"
#include "ui_settings.h"
void settings::paintEvent(QPaintEvent* /*event*/)
{
    QColor backgroundColor ;
    backgroundColor.setRgb(173, 216, 230);
    backgroundColor.setAlpha(70);
    QPainter customPainter(this);
    customPainter.fillRect(rect(),backgroundColor);
}
settings::settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
}

settings::~settings()
{
    delete ui;
}

void settings::on_settings_back_button_clicked()
{
     emit back_clicked();
}
