
#include "ecu_relay.h"

/**
 * 
 * @param _relay
 * @return 
 */
STD_RETURN_TYPE RELAY_INITIALIZE (const RELAY_T *_relay) {
    STD_RETURN_TYPE RET = E_OK;
    if((NULL == _relay)) {
        RET = E_NOT_OK;
    }
    else {
        PIN_CONFIG_T pin_obj = {.PORT = _relay->RELAY_PORT, .PIN = _relay->RELAY_PIN,
                                .DIRECTION = GPIO_DIRECTION_OUTPUT, .LOGIC = _relay->RELAY_STATUS};
        PIN_INITIALIZE(&pin_obj);
    }
    return  RET;
}

/**
 * 
 * @param _relay
 * @return 
 */
STD_RETURN_TYPE RELAY_TURN_ON(const RELAY_T *_relay) {
    STD_RETURN_TYPE RET = E_OK;
    if((NULL == _relay)) {
        RET = E_NOT_OK;
    }
    else {
        PIN_CONFIG_T pin_obj = {.PORT = _relay->RELAY_PORT, .PIN = _relay->RELAY_PIN,
                                .DIRECTION = GPIO_DIRECTION_OUTPUT, .LOGIC = _relay->RELAY_STATUS};
        GPIO_PIN_WRITE_LOGIC(&pin_obj, GPIO_HIGH);
    }
    return  RET;
}

/**
 * 
 * @param _relay
 * @return 
 */
STD_RETURN_TYPE RELAY_TURN_OFF(const RELAY_T *_relay) {
    STD_RETURN_TYPE RET = E_OK;
    if((NULL == _relay)) {
        RET = E_NOT_OK;
    }
    else {
        PIN_CONFIG_T pin_obj = {.PORT = _relay->RELAY_PORT, .PIN = _relay->RELAY_PIN,
                                .DIRECTION = GPIO_DIRECTION_OUTPUT, .LOGIC = _relay->RELAY_STATUS};
        GPIO_PIN_WRITE_LOGIC(&pin_obj, GPIO_LOW);
    }
    return  RET;
}