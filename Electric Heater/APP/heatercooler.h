#ifndef __HEATERCOOLER__H
#define __HEATERCOOLER__H

//************************************
//         modules states
//************************************

typedef enum
{
    heateroff,
    heateron
}heater_state;

typedef enum
{
    cooleroff,
    cooleron
}cooler_state;


void heater_init (heater_state state);
void heater_set_state(heater_state state);
heater_state heater_get_state(void);
void heater_update(void);


void cooler_init (cooler_state state);
void cooler_set_state(cooler_state state);
cooler_state cooler_get_state(void);
void cooler_update();



//************************************

#endif // __HEATERCOOLER__H
