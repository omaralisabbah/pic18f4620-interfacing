
#ifndef HAL_TIMR3_H
#define	HAL_TIMR3_H


#include "../mcal_std_types.h"
#include "../../mcal_layer/gpio/hal_gpio.h"
#include "../../mcal_layer/interrupt/mcal_internal_interrupt.h"


#define TIMER3_COUNTER_MODE            1
#define TIMER3_TIMER_MODE              0

#define TIMER3_ASYNC_COUNTER_MODE      1
#define TIMER3_SYNC_COUNTER_MODE       0

#define TIMER3_PRESCALER_DIV_BY_1      0
#define TIMER3_PRESCALER_DIV_BY_2      1
#define TIMER3_PRESCALER_DIV_BY_4      2
#define TIMER3_PRESCALER_DIV_BY_8      3

#define TIMER3_RW_REG_8Bit_MODE        0
#define TIMER3_RW_REG_16Bit_MODE       1


#define TIMER3_MODULE_ENABLE()              (T3CONbits.TMR3ON = 1)
#define TIMER3_MODULE_DISABLE()             (T3CONbits.TMR3ON = 0)

#define TIMER3_TIMER_MODE_ENABLE()          (T3CONbits.TMR3CS = 0)
#define TIMER3_COUNTER_MODE_ENABLE()        (T3CONbits.TMR3CS = 1)

#define TIMER3_ASYNC_COUNTER_MODE_ENABLE()  (T3CONbits.T3SYNC = 1)
#define TIMER3_SYNC_COUNTER_MODE_ENABLE()   (T3CONbits.T3SYNC = 0)

#define TIMER3_PRESCALER_SELECT(_PRESCALER_) (T3CONbits.T3CKPS = _PRESCALER_) // 2 Bits

#define TIMER3_RW_REG_8BIT_MODE_ENABLE()    (T3CONbits.RD16 = 0)
#define TIMER3_RW_REG_16BIT_MODE_ENABLE()   (T3CONbits.RD16 = 1)


typedef struct{
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* TMR3_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint16 timer3_preload_value;
    uint8 timer3_prescaler_value : 2;
    uint8 timer3_mode : 1;
    uint8 timer3_counter_mode : 1;
    uint8 timer3_reg_wr_mode : 1;
    uint8 timer1_reserved : 3;
}timer3_t;


STD_RETURN_TYPE Timer3_Init(const timer3_t *_timer);
STD_RETURN_TYPE Timer3_DeInit(const timer3_t *_timer);
STD_RETURN_TYPE Timer3_Write_Value(const timer3_t *_timer, uint16 _value);
STD_RETURN_TYPE Timer3_Read_Value(const timer3_t *_timer, uint16 *_value);

#endif	/* HAL_TIMR3_H */
