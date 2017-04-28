/********************************************************************************
** Form generated from reading UI file 'prerecorded.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRERECORDED_H
#define UI_PRERECORDED_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreRecorded
{
public:
    QGridLayout *gridLayout;
    QPushButton *play;
    QPushButton *pushButton;
    QTableView *tableView;

    void setupUi(QWidget *PreRecorded)
    {
        if (PreRecorded->objectName().isEmpty())
            PreRecorded->setObjectName(QStringLiteral("PreRecorded"));
        PreRecorded->resize(570, 367);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PreRecorded->sizePolicy().hasHeightForWidth());
        PreRecorded->setSizePolicy(sizePolicy);
        PreRecorded->setMaximumSize(QSize(1000, 1080));
        PreRecorded->setWindowOpacity(0.95);
        PreRecorded->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(PreRecorded);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        play = new QPushButton(PreRecorded);
        play->setObjectName(QStringLiteral("play"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(play->sizePolicy().hasHeightForWidth());
        play->setSizePolicy(sizePolicy1);
        play->setMinimumSize(QSize(0, 40));
        play->setMaximumSize(QSize(500000, 16777215));
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        font.setPointSize(24);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        play->setFont(font);
        play->setStyleSheet(QLatin1String("background-color:rgb(101, 104, 103);\n"
"font: 24pt \"Ubuntu\";"));

        gridLayout->addWidget(play, 2, 0, 1, 1);

        pushButton = new QPushButton(PreRecorded);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(0, 40));
        pushButton->setMaximumSize(QSize(50000, 50000));
        pushButton->setLayoutDirection(Qt::RightToLeft);
        pushButton->setStyleSheet(QLatin1String("background-color:rgb(101, 104, 103);\n"
"font: 24pt \"Ubuntu\";"));

        gridLayout->addWidget(pushButton, 2, 1, 1, 1);

        tableView = new QTableView(PreRecorded);
        tableView->setObjectName(QStringLiteral("tableView"));
        sizePolicy.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy);
        tableView->setMaximumSize(QSize(50000, 16777215));
        QFont font1;
        font1.setPointSize(24);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        tableView->setFont(font1);
        tableView->setStyleSheet(QLatin1String(" background-color: rgb(179, 179, 179);\n"
"alternate-background-color: rgb(186, 186, 186);"));
        tableView->setAlternatingRowColors(true);

        gridLayout->addWidget(tableView, 1, 0, 1, 2);


        retranslateUi(PreRecorded);

        QMetaObject::connectSlotsByName(PreRecorded);
    } // setupUi

    void retranslateUi(QWidget *PreRecorded)
    {
        PreRecorded->setWindowTitle(QApplication::translate("PreRecorded", "Form", 0));
        play->setText(QApplication::translate("PreRecorded", "Announce", 0));
        pushButton->setText(QApplication::translate("PreRecorded", "  Close  ", 0));
    } // retranslateUi

};

namespace Ui {
    class PreRecorded: public Ui_PreRecorded {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRERECORDED_H
