/* 
 * File:   ecu_led.h
 * Author: omaralisabbah
 * 
 * Created on September 8, 2024, 7:16 AM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section : Includes */
#include "../../mcal_layer/hal_gpio.h"
#include "ecu_led_cfg.h"

/* Section: Macro Declarations */

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */
typedef enum{
    LED_OFF,
    LED_ON
}led_status_t;

typedef struct{
    uint8 PORT_NAME : 4;
    uint8 PIN : 3;
    uint8 LED_STATUS : 1;
}LED_T;

/* Section: Function Declarations */
STD_RETURN_TYPE LED_INTIALIZE(const LED_T *led);
STD_RETURN_TYPE LED_TURN_ON(const LED_T *led);
STD_RETURN_TYPE LED_TURN_OFF(const LED_T *led);
STD_RETURN_TYPE LED_TURN_TOGGLE(const LED_T *led);

#endif	/* ECU_LED_H */

