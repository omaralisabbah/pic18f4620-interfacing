
#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

#include "../mcal_std_types.h"
#include "mcal_interrupt_cfg.h"
#include "../gpio/hal_gpio.h"

#define INTERRUPT_ENABLE         1
#define INTERRUPT_DISABLE        0
#define INTERRUPT_OCCUR          1
#define INTERRUPT_NOT_OCCUR      0

#define INTERRUPT_PRIORITY_ENABLE       1
#define INTERRUPT_PRIORITY_DISABLE      0


/*
 * Datasheet
 * The interrupt priority feature is enabled by setting the
    IPEN bit (RCON<7>). When interrupt priority is enabled, there are two bits which enable interrupts globally.
 * 
 * Setting the GIEH bit (INTCON<7>) enables all interrupts that have the priority bit set (high priority).
 * Setting the GIEL bit (INTCON<6>) enables all interrupts that have the priority bit cleared (low priority).
 */

/*
 * 10.1 INTCON Registers
    The INTCON registers are readable and writable
    registers, which contain various enable, priority and
    flag bits. (page 113)
 */

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

// GIEH (Global Interrupt High Priority)
// Enable High Priority Global Interrupt (1 = Enables all high-priority interrupts )
#define INTERRUPT_GlobalInterruptHighEnable() (INTCONbits.GIEH = 1)
// Disable High Priority Global Interrupt (1 = Disable all high-priority interrupts )
#define INTERRUPT_GlobalInterruptHighDisable() (INTCONbits.GIEH = 0)

// GIEL (Global Interrupt Low Priority)
// Enable Low Priority Global Interrupt (1 = Enables all low-priority peripheral interrupts)
#define INTERRUPT_GlobalInterruptLowEnable() (INTCONbits.GIEL = 1)
// Disable Low Priority Global Interrupt(0 = Disables all low-priority peripheral interrupts)
#define INTERRUPT_GlobalInterruptLowDisable() (INTCONbits.GIEL = 0)

/*
 * 10.5 RCON Register
    The RCON register contains flag bits which are used to
    determine the cause of the last Reset or wake-up from
    Idle or Sleep modes. RCON also contains the IPEN bit
    which enables interrupt priorities. (page 122)
 */


// IPEN: Interrupt Priority Enable
// (1 = Enable priority levels on interrupts)
#define INTERRUPT_PriorityLevelsEnable() (RCONbits.IPEN = 1)
// (0 = Disable priority levels on interrupts)
#define INTERRUPT_PriorityLevelsDisable() (RCONbits.IPEN = 0)

#else

// GIE: Global Interrupt Enable bit
#define INTERRUPT_GlobalInterruptEnable() (INTCONbits.GIE = 1)
// GIE: Global Interrupt Disable bit
#define INTERRUPT_GlobalInterruptDisable() (INTCONbits.GIE = 0)

// PEIE (Peripheral Interrupt)
// (1 = Enables all unmasked peripheral interrupts)
#define INTERRUPT_PeripheralInterruptEnable() (INTCONbits.PEIE = 1)
// (0 = Disables all peripheral interrupts)
#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)

#endif





typedef enum {
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY        
}interrupt_priority_cfg;

#endif	/* MCAL_INTERRUPT_CONFIG_H */

