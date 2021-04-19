#ifndef __PORT_H__
#define __PORT_H__

#include "Main.h"


/* Leds' pins */
#define LED_1_PORT_DR   (GPIO_PORTB_DATA)
#define LED_1_PORT_CR   (GPIO_PORTB_CONTROL)
#define LED_1_PIN       (GPIO_PIN_0)

#define LED_2_PORT_DR   (GPIO_PORTB_DATA)
#define LED_2_PORT_CR   (GPIO_PORTB_CONTROL)
#define LED_2_PIN       (GPIO_PIN_1)

#define LED_3_PORT_DR   (GPIO_PORTB_DATA)
#define LED_3_PORT_CR   (GPIO_PORTB_CONTROL)
#define LED_3_PIN       (GPIO_PIN_2)

#define LED_4_PORT_DR   (GPIO_PORTB_DATA)
#define LED_4_PORT_CR   (GPIO_PORTB_CONTROL)
#define LED_4_PIN       (GPIO_PIN_3)

/* Fill missing code below */
/* Switches */
#define SW_PLUS_PORT_DR     (GPIO_PORTB_DATA)
#define SW_PLUS_PORT_CR     (GPIO_PORTB_CONTROL)
#define SW_PLUS_PIN         (GPIO_PIN_2)

#define SW_MINUS_PORT_DR    (GPIO_PORTB_DATA)
#define SW_MINUS_PORT_CR    (GPIO_PORTB_CONTROL)
#define SW_MINUS_PIN        (GPIO_PIN_1)

#define SW_ONOFF_PORT_DR      (GPIO_PORTB_DATA)
#define SW_ONOFF_PORT_CR      (GPIO_PORTB_CONTROL)
#define SW_ONOFF_PIN          (GPIO_PIN_0)

/* SSD */
#define SSD_DATA_PORT_DR        (GPIO_PORTD_DATA)
#define SSD_DATA_PORT_CR        (GPIO_PORTD_CONTROL)

#define SSD_HOURS_TENS_DR       (GPIO_PORTA_DATA)
#define SSD_HOURS_TENS_CR       (GPIO_PORTA_CONTROL)
#define SSD_HOURS_TENS_PIN      (GPIO_PIN_4)

#define SSD_HOURS_UNITS_DR      (GPIO_PORTA_DATA)
#define SSD_HOURS_UNITS_CR      (GPIO_PORTA_CONTROL)
#define SSD_HOURS_UNITS_PIN     (GPIO_PIN_5)



#endif // __PORT_H__
