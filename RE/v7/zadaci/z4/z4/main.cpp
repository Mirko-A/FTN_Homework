#include "ledswitcher.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    if (wiringPiSetup() == -1) exit(1);
    pinMode(LED_PIN, OUTPUT);

    QApplication a(argc, argv);
    LedSwitcher w;
    w.show();
    return a.exec();
}
