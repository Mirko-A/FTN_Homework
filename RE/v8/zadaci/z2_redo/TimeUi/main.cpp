#include "mainwindow.h"

#include <QApplication>

#include <wiringPi.h>
#include <bcm2835.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

// adresa PCF8563 na I2C magistrali
#define DEVICE_ID (0x51)

// adrese PCF8563 registara (5, 6, 8 za DAN, MES, GOD)
#define SEC_ADDR    (0x02)
#define MIN_ADDR    (0x03)
#define HR_ADDR     (0x04)
#define DAY_ADDR    (0x05)
#define WEEK_ADDR   (0x06)
#define MONTH_ADDR  (0x07)
#define YEAR_ADDR   (0x08)

unsigned char WriteBuf[2] = {0};

unsigned char a_clock[13] = {0};

int bcdToD(unsigned char byte)
{
    unsigned int b1, b2;
    b1 = byte & 0x0F;
    b2 = ((byte >> 4) & 0x0F) * 10;
    return b1 + b2;
}

unsigned int dToBcd(unsigned int byte)
{
    return ((byte / 10) << 4) + (byte % 10);
}

void setInitialTime(void)
{
    struct tm t;
    time_t now;

    printf("Inititalizing the clock...\n");

    now = time(NULL);
    gmtime_r(&now, &t);

    // Set seconds
    a_clock[SEC] = dToBcd(t.tm_sec);
    WriteBuf[0] = SEC_ADDR;
    WriteBuf[1] = a_clock[SEC];
    bcm2835_i2c_write((const char *)WriteBuf, 2);

    // Set minutes
    a_clock[MNT] = dToBcd(t.tm_min);
    WriteBuf[0] = MIN_ADDR;
    WriteBuf[1] = a_clock[MNT];
    bcm2835_i2c_write((const char *)WriteBuf, 2);

    // Set hours
    a_clock[HOUR] = dToBcd(t.tm_hour);
    WriteBuf[0] = HR_ADDR;
    WriteBuf[1] = a_clock[HOUR];
    bcm2835_i2c_write((const char *)WriteBuf, 2);

    // Set day of month
    a_clock[DAY] = dToBcd(t.tm_mday);
    WriteBuf[0] = MONTH_ADDR;
    WriteBuf[1] = a_clock[DAY];
    bcm2835_i2c_write((const char *)WriteBuf, 2);

    // Set day of week
    a_clock[WEEK] = dToBcd(t.tm_wday);
    WriteBuf[0] = WEEK_ADDR;
    WriteBuf[1] = a_clock[WEEK];
    bcm2835_i2c_write((const char *)WriteBuf, 2);

    // Set month
    a_clock[MONTH] = dToBcd(t.tm_mon + 1);
    WriteBuf[0] = MONTH_ADDR;
    WriteBuf[1] = a_clock[MONTH];
    bcm2835_i2c_write((const char *)WriteBuf, 2);

    // Set year
    a_clock[YEAR] = dToBcd(t.tm_year - 100);
    WriteBuf[0] = YEAR_ADDR;
    WriteBuf[1] = a_clock[YEAR];
    bcm2835_i2c_write((const char *)WriteBuf, 2);
}

void rtcInit(void)
{
    setInitialTime();

    // Inicijalizacija RTC-a (start clock)
    WriteBuf[0] = 0x00;
    WriteBuf[1] = 0x00;

    bcm2835_i2c_write((const char *)WriteBuf, 2);
}

void setCustomTime(void)
{
    // Set seconds
    WriteBuf[0] = SEC_ADDR;
    WriteBuf[1] = a_clock[SEC];
    bcm2835_i2c_write((const char *)WriteBuf, 2);

    // Set minutes
    WriteBuf[0] = MIN_ADDR;
    WriteBuf[1] = a_clock[MNT];
    bcm2835_i2c_write((const char *)WriteBuf, 2);

    // Set hours
    WriteBuf[0] = HR_ADDR;
    WriteBuf[1] = a_clock[HOUR];
    bcm2835_i2c_write((const char *)WriteBuf, 2);

    // Set day of month
    WriteBuf[0] = DAY_ADDR;
    WriteBuf[1] = a_clock[DAY];
    bcm2835_i2c_write((const char *)WriteBuf, 2);

    // Set day of week
    WriteBuf[0] = WEEK_ADDR;
    WriteBuf[1] = a_clock[WEEK];
    bcm2835_i2c_write((const char *)WriteBuf, 2);

    // Set month
    WriteBuf[0] = MONTH_ADDR;
    WriteBuf[1] = a_clock[MONTH];
    bcm2835_i2c_write((const char *)WriteBuf, 2);

    // Set year
    WriteBuf[0] = YEAR_ADDR;
    WriteBuf[1] = a_clock[YEAR];
    bcm2835_i2c_write((const char *)WriteBuf, 2);
}

void readTime(void)
{
    WriteBuf[0] = SEC_ADDR;
    bcm2835_i2c_write_read_rs((char *)WriteBuf, 1, (char *)a_clock, SLOTS_LEN);

// TODO: put back in if needed
#if 0
    a_clock[0] =  a_clock[0] & 0x7F;
    a_clock[1] =  a_clock[1] & 0x7F;
    a_clock[2] =  a_clock[2] & 0x3F;
    a_clock[3] =  a_clock[3] & 0x3F;
    a_clock[5] = (a_clock[5] & 0x1F) + 1;
    a_clock[6] =  a_clock[6] + 100;
#endif
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    printf("Initializing I2C protocol...\n");
    if (!bcm2835_init())
    {
        printf("ERROR: Failed to init I2C communication.\n");
        return -1;
    }

    printf("Starting I2C communication...\n");
    bcm2835_i2c_begin();

    bcm2835_i2c_setSlaveAddress(DEVICE_ID);
    bcm2835_i2c_set_baudrate(10000);

    rtcInit();

    w.show();

    bcm2835_i2c_end();
    bcm2835_close();

    return a.exec();
}
