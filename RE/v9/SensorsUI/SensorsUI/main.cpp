#include "mainwindow.h"
#include <wiringPiI2C.h>
#include <stdio.h>
#include <unistd.h>

#include <QApplication>

unsigned char WriteBuf;
unsigned char ReadBuf;

int i2c_fd;

int main(int argc, char *argv[])
{
    i2c_fd = wiringPiI2CSetup(DEVICE_ID);
    if (i2c_fd < 0)
    {
        printf("ERROR: Failed to init I2C communication.\n");
        return -1;
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
