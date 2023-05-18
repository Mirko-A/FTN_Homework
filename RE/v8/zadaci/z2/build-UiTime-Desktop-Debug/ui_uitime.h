/********************************************************************************
** Form generated from reading UI file 'uitime.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UITIME_H
#define UI_UITIME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UiTime
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QLineEdit *Unos;
    QLineEdit *Ispis;
    QMenuBar *menubar;
    QMenu *menuDialog;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *UiTime)
    {
        if (UiTime->objectName().isEmpty())
            UiTime->setObjectName(QString::fromUtf8("UiTime"));
        UiTime->resize(800, 600);
        centralwidget = new QWidget(UiTime);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(180, 200, 141, 28));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(180, 310, 171, 28));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(380, 240, 131, 36));
        Unos = new QLineEdit(centralwidget);
        Unos->setObjectName(QString::fromUtf8("Unos"));
        Unos->setGeometry(QRect(380, 200, 131, 36));
        Ispis = new QLineEdit(centralwidget);
        Ispis->setObjectName(QString::fromUtf8("Ispis"));
        Ispis->setGeometry(QRect(380, 310, 131, 36));
        UiTime->setCentralWidget(centralwidget);
        menubar = new QMenuBar(UiTime);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 33));
        menuDialog = new QMenu(menubar);
        menuDialog->setObjectName(QString::fromUtf8("menuDialog"));
        UiTime->setMenuBar(menubar);
        statusbar = new QStatusBar(UiTime);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        UiTime->setStatusBar(statusbar);

        menubar->addAction(menuDialog->menuAction());

        retranslateUi(UiTime);

        QMetaObject::connectSlotsByName(UiTime);
    } // setupUi

    void retranslateUi(QMainWindow *UiTime)
    {
        UiTime->setWindowTitle(QCoreApplication::translate("UiTime", "UiTime", nullptr));
        label->setText(QCoreApplication::translate("UiTime", "Podesi vreme: ", nullptr));
        label_2->setText(QCoreApplication::translate("UiTime", "Trenutno vreme: ", nullptr));
        pushButton->setText(QCoreApplication::translate("UiTime", "Potvrdi", nullptr));
        Unos->setText(QString());
        Unos->setPlaceholderText(QCoreApplication::translate("UiTime", "   hh:mm:ss", nullptr));
        menuDialog->setTitle(QCoreApplication::translate("UiTime", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UiTime: public Ui_UiTime {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UITIME_H
