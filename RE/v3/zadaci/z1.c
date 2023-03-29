#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>
#include <wiringPi.h>

#define LED_PIN (25)

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    printf("ERROR: not enough arguments\n");
    exit(1);
  }

  if (wiringPiSetup() == -1)  
  {
    printf("ERROR: wiringPi library not working\n");
    exit(1);
  }

  pinMode(LED_PIN, OUTPUT);

  int fd = - 1;
  int ret;

  char *tmp1;
  char tmp2[10];
  char tmp3[10];
  char ch = 't';

  char devname_head[50] = "/sys/devices/w1_bus_master1/28-00000";
  
  char devname_end[] = "/w1_slave";
  char devname[100];

  long value;
  int integer, decimal, limit;
  char buffer[100];
  int i, j;

  strcpy(devname, devname_head);
  strcat(devname, argv[1]);
  strcat(devname, devname_end);

  strcpy(tmp3, argv[2]);
  limit = atoi(tmp3);

  while(1)
  {
    if ((fd = open(devname, O_RDONLY)) < 0)
    {
      perror("GRESKA PRI OTVARANJU BATO");
      exit(1);
    }

    ret = read(fd, buffer, sizeof(buffer));
  
    if (ret < 0)
    {
      close(fd);
      perror("GRESKA PRI CITANJU BATO");
      exit(1);
    }

    tmp1 = strchr(buffer, ch);
    sscanf(tmp1, "t=%s", tmp2);
    value = atoi(tmp2);
  
    integer = value / 1000;
    decimal = value % 1000;
  
    if (integer >= limit)
    {
      int led_value = digitalRead(LED_PIN);
      if (led_value == 0)
      {
        digitalWrite(LED_PIN, 1);
      }
      else
      {
        digitalWrite(LED_PIN, 0);
      }
      //delay(200);
    }
    else
    {
      digitalWrite(LED_PIN, 0);
    }
    
    printf("Temperatura: %d.%d\n", integer, decimal);
    delay(500);

    close(fd);
  }

  return 0;
}


