
#include "ecu_keypad.h"

static const uint8 btn_values[ECU_KEYPAD_ROW][ECU_KEYPAD_COL] = {
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'#', '0', '=', '+'}
};

/**
 * 
 * @param _keypad_obj
 * @return 
 */
STD_RETURN_TYPE KEYPAD_INITIALIZE(const KEYPAD_T *_keypad_obj) {
    STD_RETURN_TYPE RET = E_OK;
    uint8 l_rows = 0, l_columns = 0;
    if(NULL == _keypad_obj) {
        RET = E_NOT_OK;
    }
    else {
        for(l_rows = 0; l_rows < ECU_KEYPAD_ROW; l_rows++) {
            RET = PIN_INITIALIZE(&(_keypad_obj->KEYPAD_ROW_PINS[l_rows]));
            for(l_columns = 0; l_columns < ECU_KEYPAD_COL; l_columns++) {
                RET = GPIO_PIN_DIRECTION_INITIALIZE(&(_keypad_obj->KEYPAD_COL_PINS[l_columns]));
            }
        }
    }
    return  RET;
}

/**
 * 
 * @param _keypad_obj
 * @param value
 * @return 
 */
STD_RETURN_TYPE KEYPAD_GET_VALUE(const KEYPAD_T *_keypad_obj, uint8 *value) {
    STD_RETURN_TYPE RET = E_OK;
    uint8 l_rows = 0, l_columns = 0, l_counter = 0;
    uint8 column_logic = 0;
    if((NULL == _keypad_obj) || (NULL == value)) {
        RET = E_NOT_OK;
    }
    else {
        for(l_rows = 0; l_rows < ECU_KEYPAD_ROW; l_rows++) {
            for(l_counter = 0; l_counter < ECU_KEYPAD_ROW; l_counter++) {
                GPIO_PIN_WRITE_LOGIC(&(_keypad_obj->KEYPAD_ROW_PINS[l_counter]), GPIO_LOW);
            }
            GPIO_PIN_WRITE_LOGIC(&(_keypad_obj->KEYPAD_ROW_PINS[l_rows]), GPIO_HIGH);
            
            for(l_columns = 0; l_columns < ECU_KEYPAD_COL; l_columns++) {
                RET = GPIO_PIN_READ_LOGIC(&(_keypad_obj->KEYPAD_COL_PINS[l_columns]), &column_logic);
                if(GPIO_HIGH == column_logic) {
                    *value = btn_values[l_rows][l_columns];
                }
            }
        }
    }
    return  RET;
}
    