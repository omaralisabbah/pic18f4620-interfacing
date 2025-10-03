
#include "ecu_led.h"

/**
 * @brief Initialize the assigned pin to be OUTPUT and turn the led OFF or ON.
 * @param led : pointer to the led module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
STD_RETURN_TYPE LED_INTIALIZE(const LED_T *led){
    STD_RETURN_TYPE RET = E_OK;
    if(NULL == led){
        RET = E_NOT_OK;
    }
    else{
        PIN_CONFIG_T pin_obj = { .PORT = led->PORT_NAME, .PIN = led->PIN, 
                                 .DIRECTION = GPIO_DIRECTION_OUTPUT,.LOGIC = led->LED_STATUS };
        PIN_INITIALIZE(&pin_obj);
    }
    return RET;
}

/**
 * @brief Turn the led on
 * @param led : pointer to the led module configurations
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
STD_RETURN_TYPE LED_TURN_ON(const LED_T *led){
    STD_RETURN_TYPE RET = E_OK;
     if(NULL == led){
         RET = E_NOT_OK;
     }
     else{
         PIN_CONFIG_T pin_obj = { .PORT = led->PORT_NAME, .PIN = led->PIN, 
                                  .DIRECTION = GPIO_DIRECTION_OUTPUT,.LOGIC = led->LED_STATUS };
         GPIO_PIN_WRITE_LOGIC(&pin_obj, GPIO_HIGH);
     }
    return RET;
}

/**
 * @brief Turn the led off
 * @param led : pointer to the led module configurations
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
STD_RETURN_TYPE LED_TURN_OFF(const LED_T *led){
    STD_RETURN_TYPE RET = E_OK;
     if(NULL == led){
         RET = E_NOT_OK;
     }
     else{
         PIN_CONFIG_T pin_obj = { .PORT = led->PORT_NAME, .PIN = led->PIN, 
                                  .DIRECTION = GPIO_DIRECTION_OUTPUT,.LOGIC = led->LED_STATUS };
         GPIO_PIN_WRITE_LOGIC(&pin_obj, GPIO_LOW);
     }
    return RET;
}

/**
 * @brief Toggle the led
 * @param led : pointer to the led module configurations
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
STD_RETURN_TYPE LED_TURN_TOGGLE(const LED_T *led){
    STD_RETURN_TYPE RET = E_OK;
     if(NULL == led){
         RET = E_NOT_OK;
     }
     else{
         PIN_CONFIG_T pin_obj = { .PORT = led->PORT_NAME, .PIN = led->PIN, 
                                  .DIRECTION = GPIO_DIRECTION_OUTPUT,.LOGIC = led->LED_STATUS };
         GPIO_PIN_TOGGLE_LOGIC(&pin_obj);
     }
    return RET;
}
