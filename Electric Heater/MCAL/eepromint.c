#include "eepromint.h"
#include "Main.h"


unsigned char e2prom_r(unsigned char addr)
{
 EEADR= addr;
 RD=1;
 return EEDATA;
}


void e2prom_w(unsigned char addr,unsigned char val)
{
 EEADR= addr;
 EEDATA=val;

 WREN=1;

 EECON2=0x55;
 EECON2=0xAA;

 WR=1;
 while(WR==1);

 WREN=0;

 return;
}


