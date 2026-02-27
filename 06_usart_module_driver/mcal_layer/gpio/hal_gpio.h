
#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* SECTION : INCLUDES */
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "hal_gpio_cfg.h"

/* SECTION : MACRO DECLARATIONS */
#define BIT_MASK    (uint8)1
#define PORT_BIN_MAX_NUMBER     8
#define PORT_MAX_NUMBER         5

#define PORTC_MASK              0xFF

#define GPIO_PIN_CONFIGURATIONS     CONFIG_ENABLE
#define GPIO_PORT_CONFIGURATIONS    CONFIG_ENABLE

/* SECTION : MACRO FUNCTION DECLARATIONS */ 
#define HWREG8(_X)      (*((volatile uint8 *)(_x)))

#define SET_BIT(REG, BIT_POSN)      (REG |= (BIT_MASK << BIT_POSN))
#define CLEAR_BIT(REG, BIT_POSN)      (REG &= ~(BIT_MASK << BIT_POSN))
#define TOGGLE_BIT(REG, BIT_POSN)      (REG ^= (BIT_MASK << BIT_POSN))
#define READ_BIT(REG, BIT_POSN)     ((REG >> BIT_POSN) & BIT_MASK)


/* SECTION : DATATYPE DECLARATIONS */
typedef enum {
    GPIO_LOW,
    GPIO_HIGH
}LOGIC_T;


typedef enum {
    GPIO_DIRECTION_OUTPUT = 0,
    GPIO_DIRECTION_INPUT
}DIRECTION_T;


typedef enum {
    PIN0 = 0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7     
}PIN_INDEX_T;


typedef enum {
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,       
    PORTD_INDEX,      
    PORTE_INDEX            
}PORT_INDEX_T;

typedef struct {
    uint8 PORT      : 3; /* @ref PORT_INDEX_T */ 
    uint8 PIN       : 3; /* @ref PIN_INDEX_T */ 
    uint8 DIRECTION : 1; /* @ref DIRECTION_T */ 
    uint8 LOGIC     : 1; /* @ref LOGIC_T */ 
}PIN_CONFIG_T;


/* SECTION : FUNCTION DECLARATIONS */
// Bin configurations interfaces -----------------------------------------------
STD_RETURN_TYPE GPIO_PIN_DIRECTION_INITIALIZE(const PIN_CONFIG_T *_PIN_CONFIG);
STD_RETURN_TYPE GPIO_PIN_DIRECTION_STATUS(const PIN_CONFIG_T *_PIN_CONFIG, DIRECTION_T *DIREC_STATUS);
STD_RETURN_TYPE GPIO_PIN_WRITE_LOGIC(const PIN_CONFIG_T *_PIN_CONFIG, LOGIC_T LOG);
STD_RETURN_TYPE GPIO_PIN_READ_LOGIC(const PIN_CONFIG_T *_PIN_CONFIG, LOGIC_T *LOG);
STD_RETURN_TYPE GPIO_PIN_TOGGLE_LOGIC(const PIN_CONFIG_T *_PIN_CONFIG);
STD_RETURN_TYPE PIN_INITIALIZE(const PIN_CONFIG_T *_PIN_CONFIG);

// Port configurations interfaces ----------------------------------------------
STD_RETURN_TYPE GPIO_PORT_DIRECTION_INITIALIZE(PORT_INDEX_T PORT, uint8 DIREC);
STD_RETURN_TYPE GPIO_PORT_GET_DIRECTION_STATUS(PORT_INDEX_T PORT, uint8 *DIREC_STATUS);
STD_RETURN_TYPE GPIO_PORT_WRITE_LOGIC(PORT_INDEX_T PORT, uint8 LOG);
STD_RETURN_TYPE GPIO_PORT_READ_LOGIC(PORT_INDEX_T PORT, uint8 *LOGIC);
STD_RETURN_TYPE GPIO_PORT_TOGGLE_LOGIC(PORT_INDEX_T PORT);


#endif	/* HAL_GPIO_H */

