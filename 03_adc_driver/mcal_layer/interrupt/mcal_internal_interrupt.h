
#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

#include "mcal_interrupt_config.h"

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/*
 * ADIE: A/D Converter Interrupt Enable bit 
    1 = Enables the A/D interrupt 
    0 = Disables the A/D interrupt 
*/
#define ADC_InterruptEnable() (PIE1bits.ADIE = 1)
#define ADC_InterruptDisable() (PIE1bits.ADIE = 0)

/*
 * ADIF: A/D Converter Interrupt Flag bit 
    1 = An A/D conversion completed (must be cleared in software) 
    0 = The A/D conversion is not complete  
*/
#define ADC_InterruptFlagClear() (PIR1bits.ADIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/*
 * ADIP: A/D Converter Interrupt Priority bit
    1 =High priority 
    0 = Low priority  
*/
#define ADC_InterruptHighPrioritySet()  (IPR1.ADIP = 1)
#define ADC_InterruptLowPrioritySet()  (IPR1.ADIP = 0)

#endif

#endif
    
#endif	/* MCAL_INTERNAL_INTERRUPT_H */

