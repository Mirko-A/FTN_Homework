/********************************************************************************
** Form generated from reading UI file 'sliderdimmer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLIDERDIMMER_H
#define UI_SLIDERDIMMER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sliderDimmer
{
public:
    QWidget *centralwidget;
    QSlider *horizontalSlider;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *sliderDimmer)
    {
        if (sliderDimmer->objectName().isEmpty())
            sliderDimmer->setObjectName(QString::fromUtf8("sliderDimmer"));
        sliderDimmer->resize(800, 600);
        centralwidget = new QWidget(sliderDimmer);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(230, 180, 291, 71));
        horizontalSlider->setMaximum(100);
        horizontalSlider->setOrientation(Qt::Horizontal);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(290, 100, 221, 61));
        QFont font;
        font.setPointSize(24);
        label->setFont(font);
        sliderDimmer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(sliderDimmer);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 33));
        sliderDimmer->setMenuBar(menubar);
        statusbar = new QStatusBar(sliderDimmer);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        sliderDimmer->setStatusBar(statusbar);

        retranslateUi(sliderDimmer);

        QMetaObject::connectSlotsByName(sliderDimmer);
    } // setupUi

    void retranslateUi(QMainWindow *sliderDimmer)
    {
        sliderDimmer->setWindowTitle(QCoreApplication::translate("sliderDimmer", "sliderDimmer", nullptr));
        label->setText(QCoreApplication::translate("sliderDimmer", "LED dimmer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sliderDimmer: public Ui_sliderDimmer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLIDERDIMMER_H
