
#ifndef HAL_I2C_H
#define	HAL_I2C_H


#include "../mcal_std_types.h"
#include "../../mcal_layer/gpio/hal_gpio.h"
#include "../../mcal_layer/interrupt/mcal_internal_interrupt.h"

#define _XTAL_FREQ 8000000UL

/*
	SMP: Slew Rate Control bit Page: 171
	In Master or Slave mode:
	1 = Slew rate control disabled for Standard Speed mode (100 kHz) 
	0 = Slew rate control enabled for High-Speed mode (400 kHz)
*/
#define I2C_SLEW_RATE_DISABLE 1
#define I2C_SLEW_RATE_ENABLE  0

/*
	CKE: SMBus Select bit
	In Master or Slave mode:
	1 = Enable SMBus specific inputs
	0 = Disable SMBus specific inputs
*/
#define I2C_SMBus_ENABLE      1
#define I2C_SMBus_DISABLE     0

/*
	D/A: Data/Address bit 
	In Master mode:
		Reserved.
	In Slave mode:
	1 = Indicates that the last byte received or transmitted was data
	0 = Indicates that the last byte received or transmitted was address
*/
#define I2C_LAST_RT_BYTE_DATA	  1
#define I2C_LAST_RT_BYTE_ADDRESS  0

/*
	S: Start bit(1)
	1 = Indicates that a Start bit has been detected last
	0 = Start bit was not detected last
*/
#define I2C_START_BIT_DETECTED     1
#define I2C_START_BIT_NOT_DETECTED 0

/*
	P: Stop bit(1)
1 = Indicates that a Stop bit has been detected last
0 = Stop bit was not detected last
*/
#define I2C_STOP_BIT_DETECTED     1
#define I2C_STOP_BIT_NOT_DETECTED 0

// I2C: Master or Slave Mode
#define I2C_MSSP_MASTER_MODE 1
#define I2C_MSSP_SLAVE_MODE  0

/*
	SSPM3:SSPM0: Master Synchronous Serial Port Mode Select bits(2)
	1111 = I2C Slave mode, 10-bit address with Start and Stop bit interrupts enabled
	1110 = I2C Slave mode, 7-bit address with Start and Stop bit interrupts enabled
	1011 = I2C Firmware Controlled Master mode (Slave Idle)
	1000 = I2C Master mode, clock = FOSC/(4 * (SSPADD + 1))
	0111 = I2C Slave mode, 10-bit address
	0110 = I2C Slave mode, 7-bit address
	Bit combinations not specifically listed here are either reserved or implemented in SPI mode only.
*/
#define I2C_SLAVE_MODE_7BIT_ADDRESS					0x06U
#define I2C_SLAVE_MODE_10BIT_ADDRESS				0x07U
#define I2C_SLAVE_MODE_7BIT_ADDRESS_SS_INT_ENABLE	0x0EU
#define I2C_SLAVE_MODE_10BIT_ADDRESS_SS_INT_ENABLE	0x0FU
#define I2C_MASTER_MODE_DEFINED_CLOCK				0x08U
#define I2C_MASTER_MODE_FIRMWARE_CONTROLLED			0x0BU

// General Call Enable
#define I2C_GENERAL_CALL_ENABLE   1
#define I2C_GENERAL_CALL_DISABLE  0

// Master Mode Receive Enable
#define I2C_MASTER_RECEIVE_ENABLE   1
#define I2C_MASTER_RECEIVE_DISABLE  0

// Acknowledge Status bit (Master Transmit mode only)
/*
	ACKSTAT: Acknowledge Status bit (Master Transmit mode only) Page: 173
	1 = Acknowledge was not received from slave 
	0 = Acknowledge was received from slave
*/
#define I2C_ACK_NOT_RECEIVED_FROM_SLAVE 1
#define I2C_ACK_RECEIVED_FROM_SLAVE     0

// Acknowledge Data bit (Master Receive mode only)
/*
	ACKDT: Acknowledge Data bit (Master Receive mode only)(2)
	1 = Not Acknowledge
	0 = Acknowledge 
*/
#define I2C_MASTER_SEND_ACK  0
#define I2C_MASTER_SEND_NACK 1

/*
	SMP: Slew Rate Control bit
	In Master or Slave mode:
	1 = Slew rate control disabled for Standard Speed mode (100 kHz) 
	0 = Slew rate control enabled for High-Speed mode (400 kHz)
*/
#define I2C_SLEW_RATE_DISABLE_CFG()         (SSPSTATbits.SMP = 1)
#define I2C_SLEW_RATE_ENABLE_CFG()          (SSPSTATbits.SMP = 0)

/*
	CKE: SMBus Select bit
	In Master or Slave mode:
	1 = Enable SMBus specific inputs
	0 = Disable SMBus specific inputs
*/
#define I2C_SMBus_DISABLE_CFG()             (SSPSTATbits.CKE = 0)
#define I2C_SMBus_ENABLE_CFG()              (SSPSTATbits.CKE = 1)

/*
	GCEN: General Call Enable bit (Slave mode only)   
	1 = Enables interrupt when a general call address (0000h) is received in the SSPSR 
	0 = General call address disabled
*/
#define I2C_GENERAL_CALL_DISABLE_CFG()      (SSPCON2bits.GCEN = 0)
#define I2C_GENERAL_CALL_ENABLE_CFG()       (SSPCON2bits.GCEN = 1)

/*
	RCEN: Receive Enable bit (Master mode only)(1)
	1 = Enables Receive mode for I2C
	0 = Receive Idle
*/
#define I2C_MASTER_RECEIVE_DISABLE_CFG()    (SSPCON2bits.RCEN = 0)
#define I2C_MASTER_RECEIVE_ENABLE_CFG()     (SSPCON2bits.RCEN = 1)

/*
	SSPEN: Master Synchronous Serial Port Enable bit(1)
	1 = Enables the serial port and configures the SDA and SCL pins as the serial port pins
	0 = Disables serial port and configures these pins as I/O port pins
*/
#define MSSP_MODULE_ENABLE_CFG()            (SSPCON1bits.SSPEN = 1)
#define MSSP_MODULE_DISABLE_CFG()           (SSPCON1bits.SSPEN = 0)

/*
	CKP: SCK Release Control bit 
	In Slave mode:
	1 = Releases clock 
	0 = Holds clock low (clock stretch), used to ensure data setup time
*/
#define I2C_CLOCK_STRETCH_ENABLE()          (SSPCON1bits.CKP = 0)
#define I2C_CLOCK_STRETCH_DISABLE()         (SSPCON1bits.CKP = 1)


typedef struct{
	uint8 i2c_mode_cfg; // Master Synchronous Serial Port Mode Select
    uint8 i2c_slave_address; // I2C Slave Address
	uint8 i2c_mode : 1;	// I2C : Master or Slave Mode
	uint8 i2c_slew_rate : 1; // Slew Rate Enable/Disable
	uint8 i2c_SMBus_control : 1; // SMBus Enable/Disable */
	uint8 i2c_general_call : 1;	// General Call Enable/Disable
	uint8 i2c_master_rec_mode : 1; 	// Master Receive Mode Enable/Disable
	uint8 i2c_reserved : 3; 
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg mssp_i2c_priority;
    interrupt_priority_cfg mssp_i2c_bc_priority; // Bus Collision
#endif   
}i2c_configs_t;


typedef struct{
	uint32 i2c_clock; // Master Clock Frequency
    i2c_configs_t i2c_cfg; // I2C Configurations
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*I2C_Report_Write_Collision)(void); // Write Collision Indicator
    void (*I2C_DefaultInterruptHandler)(void); // Default Interrupt Handler
    void (*I2C_Report_Receive_Overflow)(void); // Receive Overflow Indicator
#endif    
}mssp_i2c_t;


STD_RETURN_TYPE MSSP_I2C_Init(const mssp_i2c_t *i2c_obj);
STD_RETURN_TYPE MSSP_I2C_DeInit(const mssp_i2c_t *i2c_obj);

STD_RETURN_TYPE MSSP_I2C_Master_Send_Start(const mssp_i2c_t *i2c_obj);
STD_RETURN_TYPE MSSP_I2C_Master_Send_Repeated_Start(const mssp_i2c_t *i2c_obj);
STD_RETURN_TYPE MSSP_I2C_Master_Send_Stop(const mssp_i2c_t *i2c_obj);

STD_RETURN_TYPE MSSP_I2C_Master_Write_Blocking(const mssp_i2c_t *i2c_obj, uint8 i2c_data, uint8 *_ack);
STD_RETURN_TYPE MSSP_I2C_Master_Read_Blocking(const mssp_i2c_t *i2c_obj, uint8 ack, uint8 *i2c_data);

STD_RETURN_TYPE MSSP_I2C_Master_Write_NBlocking(const mssp_i2c_t *i2c_obj, uint8 i2c_data, uint8 *_ack);
STD_RETURN_TYPE MSSP_I2C_Master_Read_NBlocking(const mssp_i2c_t *i2c_obj, uint8 ack, uint8 *i2c_data);

#endif	/* HAL_I2C_H */
