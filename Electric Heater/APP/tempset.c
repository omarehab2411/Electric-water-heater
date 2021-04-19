#include"tempset.h"
#include"SW.h"
#include "Timer.h"
#include "Main.h"
#include"SSD.h"
#include "eepromint.h"
#include "eepromi2c.h"
//***********************************
//         private constants
//***********************************
#define maxtemp (75)
#define mintemp (35)
#define taskperiod (20)
#define notpressedperiod (5000)
#define e2promaddress (0x0020)
//***********************************

//**********************************************
//     Private structure to hold state and temp
//**********************************************
typedef struct
{
    setstate  currentstate;
    tWord     currenttemprature;
}tstate;

static tstate tempstate;
//************************************************


void tempset_init(setstate state,tWord temprature)
{

tempset_setstate(state);

}

void tempset_setstate(setstate state)
{
tempstate.currentstate=state;
}

void tempset_settemp(tWord temprature)
{
tempstate.currenttemprature=temprature;
}

setstate tempset_getstate(void)
{
return tempstate.currentstate;
}

tWord tempset_gettemp(void)
{
return tempstate.currenttemprature;
}

void tempset_update(void)
{
static tWord taskcount=0;
static tWord notpressedcount=0;
tWord temp=0;
tByte epromtemp=0;

taskcount+=TMR_TICK_MS;
if(taskcount!=taskperiod)
{
    return;
}
taskcount=0;

notpressedcount+=TMR_TICK_MS;

switch(tempset_getstate())
{
case start:
    if(SW_GetState(SW_PLUS)==SW_PRE_RELEASED || SW_GetState(SW_MINUS)==SW_PRE_RELEASED)
    {
    tempset_setstate(setting);
    notpressedcount=0;
    }
    break;

case setting:
    if(SW_GetState(SW_PLUS)==SW_PRE_RELEASED )
    {
        temp=tempset_gettemp()+5;
        if(temp<=maxtemp)
        {
            tempset_settemp(temp);
        }
        else if(temp>maxtemp)
        {
            temp=maxtemp;
            tempset_settemp(temp);
        }
  notpressedcount=0;
    }

    else if(SW_GetState(SW_MINUS)==SW_PRE_RELEASED)
    {
        temp=tempset_gettemp()-5;
        if(temp>=mintemp)
        {
            tempset_settemp(temp);
        }
        else if(temp<mintemp)
        {
            temp=mintemp;
            tempset_settemp(temp);
        }
        notpressedcount=0;
    }

else if(SW_GetState(SW_PLUS)==SW_RELEASED && SW_GetState(SW_MINUS)==SW_RELEASED)
{
if(notpressedcount>=notpressedperiod)
{
  tempset_setstate(isset);
  notpressedcount=0;

}

 }
break;

case isset:
     notpressedcount=0;
     SSD_SetValue(SSD_UNITS,tempset_gettemp()%10);
     SSD_SetValue(SSD_TENS,tempset_gettemp()/10);
     tempset_setstate(working);
    break;


case working:
epromtemp=tempset_gettemp();
//e2prom_w(10,epromtemp);
e2pext_w(10,epromtemp);
notpressedcount=0;
break;

default:
break;
}


}

