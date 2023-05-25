#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QMessageBox>

#include "lcd.h"

extern int rtc_i2c_fd;
extern int lcd_h;
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
    if (NewTime.isValid())
    {
        a_clock[HOUR] = dToBcd(NewTime.hour());
        a_clock[MNT] = dToBcd(NewTime.minute());
        a_clock[SEC] = dToBcd(NewTime.second());

        SetTime(rtc_i2c_fd);
    }
    else
    {
        QMessageBox::information(this, "Clock app", "Uneli ste pogresan format!");
    }
}

void MainWindow::updateTime(void)
{
    readTime(rtc_i2c_fd);
    QTime time(bcdToD(a_clock[HOUR]), bcdToD(a_clock[MNT]), bcdToD(a_clock[SEC]), 0);
    QString time_str = time.toString(format);
    ui->Ispis->setText(time_str);

//    int y = 0;
//    if (ui->InvertRow)
//    {
//        y = (y == 0) ? 1 : 0;
//    }

    lcdClear(lcd_h);
    lcdPosition(lcd_h, 0, 0);
    lcdPrintf(lcd_h, time_str.toLocal8Bit().data());
}
