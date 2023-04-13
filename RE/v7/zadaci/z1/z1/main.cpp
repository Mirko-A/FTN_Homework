#include "buttonandled.h"
#include "wiringPi.h"

#include <QApplication>

#define LED_PIN (25u)

int main(int argc, char *argv[])
{
    if (wiringPiSetup() == -1) exit(1);
    pinMode(LED_PIN, OUTPUT);

    QApplication a(argc, argv);
    buttonAndLed w;
    w.show();
    return a.exec();
}
