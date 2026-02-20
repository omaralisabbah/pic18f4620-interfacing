
#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

#include "mcal_interrupt_config.h"

/*
    For external interrupt events, such as the INTx pins or
    the PORTB input change interrupt, the interrupt latency
    will be three to four instruction cycles. The exact
    latency is the same for one or two-cycle instructions.
    Individual interrupt flag bits are set, regardless of the
    status of their corresponding enable bit or the GIE bit.
 */
/*
    INT0IE: INT0 External Interrupt Enable bit 
    1 = Enables the INT0 external interrupt 
    0 = Disables the INT0 external interrupt 

    INT0IF: INT0 External Interrupt Flag bit 
    1 = The INT0 external interrupt occurred (must be cleared in software) 
    0 = The INT0 external interrupt did not occur
*/
/*
   INTEDG0: External Interrupt 0 Edge Select bit 
   1 = Interrupt on rising edge 
   0 = Interrupt on falling edge  
*/

#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
// 1 = Enables the INT0 external interrupt 
#define EXT_INT0_InterruptEnable()  (INTCONbits.INT0IE = 1)
// 0 = Disables the INT0 external interrupt
#define EXT_INT0_InterruptDisable() (INTCONbits.INT0IE = 0)
// 1 = The INT0 external interrupt occurred (must be cleared in software)
#define EXT_INT0_InterruptFlagClear()  (INTCONbits.INT0IF = 0)

// 1 = Interrupt on rising edge 
#define EXT_INT0_RisingEdgeSet()  (INTCON2bits.INTEDG0 = 1)
// 0 = Interrupt on falling edge
#define EXT_INT0_FallingEdgeSet() (INTCON2bits.INTEDG0 = 0)


// 1 = Enables the INT0 external interrupt 
#define EXT_INT1_InterruptEnable()  (INTCON3bits.INT1IE = 1)
// 0 = Disables the INT0 external interrupt
#define EXT_INT1_InterruptDisable() (INTCON3bits.INT1IE = 0)
// 1 = The INT0 external interrupt occurred (must be cleared in software)
#define EXT_INT1_InterruptFlagClear()  (INTCON3bits.INT1IF = 0)

// 1 = Interrupt on rising edge 
#define EXT_INT1_RisingEdgeSet()  (INTCON2bits.INTEDG1 = 1)
// 0 = Interrupt on falling edge
#define EXT_INT1_FallingEdgeSet() (INTCON2bits.INTEDG1 = 0)


// 1 = Enables the INT0 external interrupt 
#define EXT_INT2_InterruptEnable()  (INTCON3bits.INT2IE = 1)
// 0 = Disables the INT0 external interrupt
#define EXT_INT2_InterruptDisable() (INTCON3bits.INT2IE = 0)
// 1 = The INT0 external interrupt occurred (must be cleared in software)
#define EXT_INT2_InterruptFlagClear()  (INTCON3bits.INT2IF = 0)

// 1 = Interrupt on rising edge 
#define EXT_INT2_RisingEdgeSet()  (INTCON2bits.INTEDG2 = 1)
// 0 = Interrupt on falling edge
#define EXT_INT2_FallingEdgeSet() (INTCON2bits.INTEDG2 = 0)


#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/*
    INT2IP: INT2 External Interrupt Priority bit
    1 =High priority 
    0 = Low priority
 * 
    INT1IP: INT1 External Interrupt Priority bit
    1 =High priority 
    0 = Low priority
 */

// 1 = High priority (INT1 External Interrupt)
#define EXT_INT1_InterruptHighPrioritySet()  (INTCON3bits.INT1IP = 1)
// 0 = Low priority (INT1 External Interrupt)
#define EXT_INT1_InterruptLowPrioritySet()  (INTCON3bits.INT1IP = 0)
// 1 = High priority (INT2 External Interrupt)
#define EXT_INT2_InterruptHighPrioritySet()  (INTCON3bits.INT2IP = 1)
// 0 = Low priority (INT2 External Interrupt)
#define EXT_INT2_InterruptLowPrioritySet()  (INTCON3bits.INT2IP = 0)

#endif

#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*
 * RBIE: RB Port Change Interrupt Enable bit 
    1 = Enables the RB port change interrupt 
    0 = Disables the RB port change interrupt  
 * 
 * RBIF: RB Port Change Interrupt Flag bit(1)
    1 = At least one of the RB7:RB4 pins changed state (must be cleared in software) 
    0 = None of the RB7:RB4 pins have changed state
*/
// 1 = Enables the RB port change interrupt 
#define EXT_RBx_InterruptEnable() (INTCONbits.RBIE = 1)
// 0 = Disables the RB port change interrupt
#define EXT_RBx_InterruptDisable() (INTCONbits.RBIE = 0)
// 1 = At least one of the RB7:RB4 pins changed state (must be cleared in software) 
#define EXT_RBx_InterruptFlagClear() (INTCONbits.RBIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/*
 * RBIP: RB Port Change Interrupt Priority bit
    1 =High priority 
    0 = Low priority
*/
// 1 =High priority 
#define EXT_RBx_Priority_High() (INTCON2bits.RBIP = 1)
// 0 = Low priority
#define EXT_RBx_Priority_Low() (INTCON2bits.RBIP = 0)
#endif

#endif

#endif


typedef void (* InterruptHandler)(void);

typedef enum {
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RISING_EDGE
}interrupt_INTx_edge;


typedef enum {
    INTERRUPT_EXTERNAL_INT0 = 0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2
}interrupt_INTx_src;


typedef struct {
    void (* EXT_Interrupt_Handler)(void); // Pointer to Function to Call Back
    PIN_CONFIG_T mcu_pin;
    interrupt_INTx_edge edge;
    interrupt_INTx_src source;
    interrupt_priority_cfg priority;
}interrupt_INTx_t;


typedef struct {
    void (* EXT_Interrupt_Handler_High)(void);
    void (* EXT_Interrupt_Handler_Low)(void);
    PIN_CONFIG_T mcu_pin;
    interrupt_priority_cfg priority;
}interrupt_RBx_t;



/**
 * 
 * @param int_obj
 * @return 
 */
STD_RETURN_TYPE Inerrupt_INTx_Init(const interrupt_INTx_t *int_obj);
/**
 * 
 * @param int_obj
 * @return 
 */
STD_RETURN_TYPE Inerrupt_INTx_DeInit(const interrupt_INTx_t *int_obj);
/**
 * 
 * @param int_obj
 * @return 
 */
STD_RETURN_TYPE Interrupt_RBx_Init(const interrupt_RBx_t *int_obj);
/**
 * 
 * @param int_obj
 * @return 
 */
STD_RETURN_TYPE Inerrupt_RBx_DeInit(const interrupt_RBx_t *int_obj);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

