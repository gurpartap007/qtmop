#include "settings.h"
#include "ui_settings.h"
extern char input[20];
int current_input=COACH_COUNT_INPUT ;
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
    keypad = new numeric_keypad;
    keypad->hide();
    original_size_of_spacer = ui->spacer_left->sizeHint();
    ui->coach_count_input->setMinimumHeight(screen_size.height()/6);
    ui->handicap1_input->setMinimumHeight(screen_size.height()/6);
    ui->handicap2_input->setMinimumHeight(screen_size.height()/6);
    connect(ui->coach_count_input,SIGNAL(cursorPositionChanged(int,int)),this,SLOT(coach_count_input_clicked()));
    connect(ui->handicap1_input,SIGNAL(cursorPositionChanged(int,int)),this,SLOT(handicap_coach1_input_clicked()));
    connect(ui->handicap2_input,SIGNAL(cursorPositionChanged(int,int)),this,SLOT(handicap_coach2_input_clicked()));
    connect(this,SIGNAL(enable_keypad()),this,SLOT(display_numeric_keypad()));
    connect(keypad,SIGNAL(enter_clicked()),this,SLOT(setvalue()));
    ui->right_area->installEventFilter(this);
    ui->left_area->installEventFilter(this);
    ui->bottom_area->installEventFilter(this);
    ui->coach_count_input->installEventFilter(this);
    ui->handicap1_input->installEventFilter(this);
    ui->handicap2_input->installEventFilter(this);
    ui->settings_back_button->hide();
    ui->coach_count_input->setMaximumWidth(screen_size.width()/4);
    ui->handicap1_input->setMaximumWidth(screen_size.width()/4);
    ui->handicap2_input->setMaximumWidth(screen_size.width()/4);
    connect(keypad,SIGNAL(value_changed()),this,SLOT(settext_in_input()));
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
    emit keypad->clear();
    keypad->hide();
    keypad_enabled=false;
}

void settings::update_database()
{
    QSqlQuery update_configuration_table("UPDATE `configuration` SET `coach_count`= '"+QString::number(coach_count)+"',`handicap_coach1`='"+QString::number(handicap_coach1)+"',`handicap_coach2`='"+QString::number(handicap_coach2)+"'");
}

void settings::on_system_config_clicked()
{
    this->updateGeometry();
    ui->spacer_left->changeSize(0,0);
    ui->spacer_right->changeSize(0,0);
    ui->spacer_right->setGeometry(QRect(0,0,0,0));
    ui->stackedWidget->setCurrentIndex(1);
    ui->bottom_area->hide();
    ui->settings_back_button->show();
}


void settings::display_numeric_keypad()
{
    input_box = COACH_COUNT_INPUT;
    ui->keypad_layout_right->addWidget(keypad);
    keypad->show();
}

void settings::settext_in_input()
{
    if(input_box == COACH_COUNT_INPUT)
        ui->coach_count_input->setText(QString::fromUtf8(input));
    else if(input_box == HANDICAP_COACH1_INPUT)
        ui->handicap1_input->setText(QString::fromUtf8(input));
    else if (input_box == HANDICAP_COACH2_INPUT)
        ui->handicap2_input->setText(QString::fromUtf8(input));
}

void settings::setvalue()
{

    if(input_box == COACH_COUNT_INPUT)
    {
        max_limit = coach_count = ui->coach_count_input->text().toInt();
        qDebug() << "Final Coach Count" << coach_count;
        ui->coach_count_input->setDisabled(true);
        emit keypad->clear();
    }
    else if(input_box == HANDICAP_COACH1_INPUT)
    {
        if(ui->handicap1_input->text().toInt() > max_limit)
        {
            ui->handicap1_input->setStyleSheet("background-color: rgb(239,0,0);");
        }
        else
        {
            ui->handicap1_input->setStyleSheet("background-color: rgb(232, 232, 232");
            handicap_coach1 = ui->handicap1_input->text().toInt();
            qDebug() << "Handicap_coach1" << handicap_coach1;
            ui->handicap1_input->setDisabled(true);
            emit keypad->clear();
        }
    }
    else if (input_box == HANDICAP_COACH2_INPUT)
    {
        if(ui->handicap2_input->text().toInt() > max_limit)
        {
            ui->handicap2_input->setStyleSheet("background-color: rgb(239,0,0);");
        }
        else
        {
            ui->handicap2_input->setStyleSheet("background-color: rgb(232, 232, 232");
            handicap_coach2 = ui->handicap2_input->text().toInt();
            qDebug() << "handicap_coach2" << handicap_coach2;
            ui->handicap2_input->setDisabled(true);
            emit keypad->clear();
        }
    }

}

void settings::coach_count_input_clicked()
{
    if(!keypad_enabled)
    {
        emit enable_keypad();
        keypad_enabled=true;
    }
}

void settings::handicap_coach1_input_clicked()
{
    input_box = HANDICAP_COACH1_INPUT;

}

void settings::handicap_coach2_input_clicked()
{
    input_box = HANDICAP_COACH2_INPUT;

}

