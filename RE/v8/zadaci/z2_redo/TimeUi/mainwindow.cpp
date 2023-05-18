#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QTimer>

const QString format = "hh:mm:ss";

void MainWindow::updateTime(void)
{
    readTime();
    QTime time(a_clock[HOUR], a_clock[MNT], a_clock[SEC], 0);
    QString time_str = time.toString(format);
    ui->Ispis->setText(time_str);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer* sec_ticker = new QTimer(this);
    connect(sec_ticker, SIGNAL(timeout()), this, SLOT(updateTime()));
    sec_ticker->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

