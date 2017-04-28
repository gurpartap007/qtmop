/********************************************************************************
** Form generated from reading UI file 'intercom.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERCOM_H
#define UI_INTERCOM_H

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

class Ui_intercom
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QPushButton *stop;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *intercom)
    {
        if (intercom->objectName().isEmpty())
            intercom->setObjectName(QStringLiteral("intercom"));
        intercom->resize(400, 300);
        intercom->setStyleSheet(QLatin1String("background-color: rgba(173, 216, 230,50);\n"
""));
        horizontalLayout = new QHBoxLayout(intercom);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(135, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        stop = new QPushButton(intercom);
        stop->setObjectName(QStringLiteral("stop"));
        stop->setStyleSheet(QLatin1String("QPushButton:pressed{background-color: rgb(255, 192, 192); }\n"
"QPushButton{background-color: qlineargradient(spread:pad, x1:0.5, y0.8:0, x2:1, y1:0, stop:0 rgba(240, 240, 240, 150), stop:1 rgba(255, 255, 255, 255));}\n"
""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/red_stop_button.png"), QSize(), QIcon::Normal, QIcon::Off);
        stop->setIcon(icon);
        stop->setIconSize(QSize(80, 80));

        verticalLayout->addWidget(stop);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(135, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        retranslateUi(intercom);

        QMetaObject::connectSlotsByName(intercom);
    } // setupUi

    void retranslateUi(QWidget *intercom)
    {
        intercom->setWindowTitle(QApplication::translate("intercom", "Form", 0));
        stop->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class intercom: public Ui_intercom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERCOM_H
