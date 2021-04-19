#include "lm35.h"
#include "adc.h"
#include "Main.h"
#include "port.h"
#include "Timer.h"
#include "SSD.h"

#define samples (10)
#define taskperiod (100)

static void lm35_set_temp(tWord temp,tByte index);
static tWord lm35_get_temp (tByte index);

static tWord temprature[samples];
static tWord currenttemp;

void lm35_init(tByte sensor_pin)
{
GPIO_InitPortPin(GPIO_PORTA_CONTROL,sensor_pin,GPIO_IN);
adc_init();
}

static void lm35_set_temp(tWord temp,tByte index)
{
temprature[index]=temp;
}

static tWord lm35_get_temp (tByte index)
{
return temprature[index];
}


void lm35_set_currentTemp(void)
{
    tWord temp=0;
    int i=0;
for (i;i<samples;i++)
{
    temp+=temprature[i];
}
temp/=10;
currenttemp=temp;
}

tWord lm35_get_currentTemp(void)
{
    return currenttemp;
}


void lm35_update(void)
{
static tWord taskcounter=0;
static tByte samplescounter=0;
tWord temp=0;
int x=0;
taskcounter+=TMR_TICK_MS;

if(taskcounter!=taskperiod)
{
    return ;
}
taskcounter=0;

temp=adc_convert(2)/2;
lm35_set_temp(temp,samplescounter);
samplescounter++;

if(samplescounter==10)
{
samplescounter=0;
lm35_set_currentTemp();
SSD_SetValue(SSD_UNITS,lm35_get_currentTemp()%10);
SSD_SetValue(SSD_TENS,lm35_get_currentTemp()/10);
}

}
