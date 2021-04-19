#ifndef __adc__H
#define __adc__H
#include "Main.h"
//********************************
//        ADC module prototypes
//********************************
void adc_init(void);
tWord adc_convert(tByte channel);
//********************************
#endif // __adc__H
