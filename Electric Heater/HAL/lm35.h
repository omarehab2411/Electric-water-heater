#ifndef __LM35__H
#define __LM35__H
#include "Main.h"

//*********************************
//       module prototypes
//**********************************
void lm35_init(tByte sensor_pin);
void lm35_set_currentTemp(void);
tWord lm35_get_currentTemp(void);
void lm35_update(void);
//**********************************

#endif // __LM35__H
