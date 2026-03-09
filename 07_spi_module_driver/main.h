
#ifndef MAIN_H
#define	MAIN_H

#include "ecu_layer/led/ecu_led.h"
#include "mcal_layer/interrupt/mcal_external_interrupt.h"
#include "mcal_layer/adc/hal_adc.h"
#include "ecu_layer/lcd/ecu_lcd.h"
#include "ecu_layer/dc_motor/ecu_dc_motor.h"
#include "mcal_layer/timer3/hal_timr3.h"

#include "mcal_layer/ccp/hal_ccp.h"
#include "mcal_layer/usart/hal_usart.h"

void APPLICATION_INITIALIZE(void);
#define _XTAL_FREQ 8000000UL



#endif	/* MAIN_H */

