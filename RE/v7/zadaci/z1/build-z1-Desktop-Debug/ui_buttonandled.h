/********************************************************************************
** Form generated from reading UI file 'buttonandled.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONANDLED_H
#define UI_BUTTONANDLED_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_buttonAndLed
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *buttonAndLed)
    {
        if (buttonAndLed->objectName().isEmpty())
            buttonAndLed->setObjectName(QString::fromUtf8("buttonAndLed"));
        buttonAndLed->resize(800, 600);
        centralwidget = new QWidget(buttonAndLed);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(300, 70, 171, 91));
        QFont font;
        font.setPointSize(26);
        label->setFont(font);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(320, 200, 117, 36));
        pushButton->setCheckable(true);
        buttonAndLed->setCentralWidget(centralwidget);
        menubar = new QMenuBar(buttonAndLed);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 33));
        buttonAndLed->setMenuBar(menubar);
        statusbar = new QStatusBar(buttonAndLed);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        buttonAndLed->setStatusBar(statusbar);

        retranslateUi(buttonAndLed);

        QMetaObject::connectSlotsByName(buttonAndLed);
    } // setupUi

    void retranslateUi(QMainWindow *buttonAndLed)
    {
        buttonAndLed->setWindowTitle(QCoreApplication::translate("buttonAndLed", "buttonAndLed", nullptr));
        label->setText(QCoreApplication::translate("buttonAndLed", "CLICK ME!", nullptr));
        pushButton->setText(QCoreApplication::translate("buttonAndLed", "Toggle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class buttonAndLed: public Ui_buttonAndLed {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONANDLED_H
