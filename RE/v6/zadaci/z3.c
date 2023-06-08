#include <bcm2835.h>
#include <stdio.h>
#include <unistd.h>

unsigned char WriteBuf;
unsigned char ReadBuf;
unsigned char b[]={0x40,0x00};

#define LOW_LIGHT 50u
#define MID_LIGHT 150u
#define HIGH_LIGHT 255u

int main(void)
{

    if (!bcm2835_init())
        return 1;
		
    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(0x48);
    bcm2835_i2c_set_baudrate(10000);
    
    while(1)
    {
        WriteBuf = 0x00;
        bcm2835_i2c_write_read_rs(&WriteBuf, 1, &ReadBuf0, 1);
        bcm2835_i2c_read(&ReadBuf0, 1);
        double conv_light_level = (double)ReadBuf0 * 3.3 / 255;

        if (conv_light_level < 2.8f)
        {
           printf("NIVO OSVETLJENOSTI: VISOK\n");
           b[1] = HIGH_LIGHT;
        }
        else if (conv_light_level < 3.0f)
        {
           printf("NIVO OSVETLJENOSTI: SREDNJI\n");
           b[1] = MID_LIGHT;
        }
        else
        {
           printf("NIVO OSVETLJENOSTI: NIZAK\n");
           b[1] = LOW_LIGHT;
        }

        bcm2835_i2c_write((const char *)&b, 2);
        bcm2835_delay(10);
    }
    bcm2835_i2c_end();
    bcm2835_close();
    return 0;
}