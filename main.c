/*
 * File:   main.c
 * Author: omaralisabbah
 * 
 * Created on September 1, 2025, 9:47 PM
 */


#include <xc.h>
#include "main.h"

STD_RETURN_TYPE RET = E_NOT_OK;

// Creating Software Interface with (Bad Level of abstraction)
#define DEFINE_HWREG8 (_x)     (*((volatile uint8 *)(_x)))
#define DEFINE_LATC     (HWREG8(0xF8B))
#define DEFINE_TRISC    (HWREG8(0xF94))


// [1] Access LATC Register Using Union and Struct -----------------------------
typedef union {
    struct {
        unsigned LATC_BIN_0 : 1;
        unsigned LATC_BIN_1 : 1;
        unsigned LATC_BIN_2 : 1;
        unsigned LATC_BIN_3 : 1;
        unsigned LATC_BIN_4 : 1;    
        unsigned LATC_BIN_5 : 1;
        unsigned LATC_BIN_6 : 1;
        unsigned LATC_BIN_7 : 1;
    };
    uint8 LATC_REG;
}LATC_OBJ;

// [1.1] Location
#define  LATC_REG_ADDRESS ((volatile LATC_OBJ *)0xF8B) // Bit Field (Address)
// [1.2] Dereferencing Location
#define  D_LATC_REG_ADDRESS (*(volatile LATC_OBJ *)0xF8B) // Bit Field (Access Location)



// [2] Access Set of bits of register (SSPCON1)---------------------------------
typedef union{
    struct {
        unsigned SSPM_BITS : 4;
        unsigned CKP_BIT   : 1;
        unsigned SSPEN_BIT : 1;
        unsigned SSPOV_BIT : 1;
        unsigned WCOL_BIT  : 1;
    };
    uint8 SSPCON1_REG;
}SSPCON1_OBJ;

// [2.1]
#define  SSPCON1_REG_ADDRESS ((volatile SSPCON1_OBJ *)0xFC6)
// [2.2]
#define  D_SSPCON1_REG_ADDRESS (*(volatile SSPCON1_OBJ *)0xFC6)

// Enumeration to describe set of values related to each other
typedef enum {
    SPI_MASTER_MODE_FOSC_DIV_4, /* SPI MASTER MODE, CLOCK = FOSC/4 */
    SPI_MASTER_MODE_FOSC_DIV_16,
    SPI_MASTER_MODE_FOSC_DIV_64,
    SPI_MASTER_MODE_FOSC_DIV_TMR2,
    SPI_SLAVE_MODE_SS_ENABLED,
    SPI_SLAVE_MODE_SS_DISABLED
}SSPMX_OBJ;


// Defining Pins
PIN_CONFIG_T led_one = {
    .PORT = PORTC_INDEX,
    .PIN = PIN2,
    .DIRECTION = GPIO_DIRECTION_OUTPUT,
    .LOGIC = GPIO_LOW
};


PIN_CONFIG_T led_two = {
    .PORT = PORTC_INDEX,
    .PIN = PIN3,
    .DIRECTION = GPIO_DIRECTION_OUTPUT,
    .LOGIC = GPIO_LOW
};

PIN_CONFIG_T led_three = {
    .PORT = PORTC_INDEX,
    .PIN = PIN4,
    .DIRECTION = GPIO_DIRECTION_OUTPUT,
    .LOGIC = GPIO_LOW
};


DIRECTION_T led_one_st;
uint8 portc_direction_status, portc_logic_status;

// -----------------------------------------------------------------------------

LED_T led_on_pin0 = {.PORT_NAME = PORTC_INDEX, .PIN = PIN0, .LED_STATUS = GPIO_LOW};
LED_T led_on_pin1 = {.PORT_NAME = PORTC_INDEX, .PIN = PIN1, .LED_STATUS = GPIO_LOW};
LED_T led_on_pin2 = {.PORT_NAME = PORTC_INDEX, .PIN = PIN2, .LED_STATUS = GPIO_LOW};
LED_T led_on_pin3 = {.PORT_NAME = PORTC_INDEX, .PIN = PIN3, .LED_STATUS = GPIO_LOW};
LED_T led_on_pin4 = {.PORT_NAME = PORTC_INDEX, .PIN = PIN4, .LED_STATUS = GPIO_LOW};
LED_T led_on_pin5 = {.PORT_NAME = PORTC_INDEX, .PIN = PIN5, .LED_STATUS = GPIO_LOW};

void main(void) {
        
    // [1]----------------------------------------------------------------------
    /*
    DEFINE_TRISC = 0x00; // 0000 0000
    
    LATC_REG_ADDRESS->LATC_REG = 0x55;
    LATC_REG_ADDRESS->LATC_BIN_0 = 1;
    
    D_LATC_REG_ADDRESS.LATC_REG = 0xAA; // 8 Bit Access
    __delay_ms(2000);
    D_LATC_REG_ADDRESS.LATC_BIN_7 = 1; // Bit 7 Access
    */
        
    // [2]----------------------------------------------------------------------
    // SSPCON1_REG_ADDRESS->SSPM_BITS = 4; // 0100 = Slave mode clock = SCK pin, SS pin control enabled
    
    // [3]----------------------------------------------------------------------
    
    while(1) {
        APPLICATION_INITIALIZE();
        LED_TURN_ON(&led_on_pin0); LED_TURN_ON(&led_on_pin1); LED_TURN_ON(&led_on_pin2);
        LED_TURN_ON(&led_on_pin3); LED_TURN_ON(&led_on_pin4); LED_TURN_ON(&led_on_pin5);
        __delay_ms(500);
        LED_TURN_OFF(&led_on_pin0); LED_TURN_OFF(&led_on_pin1); LED_TURN_OFF(&led_on_pin2);
        LED_TURN_OFF(&led_on_pin3); LED_TURN_OFF(&led_on_pin4); LED_TURN_OFF(&led_on_pin5);
        __delay_ms(500);
    }
    
    return;
}

void APPLICATION_INITIALIZE(void) {
    RET = LED_INTIALIZE(&led_on_pin0);
    RET = LED_INTIALIZE(&led_on_pin1);
    RET = LED_INTIALIZE(&led_on_pin2);
    RET = LED_INTIALIZE(&led_on_pin3);
    RET = LED_INTIALIZE(&led_on_pin4);
    RET = LED_INTIALIZE(&led_on_pin5);
}