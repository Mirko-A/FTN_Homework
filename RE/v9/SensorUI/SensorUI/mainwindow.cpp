#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>
#include <wiringPi.h>

extern int fd;

extern char devname_head[50];

extern char devname_end[15];
extern char devname[100];

extern int ret;

extern char *tmp1;
extern char tmp2[10];
extern char ch;

extern long value;
extern int  integer;
extern int  decimal;
extern char buffer[100];

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sec_ticker = new QTimer(this);
    connect(sec_ticker, SIGNAL(timeout()), this, SLOT(UpdateTemperature()));
    sec_ticker->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete sec_ticker;
}

void MainWindow::UpdateTemperature()
{
    if ((fd = open(devname, O_RDONLY)) < 0)
     {
       perror("Cannot establish communication with DS18B20");
       exit(1);
     }

     ret = read(fd, buffer, sizeof(buffer));

     if (ret < 0)
     {
       //close(fd);
       perror("Cannot read temperature");
       exit(1);
     }

     tmp1 = strchr(buffer, ch);
     sscanf(tmp1, "t=%s", tmp2);
     value = atoi(tmp2);

     integer = value / 1000;
     decimal = value % 1000;

     ui->TempLCD->display(QString::number(integer) + "." + QString::number(decimal).mid(0, 2));
}

