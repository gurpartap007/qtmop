/********************************************************************************
** Form generated from reading UI file 'running_route.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RUNNING_ROUTE_H
#define UI_RUNNING_ROUTE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_running_route
{
public:
    QGridLayout *gridLayout_2;
    QLabel *RouteNUm;
    QLabel *TrainName;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QLabel *nxt_station;
    QLabel *label_6;
    QLabel *distance;
    QLabel *label_8;
    QLabel *estimatedtimearr;
    QLabel *label_10;
    QLabel *next_upcoming;

    void setupUi(QWidget *running_route)
    {
        if (running_route->objectName().isEmpty())
            running_route->setObjectName(QStringLiteral("running_route"));
        running_route->resize(437, 319);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(running_route->sizePolicy().hasHeightForWidth());
        running_route->setSizePolicy(sizePolicy);
        running_route->setMaximumSize(QSize(1920, 1080));
        running_route->setStyleSheet(QLatin1String("QWidget\n"
"{	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:0.983, stop:0.0619048 rgba(138, 138, 138, 255), stop:0.357143 rgba(203, 203, 203, 255), stop:0.747619 rgba(203, 203, 203, 255), stop:1 rgba(138, 138, 138, 255));\n"
"	\n"
"	font:24pt;\n"
"	/*border: 2px solid;\n"
"	border-radius:4px;\n"
"	border-color:rgb(54, 35, 35);\n"
"	\n"
" /*	border-style: outset;*/\n"
"\n"
"}\n"
"QTreeView {font: 40pt \\\"Arial\\\";}\n"
""));
        gridLayout_2 = new QGridLayout(running_route);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        RouteNUm = new QLabel(running_route);
        RouteNUm->setObjectName(QStringLiteral("RouteNUm"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(RouteNUm->sizePolicy().hasHeightForWidth());
        RouteNUm->setSizePolicy(sizePolicy1);
        RouteNUm->setMinimumSize(QSize(0, 40));
        RouteNUm->setMaximumSize(QSize(420, 80));
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        font.setPointSize(28);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        RouteNUm->setFont(font);
        RouteNUm->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"font: 28pt \"Ubuntu\";\n"
"background-color:transparent;\n"
"color: rgb(54, 35, 35);\n"
"}"));
        RouteNUm->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(RouteNUm, 0, 0, 1, 1);

        TrainName = new QLabel(running_route);
        TrainName->setObjectName(QStringLiteral("TrainName"));
        sizePolicy.setHeightForWidth(TrainName->sizePolicy().hasHeightForWidth());
        TrainName->setSizePolicy(sizePolicy);
        TrainName->setMaximumSize(QSize(1520, 80));
        TrainName->setFont(font);
        TrainName->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"font: 28pt \"Ubuntu\";\n"
"background-color:transparent;\n"
"color: rgb(54, 35, 35);\n"
"}"));
        TrainName->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(TrainName, 0, 1, 1, 1);

        groupBox = new QGroupBox(running_route);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setMinimumSize(QSize(0, 40));
        label_4->setMaximumSize(QSize(420, 16777215));
        label_4->setAutoFillBackground(false);
        label_4->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"font: 28pt \"Ubuntu\";\n"
"background-color:transparent;\n"
"color: rgb(54, 35, 35);\n"
"}"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        nxt_station = new QLabel(groupBox);
        nxt_station->setObjectName(QStringLiteral("nxt_station"));
        nxt_station->setMinimumSize(QSize(50, 40));
        nxt_station->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"font: 28pt \"Ubuntu\";\n"
"background-color:transparent;\n"
"color: rgb(54, 35, 35);\n"
"}"));
        nxt_station->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(nxt_station, 0, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(0, 40));
        label_6->setMaximumSize(QSize(420, 16777215));
        label_6->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"font: 28pt \"Ubuntu\";\n"
"background-color:transparent;\n"
"color: rgb(54, 35, 35);\n"
"}"));
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_6, 1, 0, 1, 1);

        distance = new QLabel(groupBox);
        distance->setObjectName(QStringLiteral("distance"));
        distance->setMinimumSize(QSize(50, 40));
        distance->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"font: 28pt \"Ubuntu\";\n"
"background-color:transparent;\n"
"color: rgb(54, 35, 35);\n"
"}"));
        distance->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(distance, 1, 1, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(0, 40));
        label_8->setMaximumSize(QSize(420, 16777215));
        label_8->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"font: 28pt \"Ubuntu\";\n"
"background-color:transparent;\n"
"color: rgb(54, 35, 35);\n"
"}"));
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_8, 2, 0, 1, 1);

        estimatedtimearr = new QLabel(groupBox);
        estimatedtimearr->setObjectName(QStringLiteral("estimatedtimearr"));
        estimatedtimearr->setMinimumSize(QSize(50, 40));
        estimatedtimearr->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"font: 28pt \"Ubuntu\";\n"
"background-color:transparent;\n"
"color: rgb(54, 35, 35);\n"
"}"));
        estimatedtimearr->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(estimatedtimearr, 2, 1, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setMinimumSize(QSize(0, 40));
        label_10->setMaximumSize(QSize(420, 16777215));
        label_10->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"font: 28pt \"Ubuntu\";\n"
"background-color:transparent;\n"
"color: rgb(54, 35, 35);\n"
"}"));
        label_10->setFrameShape(QFrame::NoFrame);
        label_10->setFrameShadow(QFrame::Plain);
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_10, 3, 0, 1, 1);

        next_upcoming = new QLabel(groupBox);
        next_upcoming->setObjectName(QStringLiteral("next_upcoming"));
        next_upcoming->setMinimumSize(QSize(50, 40));
        next_upcoming->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"font: 28pt \"Ubuntu\";\n"
"background-color:transparent;\n"
"color: rgb(54, 35, 35);\n"
"}"));
        next_upcoming->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(next_upcoming, 3, 1, 1, 1);


        gridLayout_2->addWidget(groupBox, 1, 0, 1, 2);


        retranslateUi(running_route);

        QMetaObject::connectSlotsByName(running_route);
    } // setupUi

    void retranslateUi(QWidget *running_route)
    {
        running_route->setWindowTitle(QApplication::translate("running_route", "Form", 0));
        RouteNUm->setText(QString());
        TrainName->setText(QString());
        groupBox->setTitle(QString());
        label_4->setText(QApplication::translate("running_route", "NEXT STATION:", 0));
        nxt_station->setText(QString());
        label_6->setText(QApplication::translate("running_route", "DISTANCE :", 0));
        distance->setText(QString());
        label_8->setText(QApplication::translate("running_route", "ETA :", 0));
        estimatedtimearr->setText(QString());
        label_10->setText(QApplication::translate("running_route", "UPCOMING STOPS : ", 0));
        next_upcoming->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class running_route: public Ui_running_route {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RUNNING_ROUTE_H
