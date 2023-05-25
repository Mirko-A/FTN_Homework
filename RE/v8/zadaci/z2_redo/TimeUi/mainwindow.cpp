#include "mainwindow.h"
#include "ui_mainwindow.h"
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

int y_pos = 0;

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

void MainWindow::on_TasterAlarm_clicked()
{
    m_AlarmTime = new QTime(QTime::fromString(ui->UnosAlarm->text()));
    if (m_AlarmTime->isValid() == false)
    {
        QMessageBox::information(this, "Clock app", "Uneli ste pogresan format!");
        delete m_AlarmTime;
    }
}

void MainWindow::updateTime(void)
{
    QString time_str;
    readTime(rtc_i2c_fd);
    int Hours = bcdToD(a_clock[HOUR]);

    if (ui->Format12->isChecked())
    {
        if (Hours > 12)
        {
            QTime time(Hours - 12, bcdToD(a_clock[MNT]), bcdToD(a_clock[SEC]), 0);
            time_str = time.toString(format) + " PM";
        }
        else
        {
            QTime time(Hours, bcdToD(a_clock[MNT]), bcdToD(a_clock[SEC]), 0);
            time_str = time.toString(format) + " AM";
        }
    }
    else
    {
        QTime time(Hours, bcdToD(a_clock[MNT]), bcdToD(a_clock[SEC]), 0);
        time_str = time.toString(format);
    }

    if (m_AlarmTime != nullptr)
    {
        if (m_AlarmTime->toString() == time_str)
        {
            QMessageBox::information(this, "Clock app", "Alarm!!!");
            delete m_AlarmTime;
        }
    }

    ui->Ispis->setText(time_str);

    lcdClear(lcd_h);
    lcdPosition(lcd_h, 0, y_pos);
    lcdPrintf(lcd_h, time_str.toLocal8Bit().data());
}

void MainWindow::on_InvertRow_stateChanged(int arg1)
{
    if (arg1)
    {
        y_pos = 1;
    }
    else
    {
        y_pos = 0;
    }
}
