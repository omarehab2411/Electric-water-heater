#include "onoff.h"
#include "SW.h"
#include "SSD.h"
#include "Timer.h"
#include "tempset.h"
#include "eepromint.h"
#include "Main.h"
#include "eepromi2c.h"
#include "heatercooler.h"

#define taskperiod (20)

static heaterState heaterstate;

void heaterstate_init(heaterState state)
{
heaterstate_setstate(state);
}

void heaterstate_setstate(heaterState state)
{
heaterstate=state;
}

heaterState heaterstate_getstate(void)
{
return heaterstate;
}

void heaterstate_update(void)
{
static tWord periodcount=0;
 tByte on_state=0;


periodcount+=TMR_TICK_MS;

if(periodcount!=taskperiod)
{
    return;
}

periodcount=0;

switch(heaterstate_getstate())
{
case off:
//on_state=e2prom_r(20);
on_state=e2pext_r(20);
 if(on_state!=0x01)
 {
 tempset_settemp(60);
 }
 else if(on_state==0x01)
 {
 //tByte x=e2prom_r(10);
 tByte x=e2pext_r(10);
 tempset_settemp(x);
 }

if(SW_GetState(SW_ONOFF)==SW_PRE_RELEASED)
{
heaterstate_setstate(on);
}
break;

case on:
//e2prom_w(20,1);
e2pext_w(20,0x01);
if(SW_GetState(SW_ONOFF)==SW_PRE_RELEASED)
{
heaterstate_setstate(off);
cooler_set_state(cooleroff);
heater_set_state(heateroff);
tempset_setstate(start);

}
break;


default:
break;

}

}
