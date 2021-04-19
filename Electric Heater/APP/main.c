#include"Main.h"
#include "SW.h"
#include"tempset.h"
#include"Timer.h"
#include "SSD.h"
#include "onoff.h"
#include"display.h"
#include "lm35.h"
#include "heatercooler.h"
#include "led.h"
//#include"eepromint.h"
#include "eepromi2c.h"




tWord __at(0x2007) CONFIG = _HS_OSC & _WDT_OFF & _PWRTE_OFF & _BODEN_OFF & _LVP_OFF & _CPD_OFF & _WRT_OFF & _DEBUG_OFF & _CP_OFF;
tByte flag = 0;

int main()
{
unsigned int temp=0;
e2pext_init();
SW_Init();
heaterstate_init(off);
tempset_init(start,60);
display_init();
lm35_init(GPIO_PIN_2);
heater_init(heateroff);
cooler_init(cooleroff);
led_init(ledoff);
TMR_Init();
TMR_Start();

while(1)
{

}

return 0;
}



