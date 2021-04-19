#ifndef __SW_H__
#define __SW_H__

//*************************************************
//       Switch module enums and structures
//*************************************************

typedef enum
{
    SW_PLUS,
    SW_MINUS,
    SW_ONOFF
}tSW;

typedef enum
{
    SW_RELEASED,
    SW_PRE_PRESSED,
    SW_PRESSED,
    SW_PRE_RELEASED
}tSW_State;

//*****************************************
//         Sw module prototypes
//*****************************************
extern void SW_Init(void);
extern tSW_State SW_GetState(tSW sw);
extern void SW_Update(void);
//*****************************************
#endif // __SW_H__
