#include "mainwindow.h"

#include <QApplication>

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <lcd.h>

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

// dodela vrednosti za konkretne pinove
// prema gornjoj tabeli i semi DVK512
const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

char a_clock[7] = {0};

int lcd_h;
int rtc_i2c_fd;

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

void SetTime(int i2c_fd)
{
	// TODO: If it doesn't work try 0x20
    wiringPiI2CWriteReg8(i2c_fd, 0, 0x20); // Stop the clock
#if 1
	wiringPiI2CWriteReg8(i2c_fd, SEC_ADDR, a_clock[SEC]);
	wiringPiI2CWriteReg8(i2c_fd, MIN_ADDR, a_clock[MNT]);
	wiringPiI2CWriteReg8(i2c_fd, HR_ADDR, a_clock[HOUR]);
	wiringPiI2CWriteReg8(i2c_fd, DAY_ADDR, a_clock[DAY]);
	wiringPiI2CWriteReg8(i2c_fd, MONTH_ADDR, a_clock[MONTH]);
	wiringPiI2CWriteReg8(i2c_fd, YEAR_ADDR, a_clock[YEAR]);
#else
	// Start writing from register 0:
    wiringPiI2CWrite(i2c_fd, 2);
    // Write 7 bytes
    write(i2c_fd, a_clock, 7);
#endif
    wiringPiI2CWriteReg8(i2c_fd, 0, 0x00);  // Start the clock
}

void InitializeClock(int i2c_fd)
{
    struct tm t;
    time_t now;

    printf("Setting the clock...\n");

    now = time(NULL);
    gmtime_r(&now, &t);

    a_clock[SEC]   = dToBcd(t.tm_sec);
    a_clock[MNT]   = dToBcd(t.tm_min);
    a_clock[HOUR]  = dToBcd(t.tm_hour);
    a_clock[DAY]   = dToBcd(t.tm_mday);
    a_clock[WEEK]  = dToBcd(t.tm_wday);
    a_clock[MONTH] = dToBcd(t.tm_mon + 1);
    a_clock[YEAR]  = dToBcd(t.tm_year - 100);

	SetTime(i2c_fd);
}

void readTime(int i2c_fd)
{
#if 1
	a_clock[SEC]   = wiringPiI2CReadReg8(i2c_fd, SEC_ADDR);
	a_clock[MNT]   = wiringPiI2CReadReg8(i2c_fd, MIN_ADDR);
	a_clock[HOUR]  = wiringPiI2CReadReg8(i2c_fd, HR_ADDR);
	a_clock[DAY]   = wiringPiI2CReadReg8(i2c_fd, DAY_ADDR);
	a_clock[MONTH] = wiringPiI2CReadReg8(i2c_fd, MONTH_ADDR);
	a_clock[YEAR]  = wiringPiI2CReadReg8(i2c_fd, YEAR_ADDR);
#else
    // Start reading form register 0:
    wiringPiI2CWrite(i2c_fd, 2);
	
    // Read in 7 bytes
    int bytes_read = read(i2c_fd, a_clock, 7);

    if (bytes_read != 7)
    {
        printf("read got: %d\n", bytes_read);
    }
    else
    {
        printf("Read 7 bytes");
    }
#endif
}



int main(int argc, char *argv[])
{
    if (wiringPiSetup()  < 0)
    {
        printf("ERROR: Failed to init wiringPi.\n");
        return -1;
    }
	
    printf("Initializing I2C protocol...\n");
	rtc_i2c_fd = wiringPiI2CSetup(DEVICE_ID);
    if (rtc_i2c_fd < 0)
    {
        printf("ERROR: Failed to init I2C communication.\n");
        return -1;
    }
	
    InitializeClock(rtc_i2c_fd);
	
	// Start the clock
    wiringPiI2CWriteReg8(rtc_i2c_fd, 0, 0x00);
    //wiringPiI2CWriteReg8(rtc_i2c_fd, 1, 0x00); TODO: bring back if needed

    lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);

    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
