#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Nedostaje drugi argument\n");
    exit(1);
  }

  int fd = - 1;
  int ret;

  char *tmp1;
  char tmp2[10];
  char ch = 't';

  char devname_head[50] = "/sys/devices/w1_bus_master1/28-00000";
  
  char devname_end[] = "/w1_slave";
  char devname[100];

  long value;
  int integer, decimal;
  char buffer[100];
  int i, j;

  strcpy(devname, devname_head);
  strcat(devname, argv[1]);
  strcat(devname, devname_end);

  if ((fd = open(devname, O_RDONLY)) < 0)
  {
    perror("GRESKA PRI OTVARANJU BATO");
    exit(1);
  }

  ret = read(fd, buffer, sizeof(buffer));
  
  if (ret < 0)
  {
    perror("GRESKA PRI CITANJU BATO");
    exit(1);
  }

  tmp1 = strchr(buffer, ch);
  sscanf(tmp1, "t=%s", tmp2);
  value = atoi(tmp2);
  
  integer = value / 1000;
  decimal = value % 1000;
  
  printf("Temperatura: %d.%d\n", integer, decimal);

  close(fd);
  return 0;
}


