#include "lcdtext.h"

#include <QApplication>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <stdint.h>
#include <lcd.h>

// dodela vrednosti za konkretne pinove
// prema gornjoj tabeli i semi DVK512
const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

int lcd;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (wiringPiSetup() < 0)
    {
        fprintf (stderr, "ERROR: %s\n", strerror (errno));
        return 1 ;
    }

    if((lcd = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3,  D0, D1, D2, D3)))
    {
        fprintf (stderr, "ERROR: %s\n", strerror (errno));
        return -1 ;
    }

    LcdText w;
    w.show();
    return a.exec();
}
