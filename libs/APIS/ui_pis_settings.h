/********************************************************************************
** Form generated from reading UI file 'pis_settings.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIS_SETTINGS_H
#define UI_PIS_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>
#include <lineedit.h>

QT_BEGIN_NAMESPACE

class Ui_PIS_SETTINGS
{
public:
    QGridLayout *gridLayout_13;
    QTabWidget *Settings;
    QWidget *CoachSettings;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_11;
    QComboBox *comboBox;
    lineedit *lineEdit_4;
    QLabel *label_12;
    lineedit *lineEdit_5;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QWidget *ServerSettings;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QLabel *label;
    lineedit *lineEdit;
    QLabel *label_2;
    lineedit *lineEdit_2;
    QLabel *label_3;
    lineedit *lineEdit_3;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QWidget *Simulation;
    QGridLayout *gridLayout_7;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_5;
    QLabel *label_10;
    QComboBox *comboBox_3;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_3;
    QWidget *TimeSettings;
    QGridLayout *gridLayout_10;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_6;
    QLabel *label_5;
    QDateEdit *dateEdit;
    QLabel *label_6;
    QTimeEdit *timeEdit;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_4;
    QWidget *Features;
    QGridLayout *gridLayout_11;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_8;
    QCheckBox *checkBox;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_7;
    QWidget *Miscelleanous;
    QGridLayout *gridLayout_12;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_9;
    QLabel *label_7;
    QComboBox *comboBox_2;
    QLabel *label_8;
    QTimeEdit *timeEdit_2;
    QTimeEdit *timeEdit_3;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *save;
    QPushButton *close;

    void setupUi(QWidget *PIS_SETTINGS)
    {
        if (PIS_SETTINGS->objectName().isEmpty())
            PIS_SETTINGS->setObjectName(QStringLiteral("PIS_SETTINGS"));
        PIS_SETTINGS->setWindowModality(Qt::WindowModal);
        PIS_SETTINGS->resize(930, 510);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PIS_SETTINGS->sizePolicy().hasHeightForWidth());
        PIS_SETTINGS->setSizePolicy(sizePolicy);
        PIS_SETTINGS->setMinimumSize(QSize(0, 0));
        PIS_SETTINGS->setMaximumSize(QSize(10000, 10000));
        QFont font;
        font.setPointSize(24);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        PIS_SETTINGS->setFont(font);
        PIS_SETTINGS->setWindowOpacity(1);
        PIS_SETTINGS->setStyleSheet(QStringLiteral(""));
        gridLayout_13 = new QGridLayout(PIS_SETTINGS);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        Settings = new QTabWidget(PIS_SETTINGS);
        Settings->setObjectName(QStringLiteral("Settings"));
        sizePolicy.setHeightForWidth(Settings->sizePolicy().hasHeightForWidth());
        Settings->setSizePolicy(sizePolicy);
        Settings->setMinimumSize(QSize(0, 0));
        Settings->setMaximumSize(QSize(10000, 10000));
        Settings->setFont(font);
        Settings->setFocusPolicy(Qt::NoFocus);
        Settings->setStyleSheet(QLatin1String("\n"
"QTabBar::tab {	\n"
"    background-color :grey;/*rgb(101, 104, 103);*/\n"
"	 background-image: url(:/images/camera.png);\n"
"	border: 1px solid ;/*#C4C4C3;*/\n"
"	height:60px;\n"
"	\n"
"	color: rgb(54, 35, 35);\n"
"	border-radius: 4px;\n"
"	border-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(163, 163, 163, 255));/*grey;*/\n"
"}\n"
"\n"
"QTabBar::tab:selected{\n"
" background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(163, 163, 163, 255));\n"
"	 border-bottom-color: #C2C7CB;\n"
"}\n"
"\n"
"QTabBar::tab:!selected {\n"
"    margin-top: 3px; /* make non-selected tabs look smaller */\n"
"}"));
        CoachSettings = new QWidget();
        CoachSettings->setObjectName(QStringLiteral("CoachSettings"));
        CoachSettings->setMinimumSize(QSize(0, 0));
        gridLayout_2 = new QGridLayout(CoachSettings);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox = new QGroupBox(CoachSettings);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(15);
        gridLayout->setVerticalSpacing(20);
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);
        label_11->setMinimumSize(QSize(0, 80));
        label_11->setMaximumSize(QSize(400, 16777215));
        label_11->setStyleSheet(QLatin1String("background-color:transparent;\n"
"color: rgb(54, 35, 35);\n"
"font: 24pt \"Ubuntu\";"));
        label_11->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_11, 0, 0, 1, 1);

        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMinimumSize(QSize(0, 80));
        comboBox->setMaximumSize(QSize(100, 16777215));
        comboBox->setStyleSheet(QLatin1String("background-color:rgb(101, 104, 103);\n"
"font: 24pt \"Ubuntu\";"));

        gridLayout->addWidget(comboBox, 0, 1, 1, 1);

        lineEdit_4 = new lineedit(groupBox);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        sizePolicy.setHeightForWidth(lineEdit_4->sizePolicy().hasHeightForWidth());
        lineEdit_4->setSizePolicy(sizePolicy);
        lineEdit_4->setMinimumSize(QSize(0, 80));
        lineEdit_4->setMaximumSize(QSize(400, 80));
        lineEdit_4->setFocusPolicy(Qt::ClickFocus);
        lineEdit_4->setStyleSheet(QLatin1String("background-color:rgb(101, 104, 103);\n"
"font: 24pt \"Ubuntu\";"));

        gridLayout->addWidget(lineEdit_4, 0, 2, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));
        sizePolicy.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy);
        label_12->setMinimumSize(QSize(0, 80));
        label_12->setMaximumSize(QSize(400, 16777215));
        label_12->setStyleSheet(QLatin1String("background-color:transparent;\n"
"color: rgb(54, 35, 35);\n"
"font: 24pt \"Ubuntu\";"));
        label_12->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_12, 1, 0, 1, 1);

        lineEdit_5 = new lineedit(groupBox);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        sizePolicy.setHeightForWidth(lineEdit_5->sizePolicy().hasHeightForWidth());
        lineEdit_5->setSizePolicy(sizePolicy);
        lineEdit_5->setMinimumSize(QSize(0, 80));
        lineEdit_5->setMaximumSize(QSize(400, 80));
        lineEdit_5->setFocusPolicy(Qt::ClickFocus);
        lineEdit_5->setStyleSheet(QLatin1String("background-color:rgb(101, 104, 103);\n"
"font: 24pt \"Ubuntu\";"));

        gridLayout->addWidget(lineEdit_5, 1, 1, 1, 2);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(292, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout_2->addItem(verticalSpacer, 1, 0, 1, 1);

        Settings->addTab(CoachSettings, QString());
        ServerSettings = new QWidget();
        ServerSettings->setObjectName(QStringLiteral("ServerSettings"));
        ServerSettings->setMinimumSize(QSize(0, 0));
        gridLayout_4 = new QGridLayout(ServerSettings);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        groupBox_2 = new QGroupBox(ServerSettings);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(0, 80));
        label->setStyleSheet(QLatin1String("background-color:transparent;\n"
"color: rgb(54, 35, 35);\n"
"font: 24pt \"Ubuntu\";"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        lineEdit = new lineedit(groupBox_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 80));
        lineEdit->setMaximumSize(QSize(400, 16777215));
        lineEdit->setFocusPolicy(Qt::ClickFocus);
        lineEdit->setStyleSheet(QLatin1String("background-color:rgb(101, 104, 103);\n"
"font: 24pt \"Ubuntu\";"));
        lineEdit->setInputMethodHints(Qt::ImhNone);

        gridLayout_3->addWidget(lineEdit, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(0, 80));
        label_2->setStyleSheet(QLatin1String("background-color:transparent;\n"
"color: rgb(54, 35, 35);\n"
"font: 24pt \"Ubuntu\";"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_2 = new lineedit(groupBox_2);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setMinimumSize(QSize(0, 80));
        lineEdit_2->setMaximumSize(QSize(400, 16777215));
        lineEdit_2->setFocusPolicy(Qt::ClickFocus);
        lineEdit_2->setStyleSheet(QLatin1String("background-color:rgb(101, 104, 103);\n"
"font: 24pt \"Ubuntu\";"));
        lineEdit_2->setInputMethodHints(Qt::ImhDigitsOnly);

        gridLayout_3->addWidget(lineEdit_2, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(0, 80));
        label_3->setStyleSheet(QLatin1String("background-color:transparent;\n"
"color: rgb(54, 35, 35);\n"
"font: 24pt \"Ubuntu\";"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_3 = new lineedit(groupBox_2);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setMinimumSize(QSize(0, 80));
        lineEdit_3->setMaximumSize(QSize(400, 16777215));
        lineEdit_3->setFocusPolicy(Qt::ClickFocus);
        lineEdit_3->setStyleSheet(QLatin1String("background-color:rgb(101, 104, 103);\n"
"font: 24pt \"Ubuntu\";"));
        lineEdit_3->setInputMethodHints(Qt::ImhDigitsOnly);

        gridLayout_3->addWidget(lineEdit_3, 2, 1, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(392, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 97, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout_4->addItem(verticalSpacer_2, 1, 0, 1, 1);

        Settings->addTab(ServerSettings, QString());
        Simulation = new QWidget();
        Simulation->setObjectName(QStringLiteral("Simulation"));
        Simulation->setMinimumSize(QSize(0, 0));
        gridLayout_7 = new QGridLayout(Simulation);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        groupBox_3 = new QGroupBox(Simulation);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_5 = new QGridLayout(groupBox_3);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setMinimumSize(QSize(0, 80));
        label_10->setMaximumSize(QSize(10000, 16777215));
        label_10->setStyleSheet(QLatin1String("background-color:transparent;\n"
"color: rgb(54, 35, 35);\n"
"font: 24pt \"Ubuntu\";"));

        gridLayout_5->addWidget(label_10, 0, 0, 1, 2);

        comboBox_3 = new QComboBox(groupBox_3);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));
        comboBox_3->setMinimumSize(QSize(0, 80));
        comboBox_3->setStyleSheet(QLatin1String("background-color:rgb(101, 104, 103);\n"
"font: 24pt \"Ubuntu\";"));

        gridLayout_5->addWidget(comboBox_3, 1, 0, 1, 2);

        pushButton_2 = new QPushButton(groupBox_3);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        pushButton_2->setMinimumSize(QSize(200, 80));
        pushButton_2->setMaximumSize(QSize(100, 16777215));
        pushButton_2->setStyleSheet(QLatin1String("background-color:rgb(101, 104, 103);\n"
"font: 24pt \"Ubuntu\";"));

        gridLayout_5->addWidget(pushButton_2, 2, 0, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(178, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_7, 2, 1, 1, 1);


        gridLayout_7->addWidget(groupBox_3, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(478, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_3, 0, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 97, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout_7->addItem(verticalSpacer_3, 1, 0, 1, 1);

        Settings->addTab(Simulation, QString());
        TimeSettings = new QWidget();
        TimeSettings->setObjectName(QStringLiteral("TimeSettings"));
        TimeSettings->setMinimumSize(QSize(0, 0));
        gridLayout_10 = new QGridLayout(TimeSettings);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        groupBox_6 = new QGroupBox(TimeSettings);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        gridLayout_6 = new QGridLayout(groupBox_6);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        label_5 = new QLabel(groupBox_6);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(0, 80));
        label_5->setMaximumSize(QSize(400, 16777215));
        label_5->setStyleSheet(QLatin1String("background-color:transparent;\n"
"color: rgb(54, 35, 35);\n"
"font: 24pt \"Ubuntu\";"));
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_5, 0, 0, 1, 1);

        dateEdit = new QDateEdit(groupBox_6);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));
        dateEdit->setMinimumSize(QSize(0, 80));
        dateEdit->setMaximumSize(QSize(50000, 16777215));
        dateEdit->setStyleSheet(QLatin1String("QDateEdit\n"
"{\n"
"background-color:rgb(101, 104, 103);\n"
"font: 24pt \"Ubuntu\";\n"
"}\n"
"\n"
"QDateEdit::up-button{width:100px;  height:40px;}\n"
"QDateEdit::down-button{width:100px;  height:40px;};\n"
"\n"
""));

        gridLayout_6->addWidget(dateEdit, 0, 1, 1, 1);

        label_6 = new QLabel(groupBox_6);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(0, 80));
        label_6->setMaximumSize(QSize(400, 16777215));
        label_6->setStyleSheet(QLatin1String("background-color:transparent;\n"
"color: rgb(54, 35, 35);\n"
"font: 24pt \"Ubuntu\";"));
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_6, 1, 0, 1, 1);

        timeEdit = new QTimeEdit(groupBox_6);
        timeEdit->setObjectName(QStringLiteral("timeEdit"));
        timeEdit->setMinimumSize(QSize(0, 80));
        timeEdit->setMaximumSize(QSize(500000, 16777215));
        timeEdit->setStyleSheet(QLatin1String("QTimeEdit\n"
"{\n"
"background-color:rgb(101, 104, 103);\n"
"font: 24pt \"Ubuntu\";\n"
"}\n"
"\n"
"QTimeEdit::up-button{width:100px;  height:40px;}\n"
"QTimeEdit::down-button{width:100px;  height:40px;};\n"
"\n"
""));

        gridLayout_6->addWidget(timeEdit, 1, 1, 1, 1);


        gridLayout_10->addWidget(groupBox_6, 0, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(404, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_4, 0, 1, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 183, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout_10->addItem(verticalSpacer_4, 1, 0, 1, 1);

        Settings->addTab(TimeSettings, QString());
        Features = new QWidget();
        Features->setObjectName(QStringLiteral("Features"));
        Features->setMinimumSize(QSize(0, 0));
        gridLayout_11 = new QGridLayout(Features);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        groupBox_4 = new QGroupBox(Features);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_8 = new QGridLayout(groupBox_4);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        checkBox = new QCheckBox(groupBox_4);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        sizePolicy.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy);
        checkBox->setMinimumSize(QSize(0, 40));
        checkBox->setStyleSheet(QLatin1String("QCheckBox\n"
"{\n"
"color: rgb(54, 35, 35);\n"
"font: 24pt \"Ubuntu\";\n"
"}\n"
"\n"
"QCheckBox::indicator { width:50px; height: 50px; }"));

        gridLayout_8->addWidget(checkBox, 0, 0, 1, 1);

        checkBox_4 = new QCheckBox(groupBox_4);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));
        sizePolicy.setHeightForWidth(checkBox_4->sizePolicy().hasHeightForWidth());
        checkBox_4->setSizePolicy(sizePolicy);
        checkBox_4->setMinimumSize(QSize(0, 40));
        checkBox_4->setStyleSheet(QLatin1String("QCheckBox\n"
"{\n"
"color: rgb(54, 35, 35);\n"
"font: 24pt \"Ubuntu\";\n"
"}\n"
"\n"
"QCheckBox::indicator { width:50px; height: 50px; }"));

        gridLayout_8->addWidget(checkBox_4, 0, 1, 1, 1);

        checkBox_3 = new QCheckBox(groupBox_4);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        sizePolicy.setHeightForWidth(checkBox_3->sizePolicy().hasHeightForWidth());
        checkBox_3->setSizePolicy(sizePolicy);
        checkBox_3->setMinimumSize(QSize(0, 40));
        checkBox_3->setStyleSheet(QLatin1String("QCheckBox\n"
"{\n"
"color: rgb(54, 35, 35);\n"
"font: 24pt \"Ubuntu\";\n"
"}\n"
"\n"
"QCheckBox::indicator { width:50px; height: 50px; }"));

        gridLayout_8->addWidget(checkBox_3, 1, 0, 1, 1);

        checkBox_6 = new QCheckBox(groupBox_4);
        checkBox_6->setObjectName(QStringLiteral("checkBox_6"));
        sizePolicy.setHeightForWidth(checkBox_6->sizePolicy().hasHeightForWidth());
        checkBox_6->setSizePolicy(sizePolicy);
        checkBox_6->setMinimumSize(QSize(0, 40));
        checkBox_6->setStyleSheet(QLatin1String("QCheckBox\n"
"{\n"
"color: rgb(54, 35, 35);\n"
"font: 24pt \"Ubuntu\";\n"
"}\n"
"\n"
"QCheckBox::indicator { width:50px; height: 50px; }"));

        gridLayout_8->addWidget(checkBox_6, 1, 1, 1, 1);

        checkBox_8 = new QCheckBox(groupBox_4);
        checkBox_8->setObjectName(QStringLiteral("checkBox_8"));
        sizePolicy.setHeightForWidth(checkBox_8->sizePolicy().hasHeightForWidth());
        checkBox_8->setSizePolicy(sizePolicy);
        checkBox_8->setMinimumSize(QSize(0, 40));
        checkBox_8->setStyleSheet(QLatin1String("QCheckBox\n"
"{\n"
"color: rgb(54, 35, 35);\n"
"font: 24pt \"Ubuntu\";\n"
"}\n"
"\n"
"QCheckBox::indicator { width:50px; height: 50px; }"));

        gridLayout_8->addWidget(checkBox_8, 2, 0, 1, 1);

        checkBox_5 = new QCheckBox(groupBox_4);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));
        sizePolicy.setHeightForWidth(checkBox_5->sizePolicy().hasHeightForWidth());
        checkBox_5->setSizePolicy(sizePolicy);
        checkBox_5->setMinimumSize(QSize(0, 40));
        checkBox_5->setStyleSheet(QLatin1String("QCheckBox\n"
"{\n"
"color: rgb(54, 35, 35);\n"
"font: 24pt \"Ubuntu\";\n"
"}\n"
"\n"
"QCheckBox::indicator { width:50px; height: 50px; }"));

        gridLayout_8->addWidget(checkBox_5, 2, 1, 1, 1);

        checkBox_9 = new QCheckBox(groupBox_4);
        checkBox_9->setObjectName(QStringLiteral("checkBox_9"));
        sizePolicy.setHeightForWidth(checkBox_9->sizePolicy().hasHeightForWidth());
        checkBox_9->setSizePolicy(sizePolicy);
        checkBox_9->setMinimumSize(QSize(0, 40));
        checkBox_9->setStyleSheet(QLatin1String("QCheckBox\n"
"{\n"
"color: rgb(54, 35, 35);\n"
"font: 24pt \"Ubuntu\";\n"
"}\n"
"\n"
"QCheckBox::indicator { width:50px; height: 50px; }"));

        gridLayout_8->addWidget(checkBox_9, 3, 0, 1, 1);

        checkBox_7 = new QCheckBox(groupBox_4);
        checkBox_7->setObjectName(QStringLiteral("checkBox_7"));
        sizePolicy.setHeightForWidth(checkBox_7->sizePolicy().hasHeightForWidth());
        checkBox_7->setSizePolicy(sizePolicy);
        checkBox_7->setMinimumSize(QSize(0, 40));
        checkBox_7->setStyleSheet(QLatin1String("QCheckBox\n"
"{\n"
"color: rgb(54, 35, 35);\n"
"font: 24pt \"Ubuntu\";\n"
"}\n"
"\n"
"QCheckBox::indicator { width:50px; height: 50px; }"));

        gridLayout_8->addWidget(checkBox_7, 3, 1, 1, 1);


        gridLayout_11->addWidget(groupBox_4, 0, 0, 1, 1);

        Settings->addTab(Features, QString());
        Miscelleanous = new QWidget();
        Miscelleanous->setObjectName(QStringLiteral("Miscelleanous"));
        Miscelleanous->setMinimumSize(QSize(0, 0));
        gridLayout_12 = new QGridLayout(Miscelleanous);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        groupBox_5 = new QGroupBox(Miscelleanous);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        gridLayout_9 = new QGridLayout(groupBox_5);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        label_7 = new QLabel(groupBox_5);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setMinimumSize(QSize(0, 80));
        label_7->setStyleSheet(QLatin1String("background-color:transparent;\n"
"color: rgb(54, 35, 35);\n"
"font: 24pt \"Ubuntu\";"));

        gridLayout_9->addWidget(label_7, 0, 0, 1, 1);

        comboBox_2 = new QComboBox(groupBox_5);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        sizePolicy.setHeightForWidth(comboBox_2->sizePolicy().hasHeightForWidth());
        comboBox_2->setSizePolicy(sizePolicy);
        comboBox_2->setMinimumSize(QSize(0, 80));
        comboBox_2->setStyleSheet(QLatin1String("background-color:rgb(101, 104, 103);\n"
"font: 24pt \"Ubuntu\";"));

        gridLayout_9->addWidget(comboBox_2, 0, 1, 1, 1);

        label_8 = new QLabel(groupBox_5);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(0, 80));
        label_8->setStyleSheet(QLatin1String("background-color:transparent;\n"
"color: rgb(54, 35, 35);\n"
"font: 24pt \"Ubuntu\";"));

        gridLayout_9->addWidget(label_8, 1, 0, 1, 1);

        timeEdit_2 = new QTimeEdit(groupBox_5);
        timeEdit_2->setObjectName(QStringLiteral("timeEdit_2"));
        sizePolicy.setHeightForWidth(timeEdit_2->sizePolicy().hasHeightForWidth());
        timeEdit_2->setSizePolicy(sizePolicy);
        timeEdit_2->setMinimumSize(QSize(0, 80));
        timeEdit_2->setStyleSheet(QLatin1String("QTimeEdit\n"
"{\n"
"background-color:rgb(101, 104, 103);\n"
"font: 24pt \"Ubuntu\";\n"
"}\n"
"\n"
"QTimeEdit::up-button{width:100px;  height:40px;}\n"
"QTimeEdit::down-button{width:100px;  height:40px;};\n"
"\n"
""));

        gridLayout_9->addWidget(timeEdit_2, 1, 1, 1, 1);

        timeEdit_3 = new QTimeEdit(groupBox_5);
        timeEdit_3->setObjectName(QStringLiteral("timeEdit_3"));
        sizePolicy.setHeightForWidth(timeEdit_3->sizePolicy().hasHeightForWidth());
        timeEdit_3->setSizePolicy(sizePolicy);
        timeEdit_3->setMinimumSize(QSize(0, 80));
        timeEdit_3->setStyleSheet(QLatin1String("QTimeEdit\n"
"{\n"
"background-color:rgb(101, 104, 103);\n"
"font: 24pt \"Ubuntu\";\n"
"}\n"
"\n"
"QTimeEdit::up-button{width:100px;  height:40px;}\n"
"QTimeEdit::down-button{width:100px;  height:40px;};\n"
"\n"
""));

        gridLayout_9->addWidget(timeEdit_3, 3, 1, 1, 1);

        label_9 = new QLabel(groupBox_5);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMinimumSize(QSize(0, 80));
        label_9->setStyleSheet(QLatin1String("background-color:transparent;\n"
"color: rgb(54, 35, 35);\n"
"font: 24pt \"Ubuntu\";"));

        gridLayout_9->addWidget(label_9, 2, 0, 2, 1);


        gridLayout_12->addWidget(groupBox_5, 0, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(224, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_12->addItem(horizontalSpacer_6, 0, 1, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 91, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout_12->addItem(verticalSpacer_5, 1, 0, 1, 1);

        Settings->addTab(Miscelleanous, QString());

        gridLayout_13->addWidget(Settings, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        save = new QPushButton(PIS_SETTINGS);
        save->setObjectName(QStringLiteral("save"));
        save->setMinimumSize(QSize(0, 40));
        save->setStyleSheet(QLatin1String("background-color:rgb(101, 104, 103);\n"
"font: 22pt \"Sans Serif\";\n"
"color: rgb(54, 35, 35);"));

        horizontalLayout->addWidget(save);

        close = new QPushButton(PIS_SETTINGS);
        close->setObjectName(QStringLiteral("close"));
        close->setMinimumSize(QSize(0, 40));
        close->setStyleSheet(QLatin1String("background-color:rgb(101, 104, 103);\n"
"font: 22pt \"Sans Serif\";\n"
"color: rgb(54, 35, 35);"));

        horizontalLayout->addWidget(close);


        gridLayout_13->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(PIS_SETTINGS);

        Settings->setCurrentIndex(5);


        QMetaObject::connectSlotsByName(PIS_SETTINGS);
    } // setupUi

    void retranslateUi(QWidget *PIS_SETTINGS)
    {
        PIS_SETTINGS->setWindowTitle(QApplication::translate("PIS_SETTINGS", "Form", 0));
        groupBox->setTitle(QString());
        label_11->setText(QApplication::translate("PIS_SETTINGS", "  CCA Initials       ", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("PIS_SETTINGS", "S", 0)
         << QApplication::translate("PIS_SETTINGS", "B", 0)
         << QApplication::translate("PIS_SETTINGS", "A", 0)
         << QApplication::translate("PIS_SETTINGS", "HA", 0)
         << QApplication::translate("PIS_SETTINGS", "H", 0)
        );
        label_12->setText(QApplication::translate("PIS_SETTINGS", "  Coach ID           ", 0));
        Settings->setTabText(Settings->indexOf(CoachSettings), QApplication::translate("PIS_SETTINGS", " Coach Setting ", 0));
        groupBox_2->setTitle(QString());
        label->setText(QApplication::translate("PIS_SETTINGS", " Server IP         ", 0));
        label_2->setText(QApplication::translate("PIS_SETTINGS", "  Port Sync         ", 0));
        label_3->setText(QApplication::translate("PIS_SETTINGS", "  Port Async      ", 0));
        Settings->setTabText(Settings->indexOf(ServerSettings), QApplication::translate("PIS_SETTINGS", " Server Setting ", 0));
        groupBox_3->setTitle(QString());
        label_10->setText(QApplication::translate("PIS_SETTINGS", "  Select File", 0));
        pushButton_2->setText(QApplication::translate("PIS_SETTINGS", "Start", 0));
        Settings->setTabText(Settings->indexOf(Simulation), QApplication::translate("PIS_SETTINGS", " Simulation ", 0));
        groupBox_6->setTitle(QString());
        label_5->setText(QApplication::translate("PIS_SETTINGS", " Date                 ", 0));
        label_6->setText(QApplication::translate("PIS_SETTINGS", " Time               ", 0));
        Settings->setTabText(Settings->indexOf(TimeSettings), QApplication::translate("PIS_SETTINGS", " Date/Time ", 0));
        groupBox_4->setTitle(QString());
        checkBox->setText(QApplication::translate("PIS_SETTINGS", "   Speed", 0));
        checkBox_4->setText(QApplication::translate("PIS_SETTINGS", "   Safety Slogans           ", 0));
        checkBox_3->setText(QApplication::translate("PIS_SETTINGS", "   Logging", 0));
        checkBox_6->setText(QApplication::translate("PIS_SETTINGS", "   Announcement", 0));
        checkBox_8->setText(QApplication::translate("PIS_SETTINGS", "   Destination Board", 0));
        checkBox_5->setText(QApplication::translate("PIS_SETTINGS", "   Route Toggle", 0));
        checkBox_9->setText(QApplication::translate("PIS_SETTINGS", "   Fault Monitoriing of Slaves   ", 0));
        checkBox_7->setText(QApplication::translate("PIS_SETTINGS", "   AC/Non-AC", 0));
        Settings->setTabText(Settings->indexOf(Features), QApplication::translate("PIS_SETTINGS", " Features ", 0));
        groupBox_5->setTitle(QString());
        label_7->setText(QApplication::translate("PIS_SETTINGS", "Logging Frequency ", 0));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("PIS_SETTINGS", "1", 0)
         << QApplication::translate("PIS_SETTINGS", "2", 0)
         << QApplication::translate("PIS_SETTINGS", "3", 0)
         << QApplication::translate("PIS_SETTINGS", "4", 0)
         << QApplication::translate("PIS_SETTINGS", "5", 0)
         << QApplication::translate("PIS_SETTINGS", "10", 0)
         << QApplication::translate("PIS_SETTINGS", "15", 0)
         << QApplication::translate("PIS_SETTINGS", "20", 0)
         << QApplication::translate("PIS_SETTINGS", "30", 0)
         << QApplication::translate("PIS_SETTINGS", "60", 0)
        );
        label_8->setText(QApplication::translate("PIS_SETTINGS", "Announcement On Time ", 0));
        label_9->setText(QApplication::translate("PIS_SETTINGS", "Announcement Off Time ", 0));
        Settings->setTabText(Settings->indexOf(Miscelleanous), QApplication::translate("PIS_SETTINGS", " Miscellaneous ", 0));
        save->setText(QApplication::translate("PIS_SETTINGS", "Save", 0));
        close->setText(QApplication::translate("PIS_SETTINGS", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class PIS_SETTINGS: public Ui_PIS_SETTINGS {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIS_SETTINGS_H
