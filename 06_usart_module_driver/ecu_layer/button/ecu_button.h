
#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H


#include "../../mcal_layer/gpio/hal_gpio.h"
#include "ecu_button_cfg.h"


typedef enum {
    BUTTON_PRESSED,
    BUTTON_RELEASED
}BUTTON_STATE_T;

typedef enum {
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW
}BUTTON_ACTIVE_STATE;

typedef struct {
    PIN_CONFIG_T BUTTON_PIN;
    BUTTON_STATE_T BUTTON_STATE;
    BUTTON_ACTIVE_STATE BUTTON_CONNECTION;
}BUTTON_T;


STD_RETURN_TYPE BUTTON_INITIALIZE(const BUTTON_T *btn);
STD_RETURN_TYPE BUTTON_READ_STATE(const BUTTON_T *btn, BUTTON_STATE_T *btn_state);
#endif	/* ECU_BUTTON_H */

