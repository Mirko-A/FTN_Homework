/********************************************************************************
** Form generated from reading UI file 'lcdtext.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LCDTEXT_H
#define UI_LCDTEXT_H

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

class Ui_LcdText
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QLineEdit *Red2_Txt;
    QLineEdit *Red1_Txt;
    QLabel *Red1_L;
    QLabel *Red2_L;
    QMenuBar *menubar;
    QMenu *menuDialog;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LcdText)
    {
        if (LcdText->objectName().isEmpty())
            LcdText->setObjectName(QString::fromUtf8("LcdText"));
        LcdText->resize(800, 600);
        centralwidget = new QWidget(LcdText);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(468, 260, 117, 36));
        Red2_Txt = new QLineEdit(centralwidget);
        Red2_Txt->setObjectName(QString::fromUtf8("Red2_Txt"));
        Red2_Txt->setGeometry(QRect(250, 260, 201, 36));
        Red1_Txt = new QLineEdit(centralwidget);
        Red1_Txt->setObjectName(QString::fromUtf8("Red1_Txt"));
        Red1_Txt->setGeometry(QRect(250, 210, 201, 36));
        Red1_L = new QLabel(centralwidget);
        Red1_L->setObjectName(QString::fromUtf8("Red1_L"));
        Red1_L->setGeometry(QRect(180, 210, 61, 28));
        Red2_L = new QLabel(centralwidget);
        Red2_L->setObjectName(QString::fromUtf8("Red2_L"));
        Red2_L->setGeometry(QRect(180, 270, 61, 28));
        LcdText->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LcdText);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 33));
        menuDialog = new QMenu(menubar);
        menuDialog->setObjectName(QString::fromUtf8("menuDialog"));
        LcdText->setMenuBar(menubar);
        statusbar = new QStatusBar(LcdText);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        LcdText->setStatusBar(statusbar);

        menubar->addAction(menuDialog->menuAction());

        retranslateUi(LcdText);

        QMetaObject::connectSlotsByName(LcdText);
    } // setupUi

    void retranslateUi(QMainWindow *LcdText)
    {
        LcdText->setWindowTitle(QCoreApplication::translate("LcdText", "LcdText", nullptr));
        pushButton->setText(QCoreApplication::translate("LcdText", "Text2LCD", nullptr));
        Red1_L->setText(QCoreApplication::translate("LcdText", "Red 1:", nullptr));
        Red2_L->setText(QCoreApplication::translate("LcdText", "Red 2:", nullptr));
        menuDialog->setTitle(QCoreApplication::translate("LcdText", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LcdText: public Ui_LcdText {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LCDTEXT_H
