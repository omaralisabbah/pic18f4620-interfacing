
#include "ecu_dc_motor.h"

/**
 * 
 * @param _dc_motor
 * @return 
 */
STD_RETURN_TYPE DC_MOTOR_INITIALIZE(const DC_MOTOR_T *_dc_motor){
    STD_RETURN_TYPE RET = E_OK;
    if((NULL == _dc_motor)) {
        RET = E_NOT_OK;
    }
    else {        
        PIN_INITIALIZE(&(_dc_motor->DC_MOTOR_PIN[DC_MOTOR_PIN_ONE]));
        PIN_INITIALIZE(&(_dc_motor->DC_MOTOR_PIN[DC_MOTOR_PIN_TWO]));
    }
    return  RET;
}

/**
 * 
 * @param _dc_motor
 * @return 
 */
STD_RETURN_TYPE DC_MOTOR_MOVE_RIGHT(const DC_MOTOR_T *_dc_motor){
    STD_RETURN_TYPE RET = E_OK;
    if((NULL == _dc_motor)) {
        RET = E_NOT_OK;
    }
    else {
        GPIO_PIN_WRITE_LOGIC(&(_dc_motor->DC_MOTOR_PIN[DC_MOTOR_PIN_ONE]), GPIO_HIGH);
        GPIO_PIN_WRITE_LOGIC(&(_dc_motor->DC_MOTOR_PIN[DC_MOTOR_PIN_TWO]), GPIO_LOW);
    }
    return  RET;
}

/**
 * 
 * @param _dc_motor
 * @return 
 */
STD_RETURN_TYPE DC_MOTOR_MOVE_LEFT(const DC_MOTOR_T *_dc_motor) {
    STD_RETURN_TYPE RET = E_OK;
    if((NULL == _dc_motor)) {
        RET = E_NOT_OK;
    }
    else {
        GPIO_PIN_WRITE_LOGIC(&(_dc_motor->DC_MOTOR_PIN[DC_MOTOR_PIN_ONE]), GPIO_LOW);
        GPIO_PIN_WRITE_LOGIC(&(_dc_motor->DC_MOTOR_PIN[DC_MOTOR_PIN_TWO]), GPIO_HIGH);
    }
    return  RET;
}

/**
 * 
 * @param _dc_motor
 * @return 
 */
STD_RETURN_TYPE DC_MOTOR_STOP(const DC_MOTOR_T *_dc_motor) {
    STD_RETURN_TYPE RET = E_OK;
    if((NULL == _dc_motor)) {
        RET = E_NOT_OK;
    }
    else {
        GPIO_PIN_WRITE_LOGIC(&(_dc_motor->DC_MOTOR_PIN[DC_MOTOR_PIN_ONE]), GPIO_LOW);
        GPIO_PIN_WRITE_LOGIC(&(_dc_motor->DC_MOTOR_PIN[DC_MOTOR_PIN_TWO]), GPIO_LOW);
    }
    return  RET;
}