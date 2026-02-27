
#ifndef HAL_TIMR1_H
#define	HAL_TIMR1_H

#include "../mcal_std_types.h"
#include "../../mcal_layer/gpio/hal_gpio.h"
#include "../../mcal_layer/interrupt/mcal_internal_interrupt.h"


// Timer1 Clock Source (Timer or Counter)
#define TIMER1_COUNTER_MODE            1
#define TIMER1_TIMER_MODE              0

// Timer1 External Clock Input Synchronization
#define TIMER1_ASYNC_COUNTER_MODE      1
#define TIMER1_SYNC_COUNTER_MODE       0

// Timer1 Oscillator
#define TIMER1_OSCILLATOR_ENABLE       1
#define TIMER1_OSCILLATOR_DISABLE      0

// Timer1 Input Clock Pre-scaler (Macros instead of Enum (as you wish))
#define TIMER1_PRESCALER_DIV_BY_1      0
#define TIMER1_PRESCALER_DIV_BY_2      1
#define TIMER1_PRESCALER_DIV_BY_4      2
#define TIMER1_PRESCALER_DIV_BY_8      3

// 16-Bit Read/Write Mode 
#define TIMER1_RW_REG_8Bit_MODE        0
#define TIMER1_RW_REG_16Bit_MODE       1


// Enable or Disable Timer1 Module
#define TIMER1_MODULE_ENABLE()              (T1CONbits.TMR1ON = 1)
#define TIMER1_MODULE_DISABLE()             (T1CONbits.TMR1ON = 0)

/*
 * TMR1CS: Timer1 Clock Source Select bit
    1 = External clock from pin RC0/T1OSO/T13CKI (on the rising edge) 
    0 = Internal clock (FOSC/4) 
*/
#define TIMER1_TIMER_MODE_ENABLE()          (T1CONbits.TMR1CS = 0)
#define TIMER1_COUNTER_MODE_ENABLE()        (T1CONbits.TMR1CS = 1)

//  Timer1 External Clock Input Synchronization
/*
 * T1SYNC: Timer1 External Clock Input Synchronization Select bit
    When TMR1CS = 1:
        1 = Do not synchronize external clock input 
        0 = Synchronize external clock input
    When TMR1CS = 0:
        This bit is ignored. Timer1 uses the internal clock when TMR1CS = 0.
        TMR1CS: Timer1 Clock Source Select bit
    1 = External clock from pin RC0/T1OSO/T13CKI (on the rising edge) 
    0 = Internal clock (FOSC/4)
*/
#define TIMER1_ASYNC_COUNTER_MODE_ENABLE()  (T1CONbits.T1SYNC = 1)
#define TIMER1_SYNC_COUNTER_MODE_ENABLE()   (T1CONbits.T1SYNC = 0)

// Timer1 Oscillator
/*
 * T1OSCEN: Timer1 Oscillator Enable bit
    1 = Timer1 oscillator is enabled 
    0 = Timer1 oscillator is shut off  
*/
#define TIMER1_OSC_HW_ENABLE()              (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSC_HW_DISABLE()             (T1CONbits.T1OSCEN = 0)

// Timer1 Input Clock Pre-scaler
#define TIMER1_PRESCALER_SELECT(_PRESCALER_) (T1CONbits.T1CKPS = _PRESCALER_)

// Timer1 System Clock Status
/*
 * Page: 127
 * T1RUN: Timer1 System Clock Status bit
    1 = Device clock is derived from Timer1 oscillator
    0 = Device clock is derived from another source 
*/
#define TIMER1_SYSTEM_CLK_STATUS()          (T1CONbits.T1RUN)

// 16-Bit Read/Write Mode
/*
 * RD16: 16-Bit Read/Write Mode Enable bit
    1 = Enables register read/write of TImer1 in one 16-bit operation
    0 = Enables register read/write of Timer1 in two 8-bit operations 
*/
#define TIMER1_RW_REG_8BIT_MODE_ENABLE()    (T1CONbits.RD16 = 0)
#define TIMER1_RW_REG_16BIT_MODE_ENABLE()   (T1CONbits.RD16 = 1)


typedef struct{
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* TMR1_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint16 timer1_preload_value;
    uint8 timer1_prescaler_value : 2; // 0-3
    uint8 timer1_mode : 1;
    uint8 timer1_counter_mode : 1;
    uint8 timer1_osc_cfg : 1;
    uint8 timer1_reg_wr_mode : 1;
    uint8 timer1_reserved : 2;
}timer1_t;


STD_RETURN_TYPE Timer1_Init(const timer1_t *_timer);
STD_RETURN_TYPE Timer1_DeInit(const timer1_t *_timer);
STD_RETURN_TYPE Timer1_Write_Value(const timer1_t *_timer, uint16 _value);
STD_RETURN_TYPE Timer1_Read_Value(const timer1_t *_timer, uint16 *_value);

#endif	/* HAL_TIMR1_H */