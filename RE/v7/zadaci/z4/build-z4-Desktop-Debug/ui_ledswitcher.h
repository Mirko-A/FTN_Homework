/********************************************************************************
** Form generated from reading UI file 'ledswitcher.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEDSWITCHER_H
#define UI_LEDSWITCHER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LedSwitcher
{
public:
    QWidget *centralwidget;
    QLabel *SwitchLabel;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LedSwitcher)
    {
        if (LedSwitcher->objectName().isEmpty())
            LedSwitcher->setObjectName(QString::fromUtf8("LedSwitcher"));
        LedSwitcher->resize(800, 600);
        centralwidget = new QWidget(LedSwitcher);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        SwitchLabel = new QLabel(centralwidget);
        SwitchLabel->setObjectName(QString::fromUtf8("SwitchLabel"));
        SwitchLabel->setGeometry(QRect(150, 100, 511, 191));
        QFont font;
        font.setPointSize(20);
        SwitchLabel->setFont(font);
        SwitchLabel->setPixmap(QPixmap(QString::fromUtf8(":/switch_off.png")));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(340, 310, 117, 36));
        pushButton->setCheckable(true);
        LedSwitcher->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LedSwitcher);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 33));
        LedSwitcher->setMenuBar(menubar);
        statusbar = new QStatusBar(LedSwitcher);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        LedSwitcher->setStatusBar(statusbar);

        retranslateUi(LedSwitcher);

        QMetaObject::connectSlotsByName(LedSwitcher);
    } // setupUi

    void retranslateUi(QMainWindow *LedSwitcher)
    {
        LedSwitcher->setWindowTitle(QCoreApplication::translate("LedSwitcher", "LedSwitcher", nullptr));
        SwitchLabel->setText(QString());
        pushButton->setText(QCoreApplication::translate("LedSwitcher", "Toggle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LedSwitcher: public Ui_LedSwitcher {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEDSWITCHER_H
