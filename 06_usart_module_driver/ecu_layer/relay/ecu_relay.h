
#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

#include "ecu_relay_cfg.h"
#include "../../mcal_layer/gpio/hal_gpio.h"

#define RELAY_ON_STATUS  0x01U
#define RELAY_OFF_STATUS 0x00U


typedef struct {
    uint8 RELAY_PORT : 4;
    uint8 RELAY_PIN : 3;
    uint8 RELAY_STATUS : 1;
}RELAY_T;


STD_RETURN_TYPE RELAY_INITIALIZE (const RELAY_T *_relay);
STD_RETURN_TYPE RELAY_TURN_ON(const RELAY_T *_relay);
STD_RETURN_TYPE RELAY_TURN_OFF(const RELAY_T *_relay);

#endif	/* ECU_RELAY_H */

