#include "display.h"
#include "SSD.h"
#include "tempset.h"
#include "Timer.h"

#define taskperiod (20)
#define blinkperiod (1000)

static void display_blink(tWord temp);

void display_init(void)
{
SSD_Init(SSD_UNITS);
SSD_Init(SSD_TENS);

SSD_SetValue(SSD_UNITS,SSD_0);
SSD_SetValue(SSD_TENS,SSD_0);
}


void display_update(void)
{
static tWord periodcount=0;
static tWord blinkcnt=0;
tWord temprature=0;

periodcount+=TMR_TICK_MS;

if(periodcount!=taskperiod)
{
    return ;
}
periodcount=0;

temprature=tempset_gettemp();
blinkcnt+=TMR_TICK_MS;

if(blinkcnt==blinkperiod)
{
switch(tempset_getstate())
{
case start:
SSD_SetValue(SSD_UNITS,0);
SSD_SetValue(SSD_TENS,0);
blinkcnt=0;
break;

case setting:
blinkcnt=0;
display_blink(temprature);
break;

case isset:
SSD_SetValue(SSD_UNITS,temprature%10);
SSD_SetValue(SSD_TENS,temprature/10);
    break;

case working:
blinkcnt=0;
break;

default:
break;
}
}

}

static void display_blink(tWord temp)
{

    if (SSD_GetValue(SSD_UNITS) == SSD_NULL)
    {
        SSD_SetValue(SSD_UNITS, temp%10);
        SSD_SetValue(SSD_TENS, temp/10);
    } else
    {
        SSD_SetValue(SSD_UNITS, SSD_NULL);
        SSD_SetValue(SSD_TENS, SSD_NULL);
    }

}


