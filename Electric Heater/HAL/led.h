#ifndef __LED__H
#define __LED__H

typedef enum
{
    ledoff,
    ledblink,
    ledon
}led;


//***********************
//      prototypes
//***********************

void led_init(led state);
void led_set_state(led state);
led led_get_state(void);
void led_update(void);

//***********************

#endif // __LED__H
