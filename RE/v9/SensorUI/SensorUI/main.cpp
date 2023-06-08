#include "mainwindow.h"
#include "wiringPi.h"

#include "cstdint"

#include <QApplication>

int fd = -1;

char devname_head[50] = "/sys/devices/w1_bus_master1/28-00000";

char devname_end[15] = "/w1_slave";
char devname[100];

int ret;

char *tmp1;
char tmp2[10];
char ch = 't';

long value;
int  integer, decimal;
char buffer[100];
int i, j;

int main(int argc, char *argv[])
{
    for (i = 0; i < argc; i++)
        printf("%s ", argv[i]);

    if (argc < 2)
    {
      printf("ERROR: not enough arguments\n");
      exit(1);
    }

    if (wiringPiSetup() == -1)
    {
      printf("ERROR: wiringPi library not working\n");
      exit(1);
    }

    strcpy(devname, devname_head);
    strcat(devname, argv[1]);
    strcat(devname, devname_end);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
