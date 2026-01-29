
#include "ecu_button.h"

/**
 * @brief Initialize the assigned pin to be input
 * @param btn pointer to the button configurations
 * @return status of the function
 *          (E_OK)
 *          (E_NOT_OK)
 */
STD_RETURN_TYPE BUTTON_INITIALIZE(const BUTTON_T *btn) {
    STD_RETURN_TYPE RET = E_OK;
    if(NULL == btn) {
        RET = E_NOT_OK;
    }
    else {
        RET = GPIO_PIN_DIRECTION_INITIALIZE(&(btn->BUTTON_PIN));
    }
    return RET;
}

/**
 * @brief Read the status of the button
 * @param btn pointer to the button configurations
 * @return status of the function
 *          (E_OK)
 *          (E_NOT_OK)
 */
STD_RETURN_TYPE BUTTON_READ_STATE(const BUTTON_T *btn, BUTTON_STATE_T *btn_state) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    LOGIC_T Pin_Logic_status = GPIO_LOW;
    if(NULL == btn || NULL == btn_state) {
        RET = E_NOT_OK;
    }
    else {
        GPIO_PIN_READ_LOGIC(&(btn->BUTTON_PIN), &Pin_Logic_status);
        if(BUTTON_ACTIVE_HIGH == btn->BUTTON_CONNECTION) {
            if(GPIO_HIGH == Pin_Logic_status) {
                *btn_state = BUTTON_PRESSED;
            }
            else {
                *btn_state = BUTTON_RELEASED;
            }
        }
        else if(BUTTON_ACTIVE_LOW == btn->BUTTON_CONNECTION) {
            if(GPIO_HIGH == Pin_Logic_status) {
                *btn_state = BUTTON_RELEASED;
            }
            else {
                *btn_state = BUTTON_PRESSED;
            }
        }
        else {
            /* nothing */
        }
        RET = E_OK;
    }
    return RET;
}