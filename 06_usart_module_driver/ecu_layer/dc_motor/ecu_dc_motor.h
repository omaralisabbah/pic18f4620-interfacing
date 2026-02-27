
#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

#include "ecu_dc_motor_cfg.h"
#include "../../mcal_layer/gpio/hal_gpio.h"

#define DC_MOTOR_ON_STATUS  0x01U
#define DC_MOTOR_OFF_STATUS 0x00U

#define DC_MOTOR_PIN_ONE 0x00U
#define DC_MOTOR_PIN_TWO 0x01U


typedef struct {
    PIN_CONFIG_T DC_MOTOR_PIN[2];
}DC_MOTOR_T;


STD_RETURN_TYPE DC_MOTOR_INITIALIZE(const DC_MOTOR_T *_dc_motor);
STD_RETURN_TYPE DC_MOTOR_MOVE_RIGHT(const DC_MOTOR_T *_dc_motor);
STD_RETURN_TYPE DC_MOTOR_MOVE_LEFT(const DC_MOTOR_T *_dc_motor);
STD_RETURN_TYPE DC_MOTOR_STOP(const DC_MOTOR_T *_dc_motor);

#endif	/* ECU_DC_MOTOR_H */

