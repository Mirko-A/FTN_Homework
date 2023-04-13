/********************************************************************************
** Form generated from reading UI file 'slideandprogress.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLIDEANDPROGRESS_H
#define UI_SLIDEANDPROGRESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SlideAndProgress
{
public:
    QWidget *centralwidget;
    QProgressBar *progressBar;
    QSlider *horizontalSlider;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SlideAndProgress)
    {
        if (SlideAndProgress->objectName().isEmpty())
            SlideAndProgress->setObjectName(QString::fromUtf8("SlideAndProgress"));
        SlideAndProgress->resize(800, 600);
        centralwidget = new QWidget(SlideAndProgress);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(287, 370, 231, 51));
        progressBar->setValue(0);
        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(189, 195, 421, 101));
        horizontalSlider->setMaximum(100);
        horizontalSlider->setOrientation(Qt::Horizontal);
        SlideAndProgress->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SlideAndProgress);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 33));
        SlideAndProgress->setMenuBar(menubar);
        statusbar = new QStatusBar(SlideAndProgress);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SlideAndProgress->setStatusBar(statusbar);

        retranslateUi(SlideAndProgress);
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), progressBar, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(SlideAndProgress);
    } // setupUi

    void retranslateUi(QMainWindow *SlideAndProgress)
    {
        SlideAndProgress->setWindowTitle(QCoreApplication::translate("SlideAndProgress", "SlideAndProgress", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SlideAndProgress: public Ui_SlideAndProgress {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLIDEANDPROGRESS_H
