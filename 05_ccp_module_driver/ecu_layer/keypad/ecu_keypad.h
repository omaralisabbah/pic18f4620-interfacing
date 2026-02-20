
#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

#include "ecu_keypad_cfg.h"
#include "../../mcal_layer/gpio/hal_gpio.h"

#define ECU_KEYPAD_ROW 4
#define ECU_KEYPAD_COL 4


typedef struct {
    PIN_CONFIG_T KEYPAD_ROW_PINS[ECU_KEYPAD_ROW];
    PIN_CONFIG_T KEYPAD_COL_PINS[ECU_KEYPAD_COL];
}KEYPAD_T;

STD_RETURN_TYPE KEYPAD_INITIALIZE(const KEYPAD_T *_keypad_obj);
STD_RETURN_TYPE KEYPAD_GET_VALUE(const KEYPAD_T *_keypad_obj, uint8 *value);

#endif	/* ECU_KEYPAD_H */

