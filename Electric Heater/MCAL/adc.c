#include "adc.h"
#include "port.h"

void adc_init(void)
{
ADCON1|=0x02;
ADCON0|=0x51;
}

tWord adc_convert(tByte channel)
{
ADCON0|=(1<<2);  //channel 2 which is connected to lm35
while( ADCON0&(1<<2)==1 )
{

}

return (((((unsigned int)ADRESH)<<2)|(ADRESL>>6)));
}
