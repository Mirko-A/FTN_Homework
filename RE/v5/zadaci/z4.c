#include <bcm2835.h>
#include <stdio.h>
#include <unistd.h>

#define changeHexToInt(hex) ( (((hex)>>4) * 10) + ((hex) % 16) )

// adrese registara (5, 6, 8 za DAN, MES, GOD)
#define SEK 0x02
#define MIN 0x03
#define SAT 0x04

typedef enum
{
	INIT = 0x00,
	DISPLAY,
	ENTER_TIME,
	STOP
} FsmState;

typedef enum
{
	SEC = 0u,
	MIN = 1u,
	HOUR = 2u,
	DAY = 3u,
	MONTH = 4u,
	YEAR = 5u
} TimeSlot;

TimeSlot time_slot = SEC;

FsmState state = INIT;

// // sec,min,sat
const unsigned char MAX_TIME_VALUES[] = {60, 60, 24, 31, 12, 2077};

unsigned char WriteBuf[2] = {0};
unsigned char ReadBuf = {0};

// sec,min,sat
unsigned char g8563_Store[3] = {0x00, 0x59, 0x08};

void P8563_setTime()
{
    WriteBuf[0] = SEK;
    WriteBuf[1] = g8563_Store[SEC];
    bcm2835_i2c_write(WriteBuf, 2);
    WriteBuf[0] = MIN;
    WriteBuf[1] = g8563_Store[MIN];
    bcm2835_i2c_write(WriteBuf, 2);
    
    WriteBuf[0] = SAT;
    WriteBuf[1] = g8563_Store[HOUR];
    bcm2835_i2c_write(WriteBuf, 2);
}

void P8563_init()
{    
    P8563_setTime();
    //printf("Postavi početno tekuće vreme\n");
    
    //inicijalizacija RTC-a
    WriteBuf[0] = 0x0;
    WriteBuf[1] = 0x00; // normalni rezim rada
    bcm2835_i2c_write(WriteBuf, 2);
}

void P8563_Readtime()
{
    unsigned char time[7] = {0};
    WriteBuf[0] = SEK;
    bcm2835_i2c_write_read_rs(WriteBuf, 1, time, 7);
    
    g8563_Store[0] = time[0] & 0x7f;
    g8563_Store[1] = time[1] & 0x7f;
    g8563_Store[2] = time[2] & 0x3f;
    
    g8563_Store[0] = changeHexToInt(g8563_Store[0]);
    g8563_Store[1] = changeHexToInt(g8563_Store[1]);
    g8563_Store[2] = changeHexToInt(g8563_Store[2]);
}

void updateTime(uint8_t taster)
{
	if (taster == TASTER_DOLE)
	{
		if (g8563_Store[time_slot] == 0u)
		{
			g8563_Store[time_slot] = MAX_TIME_VALUES[time_slot];
		}
		else
		{
			g8563_Store[time_slot]--;
		}
	}
	else if (taster == TASTER_GORE)
	{
		if (g8563_Store[time_slot] == MAX_TIME_VALUES[time_slot])
		{
			g8563_Store[time_slot] = 0u;
		}
		else
		{
			g8563_Store[time_slot]++;
		}
	}
}

int main(int argc, char **argv)
{
	while(1)
    {
	    switch (state)
	    {
	    	case INIT:
	    	{
	    		if (!bcm2835_init()) return 1;
        
                bcm2835_i2c_begin();
	    
                // adresa PCF8563 na I2C magistrali
                bcm2835_i2c_setSlaveAddress(0x51);
                bcm2835_i2c_set_baudrate(10000);
	            
                P8563_init();
	    		
	    		state = DISPLAY;
	    	} 
	    	break;
	    	case DISPLAY:
	    	{
                P8563_Readtime();
                printf("Sati:%d Minuti:%d Sekunde:%d\n", g8563_Store[HOUR], g8563_Store[MIN], g8563_Store[SEC]); // TODO: CHANGE TO LCD
                bcm2835_delay(5000);
	    		
	    		if (digitalRead(TASTER_UNOS) == 1)
	    		{
	    			state = ENTER_TIME;
	    		}
	    	}
	    	break;
	    	case ENTER_TIME:
	    	{				
                printf("Sati:%d Minuti:%d Sekunde:%d\n", g8563_Store[HOUR], g8563_Store[MIN], g8563_Store[SEC]); // TODO: CHANGE TO LCD
                bcm2835_delay(5000);
				
	    		if (digitalRead(TASTER_GORE) == 1)
				{
					updateTime(TASTER_GORE);
				}
				else if (digitalRead(TASTER_DOLE) == 1)
				{
					updateTime(TASTER_DOLE);
				}
				else if (digitalRead(TASTER_UNOS) == 1)
				{
					if (time_slot == YEAR)
					{
						time_slot = SEC;
					}
					else
					{
						time_slot++;
					}
				}
				else if (digitalRead(TASTER_OK) == 1)
				{
					// TODO: SACUVATI VREME
					state = DISPLAY;
				}
	    	}
	    	break;
	    	case STOP:
	    	{
                bcm2835_i2c_end();
                bcm2835_close();
                
                return 0;
	    	}
	    	break;
	    	default:
	    	{
	            state = STOP;
	    	}
	    	break;
	    }
    }
}