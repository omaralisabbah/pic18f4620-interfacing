
#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

#include "mcal_interrupt_config.h"

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/*
 * ADIE: A/D Converter Interrupt Enable bit 
    1 = Enables the A/D interrupt 
    0 = Disables the A/D interrupt 
*/
#define ADC_InterruptEnable()  (PIE1bits.ADIE = 1)
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
#define ADC_InterruptLowPrioritySet()   (IPR1.ADIP = 0)

#endif
#endif



#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/*
 * TMR0IE: TMR0 Overflow Interrupt Enable bit 
    1 = Enables the TMR0 overflow interrupt 
    0 = Disables the TMR0 overflow interrupt  
*/
#define TIMER0_InterruptEnable() (INTCONbits.TMR0IE = 1)
#define TIMER0_InterruptDisable() (INTCONbits.TMR0IE = 0)

/*
 * TMR0IF: TMR0 Overflow Interrupt Flag bit 
    1 = TMR0 register has overflowed (must be cleared in software) 
    0 = TMR0 register did not overflow 
*/
#define TIMER0_InterruptFlagClear() (INTCONbits.TMR0IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/*
 * TMR0IP: TMR0 Overflow Interrupt Priority bit 
    1 =High priority 
    0 = Low priority  
*/
#define TIMER0_InterruptHighPrioritySet()  (INTCON2.TMR0IP = 1)
#define TIMER0_InterruptLowPrioritySet()   (INTCON2.TMR0IP = 0)

#endif
#endif
    


#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/*
 * TABLE 12-2: REGISTERS ASSOCIATED WITH TIMER1 AS A TIMER/COUNTER
 * Page: 131 
*/
#define TIMER1_InterruptEnable()  (PIE1bits.TMR1IE = 1)
#define TIMER1_InterruptDisable() (PIE1bits.TMR1IE = 0)


#define TIMER1_InterruptFlagClear() (PIR1bits.TMR1IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE


#define TIMER1_InterruptHighPrioritySet()  (IPR1bits.TMR1IP = 1)
#define TIMER1_InterruptLowPrioritySet()   (IPR1bits.TMR1IP = 0)

#endif
#endif



#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/*
 * TABLE 13-1: REGISTERS ASSOCIATED WITH TIMER2 AS A TIMER/COUNTER      
 * Page: 134
*/
#define TIMER2_InterruptEnable()  (PIE1bits.TMR2IE = 1)
#define TIMER2_InterruptDisable() (PIE1bits.TMR2IE = 0)


#define TIMER2_InterruptFlagClear() (PIR1bits.TMR2IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE


#define TIMER2_InterruptHighPrioritySet()  (IPR1bits.TMR2IP = 1)
#define TIMER2_InterruptLowPrioritySet()   (IPR1bits.TMR2IP = 0)

#endif
#endif



#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/*
 * TABLE 14-1: REGISTERS ASSOCIATED WITH TIMER3 AS A TIMER/COUNTER 
*/
#define TIMER3_InterruptEnable()  (PIE2bits.TMR3IE = 1)
#define TIMER3_InterruptDisable() (PIE2bits.TMR3IE = 0)


#define TIMER3_InterruptFlagClear() (PIR2bits.TMR3IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE


#define TIMER3_InterruptHighPrioritySet()  (IPR2bits.TMR3IP = 1)
#define TIMER3_InterruptLowPrioritySet()   (IPR2bits.TMR3IP = 0)

#endif
#endif



#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/*
 * TABLE 15-5: REGISTERS ASSOCIATED WITH PWM AND TIMER2
*/
#define CCP1_InterruptEnable()  (PIE1bits.CCP1IE = 1)
#define CCP1_InterruptDisable() (PIE1bits.CCP1IE = 0)


#define CCP1_InterruptFlagClear() (PIR1bits.CCP1IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE


#define CCP1_InterruptHighPrioritySet()  (IPR1bits.CCP1IP = 1)
#define CCP1_InterruptLowPrioritySet()   (IPR1bits.CCP1IP = 0)

#endif
#endif



#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/*
 * TABLE 15-5: REGISTERS ASSOCIATED WITH PWM AND TIMER2
*/
#define CCP2_InterruptEnable()  (PIE2bits.CCP2IE = 1)
#define CCP2_InterruptDisable() (PIE2bits.CCP2IE = 0)


#define CCP2_InterruptFlagClear() (PIR2bits.CCP2IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE


#define CCP2_InterruptHighPrioritySet()  (IPR2bits.CCP2IP = 1)
#define CCP2_InterruptLowPrioritySet()   (IPR2bits.CCP2IP = 0)

#endif
#endif

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

