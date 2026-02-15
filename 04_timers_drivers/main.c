
#include "main.h"

/*
 * Timer Mode 
*/
volatile uint32 timer3_proteus;

LED_T led1 = {.PORT_NAME = PORTD_INDEX, .PIN = PIN0, .LED_STATUS = GPIO_LOW};

void Timer3_DefaultInterruptHandler(void){
    timer3_proteus++; // Timer3 Existence (Simulation)
    LED_TURN_TOGGLE(&led1);
}

void timer3_timer_init(void){
    timer3_t timer_obj;
    timer_obj.TMR3_InterruptHandler = Timer3_DefaultInterruptHandler;
    timer_obj.priority = INTERRUPT_LOW_PRIORITY;
    timer_obj.timer3_mode = TIMER3_TIMER_MODE;
    timer_obj.timer3_prescaler_value = TIMER3_PRESCALER_DIV_BY_8;
    timer_obj.timer3_preload_value = 15536; //MikroElectronika - Timer Calculator (200 ms & Clock Frequency = 8 MHz)
    timer_obj.timer3_reg_wr_mode = TIMER3_RW_REG_16Bit_MODE;
    Timer3_Init(&timer_obj);
}

void main(void) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    APPLICATION_INITIALIZE();

    timer3_timer_init();
    RET = LED_INTIALIZE(&led1);
    
    while(1) {
        
    }
    
    return;
}

void APPLICATION_INITIALIZE(void) {
    STD_RETURN_TYPE RET = E_NOT_OK;
}
