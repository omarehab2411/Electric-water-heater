#ifndef __onoff__H
#define __onoff__H


typedef enum
{
    off,
    on
}heaterState;

//*******************************
//        prototypes
//*******************************

void heaterstate_init(heaterState state);
void heaterstate_setstate(heaterState state);
heaterState heaterstate_getstate(void);
void heaterstate_update(void);

//******************************
#endif // __onoff__H
