
#ifndef ECU_SEVEN_SEG_H
#define ECU_SEVEN_SEG_H

#include "../../mcal_layer/gpio/hal_gpio.h"
#include "ecu_seven_seg_cfg.h"

#define SEGMENT_PIN0 0
#define SEGMENT_PIN1 1
#define SEGMENT_PIN2 2
#define SEGMENT_PIN3 3

typedef enum {
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE
}SEGMENT_TYPE_T;


typedef struct {
    PIN_CONFIG_T SEGMENT_PINS[4];
    SEGMENT_TYPE_T SEGMENT_TYPE;
}SEGMENT_T;


STD_RETURN_TYPE SEVEN_SEGMENT_INITIALIZE(const SEGMENT_T *_seg);
STD_RETURN_TYPE SEVEN_SEGMENT_WRITE_NUMBER(const SEGMENT_T *_seg, uint8 number);

#endif /* ECU_SEVEN_SEG_H */