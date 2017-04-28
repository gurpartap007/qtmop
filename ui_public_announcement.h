/********************************************************************************
** Form generated from reading UI file 'public_announcement.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PUBLIC_ANNOUNCEMENT_H
#define UI_PUBLIC_ANNOUNCEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_public_announcement
{
public:
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *start_announcement;
    QPushButton *end_announcement;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *public_announcement)
    {
        if (public_announcement->objectName().isEmpty())
            public_announcement->setObjectName(QStringLiteral("public_announcement"));
        public_announcement->resize(491, 209);
        public_announcement->setStyleSheet(QLatin1String("background-color: rgba(173, 216, 230,50);\n"
""));
        horizontalLayout_2 = new QHBoxLayout(public_announcement);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        start_announcement = new QPushButton(public_announcement);
        start_announcement->setObjectName(QStringLiteral("start_announcement"));
        start_announcement->setStyleSheet(QLatin1String("QPushButton:pressed{background-color: rgb(157, 255, 157); }\n"
"QPushButton{background-color: qlineargradient(spread:pad, x1:0.5, y0.8:0, x2:1, y1:0, stop:0 rgba(240, 240, 240, 150), stop:1 rgba(255, 255, 255, 255));}\n"
""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/start_announce.png"), QSize(), QIcon::Normal, QIcon::Off);
        start_announcement->setIcon(icon);
        start_announcement->setIconSize(QSize(80, 80));

        horizontalLayout->addWidget(start_announcement);

        end_announcement = new QPushButton(public_announcement);
        end_announcement->setObjectName(QStringLiteral("end_announcement"));
        end_announcement->setStyleSheet(QLatin1String("QPushButton:pressed{background-color: rgb(255, 192, 192); }\n"
"QPushButton{background-color: qlineargradient(spread:pad, x1:0.5, y0.8:0, x2:1, y1:0, stop:0 rgba(240, 240, 240, 150), stop:1 rgba(255, 255, 255, 255));}\n"
""));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/red_stop_button.png"), QSize(), QIcon::Normal, QIcon::Off);
        end_announcement->setIcon(icon1);
        end_announcement->setIconSize(QSize(80, 80));

        horizontalLayout->addWidget(end_announcement);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        retranslateUi(public_announcement);

        QMetaObject::connectSlotsByName(public_announcement);
    } // setupUi

    void retranslateUi(QWidget *public_announcement)
    {
        public_announcement->setWindowTitle(QApplication::translate("public_announcement", "Form", 0));
        start_announcement->setText(QString());
        end_announcement->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class public_announcement: public Ui_public_announcement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PUBLIC_ANNOUNCEMENT_H
