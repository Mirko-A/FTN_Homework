/********************************************************************************
** Form generated from reading UI file 'ledswitches.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEDSWITCHES_H
#define UI_LEDSWITCHES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LedSwitches
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LedSwitches)
    {
        if (LedSwitches->objectName().isEmpty())
            LedSwitches->setObjectName(QString::fromUtf8("LedSwitches"));
        LedSwitches->resize(800, 600);
        centralwidget = new QWidget(LedSwitches);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(200, 140, 371, 161));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        checkBox = new QCheckBox(gridLayoutWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout->addWidget(checkBox, 0, 0, 1, 1);

        checkBox_2 = new QCheckBox(gridLayoutWidget);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        gridLayout->addWidget(checkBox_2, 0, 1, 1, 1);

        checkBox_3 = new QCheckBox(gridLayoutWidget);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

        gridLayout->addWidget(checkBox_3, 1, 0, 1, 1);

        checkBox_4 = new QCheckBox(gridLayoutWidget);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));

        gridLayout->addWidget(checkBox_4, 1, 1, 1, 1);

        LedSwitches->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LedSwitches);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 33));
        LedSwitches->setMenuBar(menubar);
        statusbar = new QStatusBar(LedSwitches);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        LedSwitches->setStatusBar(statusbar);

        retranslateUi(LedSwitches);

        QMetaObject::connectSlotsByName(LedSwitches);
    } // setupUi

    void retranslateUi(QMainWindow *LedSwitches)
    {
        LedSwitches->setWindowTitle(QCoreApplication::translate("LedSwitches", "LedSwitches", nullptr));
        checkBox->setText(QCoreApplication::translate("LedSwitches", "LED0", nullptr));
        checkBox_2->setText(QCoreApplication::translate("LedSwitches", "LED1", nullptr));
        checkBox_3->setText(QCoreApplication::translate("LedSwitches", "LED2", nullptr));
        checkBox_4->setText(QCoreApplication::translate("LedSwitches", "LED3", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LedSwitches: public Ui_LedSwitches {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEDSWITCHES_H
