/********************************************************************************
** Form generated from reading UI file 'PIS.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIS_H
#define UI_PIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PIS_VIEW
{
public:
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *routesel;
    QPushButton *prerecord;
    QPushButton *setts;

    void setupUi(QWidget *PIS_VIEW)
    {
        if (PIS_VIEW->objectName().isEmpty())
            PIS_VIEW->setObjectName(QStringLiteral("PIS_VIEW"));
        PIS_VIEW->setEnabled(true);
        PIS_VIEW->resize(263, 128);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PIS_VIEW->sizePolicy().hasHeightForWidth());
        PIS_VIEW->setSizePolicy(sizePolicy);
        PIS_VIEW->setMinimumSize(QSize(20, 0));
        PIS_VIEW->setMaximumSize(QSize(1920, 1080));
        PIS_VIEW->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(PIS_VIEW);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        stackedWidget = new QStackedWidget(PIS_VIEW);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        stackedWidget->setMaximumSize(QSize(5000, 5000));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        stackedWidget->addWidget(page_2);

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        routesel = new QPushButton(PIS_VIEW);
        routesel->setObjectName(QStringLiteral("routesel"));
        sizePolicy.setHeightForWidth(routesel->sizePolicy().hasHeightForWidth());
        routesel->setSizePolicy(sizePolicy);
        routesel->setMinimumSize(QSize(0, 80));
        QFont font;
        font.setPointSize(24);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        routesel->setFont(font);
        routesel->setStyleSheet(QStringLiteral("background-color:rgb(101,104,103);"));

        horizontalLayout->addWidget(routesel);

        prerecord = new QPushButton(PIS_VIEW);
        prerecord->setObjectName(QStringLiteral("prerecord"));
        sizePolicy.setHeightForWidth(prerecord->sizePolicy().hasHeightForWidth());
        prerecord->setSizePolicy(sizePolicy);
        prerecord->setMinimumSize(QSize(0, 80));
        prerecord->setFont(font);
        prerecord->setStyleSheet(QStringLiteral("background-color:rgb(101,104,103);"));

        horizontalLayout->addWidget(prerecord);

        setts = new QPushButton(PIS_VIEW);
        setts->setObjectName(QStringLiteral("setts"));
        sizePolicy.setHeightForWidth(setts->sizePolicy().hasHeightForWidth());
        setts->setSizePolicy(sizePolicy);
        setts->setMinimumSize(QSize(0, 80));
        setts->setFont(font);
        setts->setStyleSheet(QStringLiteral("background-color:rgb(101,104,103);"));

        horizontalLayout->addWidget(setts);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(PIS_VIEW);

        QMetaObject::connectSlotsByName(PIS_VIEW);
    } // setupUi

    void retranslateUi(QWidget *PIS_VIEW)
    {
        PIS_VIEW->setWindowTitle(QApplication::translate("PIS_VIEW", "Form", 0));
        routesel->setText(QApplication::translate("PIS_VIEW", "Change Route", 0));
        prerecord->setText(QApplication::translate("PIS_VIEW", "Pre Recorded Messages", 0));
        setts->setText(QApplication::translate("PIS_VIEW", "Settings", 0));
    } // retranslateUi

};

namespace Ui {
    class PIS_VIEW: public Ui_PIS_VIEW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIS_H
