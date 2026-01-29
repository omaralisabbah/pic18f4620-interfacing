
#ifndef MAIN_H
#define	MAIN_H

#include "ecu_layer/led/ecu_led.h"
#include "ecu_layer/relay/ecu_relay.h"
#include "ecu_layer/dc_motor/ecu_dc_motor.h"
#include "ecu_layer/seven_segment/ecu_seven_seg.h"
#include "ecu_layer/keypad/ecu_keypad.h"
#include "ecu_layer/lcd/ecu_lcd.h"


void APPLICATION_INITIALIZE(void);
#define _XTAL_FREQ 4000000UL

#endif	/* MAIN_H */

