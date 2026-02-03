
#ifndef MAIN_H
#define	MAIN_H

#include "ecu_layer/led/ecu_led.h"
#include "mcal_layer/interrupt/mcal_external_interrupt.h"
#include "mcal_layer/adc/hal_adc.h"
#include "ecu_layer/lcd/ecu_lcd.h"
#include "ecu_layer/dc_motor/ecu_dc_motor.h"

void APPLICATION_INITIALIZE(void);
#define _XTAL_FREQ 4000000UL

STD_RETURN_TYPE CONVERT_UINT16_TO_STRING(uint8 value, uint8 *str);

#endif	/* MAIN_H */

