
#ifndef HAL_TIMR0_H
#define	HAL_TIMR0_H


#include "../mcal_std_types.h"
#include "../../mcal_layer/gpio/hal_gpio.h"
#include "../../mcal_layer/interrupt/mcal_internal_interrupt.h"


#define TIMER0_TIMER_MODE                1
#define TIMER0_COUNTER_MODE              0

#define TIMER0_PRESCALER_ENABLE_CFG      1
#define TIMER0_PRESCALER_DISABLE_CFG     0

#define TIMER0_8BIT_REGISTER_MODE        1
#define TIMER0_16BIT_REGISTER_MODE       0
#define TIMER0_COUNTER_RISING_EDGE_CFG   1
#define TIMER0_COUNTER_FALLING_EDGE_CFG  0


/*
 * Page: 123
 * PSA: Timer0 Prescaler Assignment bit 
    1 = TImer0 prescaler is not assigned. Timer0 clock input bypasses prescaler. 
    0 = Timer0 prescaler is assigned. Timer0 clock input comes from prescaler output.
*/
#define TIMER0_PRESCALER_ENABLE()           (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_DISABLE()          (T0CONbits.PSA = 1)

/*
 * T0SE: Timer0 Source Edge Select bit
    1 = Increment on high-to-low transition on T0CKI pin 
    0 = Increment on low-to-high transition on T0CKI pin  
*/
#define TIMER0_RISING_EDGE_ENABLE()         (T0CONbits.T0SE = 0)
#define TIMER0_FALLING_EDGE_ENABLE()        (T0CONbits.T0SE = 1)

/*
 * T0CS: Timer0 Clock Source Select bit
    1 = Transition on T0CKI pin
    0 = Internal instruction cycle clock (CLKO)
*/
#define TIMER0_TIMER_MODE_ENABLE()          (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE_ENABLE()        (T0CONbits.T0CS = 1)

/*
 * T08BIT: Timer0 8-Bit/16-Bit Control bit 
    1 = Timer0 is configured as an 8-bit timer/counter 
    0 = Timer0 is configured as a 16-bit timer/counter
*/
#define TIMER0_8BIT_REGISTER_MODE_ENABLE()  (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_REGISTER_MODE_ENABLE() (T0CONbits.T08BIT = 0)

/*
 * TMR0ON: Timer0 On/Off Control bit 
    1 = Enables Timer0 
    0 = Stops Timer0 
*/
#define TIMER0_MODULE_ENABLE()              (T0CONbits.TMR0ON = 1)
#define TIMER0_MODULE_DISABLE()             (T0CONbits.TMR0ON = 0)



/**
   T0PS2:T0PS0: Timer0 Prescaler Select bits    
   111 = 1:256  Prescale value
   110 = 1:128  Prescale value
   101 = 1:64   Prescale value
   100 = 1:32   Prescale value
   011 = 1:16   Prescale value
   010 = 1:8    Prescale value
   001 = 1:4    Prescale value
   000 = 1:2    Prescale value
*/
typedef enum{
    TIMER0_PRESCALER_DIV_BY_2= 0,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256
}timer0_prescaler_select_t;


typedef struct{
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* TMR0_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    timer0_prescaler_select_t prescaler_value;
    uint16 timer0_preload_value; // Value that timer is going to count
    uint8 prescaler_enable : 1;
    uint8 timer0_counter_edge : 1;
    uint8 timer0_mode : 1;
    uint8 timer0_register_size : 1;
    uint8 timer0_reserved : 4;
}timer0_t;


STD_RETURN_TYPE Timer0_Init(const timer0_t *_timer);
STD_RETURN_TYPE Timer0_DeInit(const timer0_t *_timer);
STD_RETURN_TYPE Timer0_Write_Value(const timer0_t *_timer, uint16 _value);
STD_RETURN_TYPE Timer0_Read_Value(const timer0_t *_timer, uint16 *_value);

#endif	/* HAL_TIMR0_H */
