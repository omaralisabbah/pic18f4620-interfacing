
#ifndef ECU_LED_H
#define	ECU_LED_H

#include "../../mcal_layer/gpio/hal_gpio.h"
#include "ecu_led_cfg.h"

typedef enum{
    LED_OFF,
    LED_ON
}led_status_t;

typedef struct{
    uint8 PORT_NAME : 4;
    uint8 PIN : 3;
    uint8 LED_STATUS : 1;
}LED_T;

STD_RETURN_TYPE LED_INTIALIZE(const LED_T *led);
STD_RETURN_TYPE LED_TURN_ON(const LED_T *led);
STD_RETURN_TYPE LED_TURN_OFF(const LED_T *led);
STD_RETURN_TYPE LED_TURN_TOGGLE(const LED_T *led);

#endif	/* ECU_LED_H */

