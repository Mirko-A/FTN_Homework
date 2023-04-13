#include "sliderdimmer.h"
#include "wiringPi.h"
#include "softPwm.h"

#define LED_PIN (25u)

#include <QApplication>

int main(int argc, char *argv[])
{
    if (wiringPiSetup() == -1) exit(1);
    if (softPwmCreate(LED_PIN, 0, 100) != 0) exit(2);

    QApplication a(argc, argv);
    sliderDimmer w;
    w.show();
    return a.exec();
}
