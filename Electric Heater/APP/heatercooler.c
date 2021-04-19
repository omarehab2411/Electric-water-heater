#include "heatercooler.h"
#include "Main.h"
#include "lm35.h"
#include "Timer.h"
#include "tempset.h"

#define taskperiod (100)

static heater_state heaterstate;
static cooler_state coolerstate;


void heater_init (heater_state state)
{
heater_set_state(state);
GPIO_InitPortPin(GPIO_PORTC_CONTROL,GPIO_PIN_5,GPIO_OUT);
}

void heater_set_state(heater_state state)
{heaterstate=state;
}

heater_state heater_get_state(void)
{
return heaterstate;
}

void heater_update(void)
{
static tWord taskcounter=0;
taskcounter+=TMR_TICK_MS;

if(taskcounter!=taskperiod)
{
    return ;
}
taskcounter=0;

switch(heater_get_state())
{
case heateroff:

    if(lm35_get_currentTemp()<(tempset_gettemp()-5))
    {
        heater_set_state(heateron);
       GPIO_WritePortPin(GPIO_PORTC_DATA,GPIO_PIN_5,1);
    }
    break;

case heateron:
    if(lm35_get_currentTemp()>(tempset_gettemp()+5))
    {
        heater_set_state(heateroff);
        GPIO_WritePortPin(GPIO_PORTC_DATA,GPIO_PIN_5,0);
    }
    break;

default:
break;

}
}



void cooler_init (cooler_state state)
{
    cooler_set_state(state);
    GPIO_InitPortPin(GPIO_PORTC_CONTROL,GPIO_PIN_2,GPIO_OUT);
}


void cooler_set_state(cooler_state state)
{
coolerstate=state;
}

cooler_state cooler_get_state(void)
{
return coolerstate;
}


void cooler_update()
{
static tWord taskcounter=0;
taskcounter+=TMR_TICK_MS;

if(taskcounter!=taskperiod)
{
    return ;
}
taskcounter=0;

switch(cooler_get_state())
{
case cooleroff:
    if(lm35_get_currentTemp()>tempset_gettemp()+5)
    {
        cooler_set_state(cooleron);
        GPIO_WritePortPin(GPIO_PORTC_DATA,GPIO_PIN_2,1);
    }
    break;

case cooleron:
     if(lm35_get_currentTemp()<tempset_gettemp()-5)
    {
        cooler_set_state(cooleroff);
        GPIO_WritePortPin(GPIO_PORTC_DATA,GPIO_PIN_2,0);
    }
    break;

default:
    break;

}

}














