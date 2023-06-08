#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <wiringPiI2C.h>

#include <iostream>

extern unsigned char WriteBuf;
extern unsigned char ReadBuf;

extern int i2c_fd;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sec_ticker = new QTimer(this);
    connect(sec_ticker, SIGNAL(timeout()), this, SLOT(UpdateSensorValues()));
    sec_ticker->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete sec_ticker;
}

void MainWindow::UpdateSensorValues()
{
    ReadBuf = wiringPiI2CReadReg8(i2c_fd, VOLTAGE_ADDR);
    printf("%c", ReadBuf);
    double voltage = (double)ReadBuf * 3.3f / 255.0f;
    ui->Dial->setValue(255 - ReadBuf);

    ReadBuf = wiringPiI2CReadReg8(i2c_fd, LIGHT_ADDR);
    printf("%c", ReadBuf);
    double light = (double)ReadBuf / 255.0f * 3.3f;
    ui->LightSlide->setValue(255 - ReadBuf);
}
