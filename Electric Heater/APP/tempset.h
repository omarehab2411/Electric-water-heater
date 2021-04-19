#ifndef __TEMPSET__H
#define __TEMPSET__H
#include "Main.h"

//****************************************
//      tempset module enum and structures
//***************************************
typedef enum
{
start,
setting,
isset,
working
}setstate;
//*********************************************

//********************************************
//       Tempset module prototypes
//********************************************
void tempset_init(setstate state,tWord temprature);
void tempset_setstate(setstate state);
void tempset_settemp(tWord temprature);
setstate tempset_getstate(void);
tWord tempset_gettemp(void);
void tempset_update(void);
//********************************************

#endif // __TEMPSET__H
