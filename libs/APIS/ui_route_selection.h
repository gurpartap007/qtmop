/********************************************************************************
** Form generated from reading UI file 'route_selection.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROUTE_SELECTION_H
#define UI_ROUTE_SELECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>
#include <lineedit.h>

QT_BEGIN_NAMESPACE

class Ui_route_selection
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    lineedit *lineEdit;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QTableView *tableView;

    void setupUi(QWidget *route_selection)
    {
        if (route_selection->objectName().isEmpty())
            route_selection->setObjectName(QStringLiteral("route_selection"));
        route_selection->resize(345, 253);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(route_selection->sizePolicy().hasHeightForWidth());
        route_selection->setSizePolicy(sizePolicy);
        route_selection->setMaximumSize(QSize(1920, 1080));
        route_selection->setStyleSheet(QLatin1String("QWidget\n"
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
"}"));
        gridLayout = new QGridLayout(route_selection);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(route_selection);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(0, 80));
        label->setMaximumSize(QSize(5000, 16777215));
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        font.setPointSize(24);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        label->setFont(font);
        label->setStyleSheet(QLatin1String("background-color:transparent;\n"
"color: rgb(54, 35, 35);\n"
"font: 24pt \"Ubuntu\";"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 1, 1, 1);

        lineEdit = new lineedit(route_selection);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy2);
        lineEdit->setMinimumSize(QSize(0, 80));
        lineEdit->setMaximumSize(QSize(5000, 80));
        QFont font1;
        font1.setPointSize(24);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        lineEdit->setFont(font1);
        lineEdit->setFocusPolicy(Qt::ClickFocus);
        lineEdit->setStyleSheet(QLatin1String("background-color: rgb(179, 179, 179);\n"
"border-color: rgb(117, 103, 103);"));

        gridLayout->addWidget(lineEdit, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        tableView = new QTableView(route_selection);
        tableView->setObjectName(QStringLiteral("tableView"));
        sizePolicy.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy);
        tableView->setMinimumSize(QSize(0, 0));
        tableView->setMaximumSize(QSize(5000, 16777215));
        QFont font2;
        font2.setFamily(QStringLiteral("Ubuntu"));
        font2.setPointSize(28);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        tableView->setFont(font2);
        tableView->setStyleSheet(QLatin1String("QTableView\n"
"{\n"
"background-color: rgb(185, 185, 185);\n"
"selection-background-color:blue;\n"
"font: 28pt \"Ubuntu\";\n"
"color: rgb(54, 35, 35);\n"
"}\n"
"\n"
"QTableView::item\n"
"{\n"
"height:80pt;\n"
"}"));
        tableView->setFrameShape(QFrame::WinPanel);
        tableView->setFrameShadow(QFrame::Sunken);
        tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

        gridLayout->addWidget(tableView, 1, 0, 1, 4);


        retranslateUi(route_selection);

        QMetaObject::connectSlotsByName(route_selection);
    } // setupUi

    void retranslateUi(QWidget *route_selection)
    {
        route_selection->setWindowTitle(QApplication::translate("route_selection", "Form", 0));
        label->setText(QApplication::translate("route_selection", "Route No:     ", 0));
        lineEdit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class route_selection: public Ui_route_selection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROUTE_SELECTION_H
