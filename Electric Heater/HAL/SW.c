#include "Main.h"
#include "Timer.h"
#include "SW.h"
#include "Port.h"

/* SW_Update period */
#define SW_PERIOD_MS   (20)

/* Number of samples per SW */
#define N_SAMPLES      (2)

#define N_SWITCHES      (3)

/* SW voltage level */
#define SW_PRESSED_LEVEL        (0)
#define SW_RELEASED_LEVEL       (1)



/* SW info: samples, state */
typedef struct
{
    tByte sw_samples[N_SAMPLES];
    tSW_State sw_state;
}tSW_Info;

/* Switches info */
static tSW_Info SWs_Info[N_SWITCHES];

void SW_Init(void)
{
    tByte index = 0;

    /* Add your code here! */
    /* Initialize switches as inputs */
    GPIO_InitPortPin(SW_PLUS_PORT_CR, SW_PLUS_PIN,   GPIO_IN);
    GPIO_InitPortPin(SW_MINUS_PORT_CR, SW_MINUS_PIN, GPIO_IN);
    GPIO_InitPortPin(SW_ONOFF_PORT_CR, SW_ONOFF_PIN, GPIO_IN);

    /* Initialize switches info */
    for (index = SW_PLUS; index < N_SWITCHES; index++)
    {
        /* Initialize switch samples */
        SWs_Info[index].sw_samples[0] = SW_RELEASED_LEVEL;
        SWs_Info[index].sw_samples[1] = SW_RELEASED_LEVEL;

        /* Initialize sw state */
        SWs_Info[index].sw_state = SW_RELEASED;

    }
    /* End of your code!*/
}


tSW_State SW_GetState(tSW sw)
{
    /* Add your code here! */
    /* return sw state */
    return SWs_Info[sw].sw_state;
    /* End of your code!*/
}


void SW_Update(void)
{
    static tWord SW_counter = 0;
    tByte index = 0;

    /* Check if it is time for the SW_Update to run */
    SW_counter += TMR_TICK_MS;


    if (SW_counter != SW_PERIOD_MS){
        return;
    }

    SW_counter = 0;

    /* Update switches states */
    for (index = SW_PLUS; index < N_SWITCHES; index++)
    {
        /* Add your code here! */
        /* Update switch samples */
        SWs_Info[index].sw_samples[0] = SWs_Info[index].sw_samples[1];

        if (index == SW_PLUS)
        {
            SWs_Info[index].sw_samples[1] = GPIO_ReadPortPin(SW_PLUS_PORT_DR, SW_PLUS_PIN);
        } else if (index == SW_MINUS)
        {
            SWs_Info[index].sw_samples[1] = GPIO_ReadPortPin(SW_MINUS_PORT_DR, SW_MINUS_PIN);
        } else if (index == SW_ONOFF)
        {
            SWs_Info[index].sw_samples[1] = GPIO_ReadPortPin(SW_ONOFF_PORT_DR,SW_ONOFF_PIN);
        } else
        {
            /* Do nothing should not be here !! */
        }
        /* End of your code!*/

        /* Update switch state */
        /* Add your code here! */
        switch(SWs_Info[index].sw_state)
        {

            case SW_RELEASED:
                /* Go to pre-pressed state if needed */
                if ((SWs_Info[index].sw_samples[0] == SW_PRESSED_LEVEL) &&
                    (SWs_Info[index].sw_samples[1] == SW_PRESSED_LEVEL))
                {
                    SWs_Info[index].sw_state = SW_PRE_PRESSED;
                } else
                {
                    /* Do nothing */
                }
                break;
            case SW_PRE_PRESSED:
                /* Go to pressed state if needed  */
                if (SWs_Info[index].sw_samples[1] == SW_PRESSED_LEVEL)
                {
                    SWs_Info[index].sw_state = SW_PRESSED;
                } else
                {
                    /* Do nothing */
                }
                break;
            case SW_PRESSED:
                /* Go to pre-released state if needed */
                if ((SWs_Info[index].sw_samples[0] == SW_RELEASED_LEVEL) &&
                    (SWs_Info[index].sw_samples[1] == SW_RELEASED_LEVEL))
                {
                    SWs_Info[index].sw_state = SW_PRE_RELEASED;
                }
                else
                {
                    /* Do nothing */
                }
                break;
            case SW_PRE_RELEASED:
                /* Go to released state if needed */
                if (SWs_Info[index].sw_samples[1] == SW_RELEASED_LEVEL)
                {
                    SWs_Info[index].sw_state = SW_RELEASED;
                } else
                {
                    /* Do nothing */
                }
                break;
            /* Should not be here */
            default:
                break;
        }
        /* End of your code!*/
    }

}
