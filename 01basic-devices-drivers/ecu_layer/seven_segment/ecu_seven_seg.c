
#include "ecu_seven_seg.h"


/**
 * 
 * @param _seg
 * @return 
 */
STD_RETURN_TYPE SEVEN_SEGMENT_INITIALIZE(const SEGMENT_T *_seg) {
    STD_RETURN_TYPE RET = E_OK;
    if(NULL == _seg) {
        RET = E_NOT_OK;
    }
    else {
        RET = PIN_INITIALIZE(&(_seg->SEGMENT_PINS[SEGMENT_PIN0]));
        RET = PIN_INITIALIZE(&(_seg->SEGMENT_PINS[SEGMENT_PIN1]));
        RET = PIN_INITIALIZE(&(_seg->SEGMENT_PINS[SEGMENT_PIN2]));
        RET = PIN_INITIALIZE(&(_seg->SEGMENT_PINS[SEGMENT_PIN3]));
    }
    return  RET;
}

/**
 * 
 * @param _seg
 * @param number
 * @return 
 */
STD_RETURN_TYPE SEVEN_SEGMENT_WRITE_NUMBER(const SEGMENT_T *_seg, uint8 number) {
    STD_RETURN_TYPE RET = E_OK;
    if((NULL == _seg) && (number > 9)) {
        RET = E_NOT_OK;
    }
    else {
        RET = GPIO_PIN_WRITE_LOGIC(&(_seg->SEGMENT_PINS[SEGMENT_PIN0]), number & 0x01);
        RET = GPIO_PIN_WRITE_LOGIC(&(_seg->SEGMENT_PINS[SEGMENT_PIN1]), (number >> 1) & 0x01);
        RET = GPIO_PIN_WRITE_LOGIC(&(_seg->SEGMENT_PINS[SEGMENT_PIN2]), (number >> 2) & 0x01);
        RET = GPIO_PIN_WRITE_LOGIC(&(_seg->SEGMENT_PINS[SEGMENT_PIN3]), (number >> 3) & 0x01);
    }
    return  RET;
}