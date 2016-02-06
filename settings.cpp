#include "settings.h"
#include "ui_settings.h"
//extern QSqlDatabase db;
void settings::paintEvent(QPaintEvent* /*event*/)
{
    QColor backgroundColor ;
    backgroundColor.setRgb(173, 216, 230);
    backgroundColor.setAlpha(180);
    QPainter customPainter(this);
    customPainter.fillRect(rect(),backgroundColor);
}

bool settings::eventFilter(QObject *watched, QEvent *event)
{
    if ( ui->settings_back_button->isHidden() && event->type() == QEvent::MouseButtonPress )
    {
        emit back_clicked();
    }

    return QObject::eventFilter(watched, event);
}
settings::settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settings)
{

    ui->setupUi(this);
    main_screen_available=true;
    numeric_keypad = new keyboard(this);
    numeric_keypad->hide();
    original_size_of_spacer = ui->spacer_left->sizeHint();
    ui->coach_count_spinBox->setMinimumHeight(screen_size.height()/6);
    ui->handicap1_spinBox->setMinimumHeight(screen_size.height()/6);
    ui->handicap2_spinBox->setMinimumHeight(screen_size.height()/6);
    connect(ui->coach_count_spinBox,SIGNAL(valueChanged(int)),this,SLOT(set_maximum_value_of_handicap_spinbox(int)));
    ui->right_area->installEventFilter(this);
    ui->left_area->installEventFilter(this);
    ui->bottom_area->installEventFilter(this);
    ui->settings_back_button->hide();
    ui->coach_count_spinBox->setMaximumWidth(screen_size.width()/4);
    ui->handicap1_spinBox->setMaximumWidth(screen_size.width()/4);
    ui->handicap2_spinBox->setMaximumWidth(screen_size.width()/4);

}

settings::~settings()
{
    delete ui;
}

void settings::on_settings_back_button_clicked()
{
    ui->spacer_left->changeSize(screen_size.width()/3.5,original_size_of_spacer.height());
    ui->spacer_right->changeSize(screen_size.width()/3.5,original_size_of_spacer.height());
    this->updateGeometry();
    update_database();
    ui->stackedWidget->setCurrentIndex(0);
    ui->settings_back_button->hide();
}

void settings::update_database()
{
    QSqlQuery update_configuration_table("UPDATE `configuration` SET `coach_count`= '"+QString::number(ui->coach_count_spinBox->value())+"',`handicap_coach1`='"+QString::number(ui->handicap1_spinBox->value())+"',`handicap_coach2`='"+QString::number(ui->handicap2_spinBox->value())+"'");
}

void settings::on_system_config_clicked()
{
    ui->coach_count_spinBox->setStyleSheet("QSpinBox { border: 1px solid black; border-radius: 5px; background-color: rgb(200,200,200); }"
                               "QSpinBox::up-arrow { border-left: 17px solid none;"
                               "border-right: 17px solid none; border-bottom: 17px solid black; width: 0px; height: 0px; }"
                               "QSpinBox::up-arrow:hover { border-left: 30px solid none;"
                               "border-right: 17px solid none; border-bottom: 17px solid black; width: 0px; height: 0px; }"
                               "QSpinBox::up-button { width: "+ QString::number(ui->coach_count_spinBox->width()/2) +" px; height: "+ QString::number((ui->coach_count_spinBox->height()/2)-3) +"px; background-color: grey }"
                               "QSpinBox::up-button:hover { width: "+ QString::number((ui->coach_count_spinBox->width()/2)-10) +"px; height: "+ QString::number((ui->coach_count_spinBox->height()/2)-10) +"px; background-color: rgb(120,120,120) }"
                               "QSpinBox::down-arrow { border-left: 17px solid none;"
                               "border-right: 17px solid none; border-top: 17px solid black; width: 0px; height: 0px; }"
                               "QSpinBox::down-arrow:hover { border-left: 30px solid none;"
                               "border-right: 17px solid none; border-top: 17px solid black; width: 0px; height: 0px; }"
                               "QSpinBox::down-button { width: "+ QString::number(ui->coach_count_spinBox->width()/2) +"px; height: "+ QString::number((ui->coach_count_spinBox->height()/2)-3) +"px; background-color: grey}"
                               "QSpinBox::down-button:hover { width: "+ QString::number((ui->coach_count_spinBox->width()/2)-10) +"px; height: "+ QString::number((ui->coach_count_spinBox->height()/2)-10) +"px; background-color: rgb(120,120,120)}"
            );
    ui->handicap1_spinBox->setStyleSheet(ui->coach_count_spinBox->styleSheet());
    ui->handicap2_spinBox->setStyleSheet(ui->coach_count_spinBox->styleSheet());
    ui->spacer_left->changeSize(0,0);
    ui->spacer_right->changeSize(0,0);
    this->updateGeometry();
    ui->stackedWidget->setCurrentIndex(1);
    ui->settings_back_button->show();

}

void settings::set_maximum_value_of_handicap_spinbox(int coach_count)
{
    ui->handicap1_spinBox->setMaximum(coach_count);
    ui->handicap2_spinBox->setMaximum(coach_count);

}
