#include "settings.h"
#include "ui_settings.h"
void settings::paintEvent(QPaintEvent* /*event*/)
{
    QColor backgroundColor ;
    backgroundColor.setRgb(173, 216, 230);
    backgroundColor.setAlpha(180);
    QPainter customPainter(this);
    customPainter.fillRect(rect(),backgroundColor);
}
settings::settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    main_screen_available=true;
}

settings::~settings()
{
    delete ui;
}

void settings::on_settings_back_button_clicked()
{
    if(main_screen_available)
     emit back_clicked();
    else
    {
        ui->stackedWidget->setCurrentIndex(0);
        main_screen_available=true;
    }
}

void settings::on_system_config_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    main_screen_available=false;
}
