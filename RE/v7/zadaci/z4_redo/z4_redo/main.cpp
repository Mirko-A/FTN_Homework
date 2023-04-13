#include "ledswitcher.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LedSwitcher w;
    w.show();
    return a.exec();
}
