#include "Main.h"
#include "Timer.h"
#include "SW.h"
#include "tempset.h"
#include "SSD.h"
#include "onoff.h"
#include "display.h"
#include "lm35.h"
#include "heatercooler.h"
#include "led.h"

extern tByte flag;

void TMR_Init(void)
{
	/* Add your code here! */
	TMR_SET_PRESCALER_256;
	TMR_DISABLE_CLOCK;
	/* End of your code!*/
}
void TMR_Start(void)
{
	/* Add your code here! */
	TMR_CLEAR_FLAG;
	TMR_UPDATE_REGISTER(TMR_TICK_MS);
	TMR_ENABLE_INTERRUPT;
	GLOBAL_INTERRUPT_ENABLE;
	TMR_ENABLE_CLOCK;
	/* End of your code!*/
}
tByte TMR_CheckOverFlow(void)
{
	/* Add your code here! */
	return TMR_GET_FLAG;
	/* End of your code!*/
}
void TMR_Stop(void)
{
	/* Add your code here! */
	TMR_DISABLE_CLOCK;
	/* End of your code!*/
}

void TMR_Update(void) __interrupt 0
{
	/* Add your code here! */
    //RC7 = 1 ^ RC7;
	/* Call Tasks */
	//flag = 1;

    /* Reload timer */
	TMR_CLEAR_FLAG;
	TMR_UPDATE_REGISTER(TMR_TICK_MS);

    //RC7 = 1 ^ RC7;
    SSD_Update();
    SW_Update();
    heaterstate_update();
    tempset_update();

    if(tempset_getstate()==working)
    {
    lm35_update();
    heater_update();
    cooler_update();
    led_update();
        }
    display_update();

	/* End of your code!*/

}
