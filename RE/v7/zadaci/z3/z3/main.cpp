#include "ledswitches.h"
#include "stdint.h"
#include "wiringPi.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    uint8_t it;
    if (wiringPiSetup() == -1) exit(1);

    for (it = 0; it < 4; it++)
    {
        pinMode(LEDS[it], OUTPUT);
    }

    QApplication a(argc, argv);
    LedSwitches w;
    w.show();
    return a.exec();
}
