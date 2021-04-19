#include "led.h"
#include "Main.h"
#include "Timer.h"
#include "heatercooler.h"

#define taskperiod (100)
#define blinkperiod (1000)

static led ledstate;

void led_init(led state)
{
led_set_state(state);
GPIO_InitPortPin(GPIO_PORTB_CONTROL,GPIO_PIN_4,GPIO_OUT);
}

void led_set_state(led state)
{
    ledstate=state;

}

led led_get_state(void)
{
    return ledstate;
}

void led_update(void)
{
    static tWord taskcounter=0;
    static tWord secondcounter=0;
    static tByte blink=0;
    taskcounter+=TMR_TICK_MS;

    if(taskcounter!=taskperiod)
    {
        return ;
    }
    taskcounter=0;
    secondcounter+=TMR_TICK_MS;

    switch(led_get_state())
    {
    case ledoff:
        secondcounter=0;
        if(heater_get_state()==heateron)
        {
            led_set_state(ledblink);
        }
        else if(cooler_get_state()==cooleron)
        {
            led_set_state(ledon);
        }

        break;


case ledblink:
        if(secondcounter==blinkperiod)
        {
          //toogle led
          blink^=1;
          GPIO_WritePortPin(GPIO_PORTB_DATA,GPIO_PIN_4,blink);
          secondcounter=0;
        }
        if(cooler_get_state()==cooleron)
        {
            led_set_state(ledon);
        }
        break;


    case ledon:
            secondcounter=0;
  GPIO_WritePortPin(GPIO_PORTB_DATA,GPIO_PIN_4,1);
    if(heater_get_state()==heateron)
        {
            led_set_state(ledblink);
        }

        break;


    default:
        break;
    }


}
