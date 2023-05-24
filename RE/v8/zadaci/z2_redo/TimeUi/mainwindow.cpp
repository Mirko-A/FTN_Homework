#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>

const QString format = "hh:mm:ss";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sec_ticker = new QTimer(this);
    connect(sec_ticker, SIGNAL(timeout()), this, SLOT(updateTime()));
    sec_ticker->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete sec_ticker;
}


void MainWindow::on_Taster_clicked()
{

}

void MainWindow::updateTime(void)
{
    readTime(rtc_i2c_fd);
    QTime time(a_clock[HOUR], a_clock[MNT], a_clock[SEC], 0);
    QString time_str = time.toString(format);
    ui->Ispis->setText(time_str);
}
