#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>

extern int rtc_i2c_fd;
extern char a_clock[];
extern void SetTime(int i2c_fd);
extern void readTime(int i2c_fd);

extern int bcdToD(unsigned char byte);
extern unsigned int dToBcd(unsigned int byte);

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
    QTime NewTime = QTime::fromString(ui->Unos->text());
    a_clock[HOUR] = dToBcd(NewTime.hour());
    a_clock[MNT] = dToBcd(NewTime.minute());
    a_clock[SEC] = dToBcd(NewTime.second());
}

void MainWindow::updateTime(void)
{
    readTime(rtc_i2c_fd);
    QTime time(bcdToD(a_clock[HOUR]), bcdToD(a_clock[MNT]), bcdToD(a_clock[SEC]), 0);
    QString time_str = time.toString(format);
    ui->Ispis->setText(time_str);
}
