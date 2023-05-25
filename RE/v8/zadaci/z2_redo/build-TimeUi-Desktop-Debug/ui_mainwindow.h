/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *Taster;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *Unos;
    QLineEdit *Ispis;
    QCheckBox *InvertRow;
    QGroupBox *FormatRadioGroup;
    QRadioButton *Format24;
    QRadioButton *Format12;
    QMenuBar *menubar;
    QMenu *menuDisplay;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(437, 530);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Taster = new QPushButton(centralwidget);
        Taster->setObjectName(QString::fromUtf8("Taster"));
        Taster->setGeometry(QRect(200, 90, 121, 36));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 40, 141, 28));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 140, 161, 28));
        Unos = new QLineEdit(centralwidget);
        Unos->setObjectName(QString::fromUtf8("Unos"));
        Unos->setGeometry(QRect(200, 40, 121, 36));
        Ispis = new QLineEdit(centralwidget);
        Ispis->setObjectName(QString::fromUtf8("Ispis"));
        Ispis->setGeometry(QRect(200, 140, 121, 36));
        InvertRow = new QCheckBox(centralwidget);
        InvertRow->setObjectName(QString::fromUtf8("InvertRow"));
        InvertRow->setGeometry(QRect(30, 260, 261, 34));
        FormatRadioGroup = new QGroupBox(centralwidget);
        FormatRadioGroup->setObjectName(QString::fromUtf8("FormatRadioGroup"));
        FormatRadioGroup->setGeometry(QRect(30, 300, 281, 131));
        Format24 = new QRadioButton(FormatRadioGroup);
        Format24->setObjectName(QString::fromUtf8("Format24"));
        Format24->setGeometry(QRect(0, 30, 141, 34));
        Format12 = new QRadioButton(FormatRadioGroup);
        Format12->setObjectName(QString::fromUtf8("Format12"));
        Format12->setGeometry(QRect(0, 60, 141, 34));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 437, 33));
        menuDisplay = new QMenu(menubar);
        menuDisplay->setObjectName(QString::fromUtf8("menuDisplay"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuDisplay->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Taster->setText(QCoreApplication::translate("MainWindow", "Potvrdi", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Podesi vreme:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Trenutno vreme:", nullptr));
        Unos->setText(QCoreApplication::translate("MainWindow", "  hh:mm:ss", nullptr));
        Ispis->setText(QString());
        Ispis->setPlaceholderText(QCoreApplication::translate("MainWindow", "  00:00:00", nullptr));
        InvertRow->setText(QCoreApplication::translate("MainWindow", "Invertuj redove na LCD-u", nullptr));
        FormatRadioGroup->setTitle(QCoreApplication::translate("MainWindow", "Format vremena na LCD-u:", nullptr));
        Format24->setText(QCoreApplication::translate("MainWindow", "24-satni", nullptr));
        Format12->setText(QCoreApplication::translate("MainWindow", "12-satni", nullptr));
        menuDisplay->setTitle(QCoreApplication::translate("MainWindow", "Display", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
