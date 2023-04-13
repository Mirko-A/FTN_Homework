#include "slideandprogress.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SlideAndProgress w;
    w.show();
    return a.exec();
}
