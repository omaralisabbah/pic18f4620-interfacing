
#ifndef HAL_USART_H
#define	HAL_USART_H

#include "../mcal_std_types.h"
#include "../../mcal_layer/gpio/hal_gpio.h"
#include "../../mcal_layer/interrupt/mcal_internal_interrupt.h"
#include "hal_usart_cfg.h"

#define _XTAL_FREQ 8000000UL

/* Page: 202 */
#define EUSART_MODULE_ENABLE   1
#define EUSART_MODULE_DISABLE  0

/*
 * SYNC: EUSART Mode Select bit 
    1 = Synchronous mode 
    0 = Asynchronous mode 
*/
#define EUSART_SYNCHRONOUS_MODE  		1
#define EUSART_ASYNCHRONOUS_MODE 		0


#define EUSART_ASYNCHRONOUS_HIGH_SPEED  1
#define EUSART_ASYNCHRONOUS_LOW_SPEED  	0

#define EUSART_16BIT_BAUDRATE_GEN  		1
#define EUSART_08BIT_BAUDRATE_GEN  		0

/*
 * TXEN: Transmit Enable bit(1)
    1 = Transmit enabled
    0 = Transmit disabled 
*/
#define EUSART_ASYNCHRONOUS_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_TX_DISABLE  0


#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE  0

/*
 * TX9: 9-Bit Transmit Enable bit
    1 = Selects 9-bit transmission
    0 = Selects 8-bit transmission
 * 
 * (TX9D: 9th Bit of Transmit Data, Can be address/data bit or a parity bit.)
*/
#define EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE  0

/*
 * SPEN: Serial Port Enable bit
    1 = Serial port enabled (configures RX/DT and TX/CK pins as serial port pins)
    0 = Serial port disabled (held in Reset) 
*/
#define EUSART_ASYNCHRONOUS_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_RX_DISABLE  0

/*
 * TRMT: Transmit Shift Register Status bit
    1 = TSR empty 
    0 = TSR full
*/
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE  0

#define EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE  0

#define EUSART_FRAMING_ERROR_DETECTED 1
#define EUSART_FRAMING_ERROR_CLEARED  0

#define EUSART_OVERRUN_ERROR_DETECTED 1
#define EUSART_OVERRUN_ERROR_CLEARED  0

/*
 * TABLE 18-3: BAUD RATES FOR ASYNCHRONOUS MODES (Page: 207) 
*/
typedef enum{
    BAUDRATE_ASYN_8BIT_lOW_SPEED,
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,
    BAUDRATE_ASYN_16BIT_lOW_SPEED,   
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,
    BAUDRATE_SYN_8BIT,
    BAUDRATE_SYN_16BIT
}baudrate_gen_t;


typedef struct{
    interrupt_priority_cfg usart_tx_int_priority;
	uint8 usart_tx_enable : 1;
	uint8 usart_tx_interrupt_enable : 1;
	uint8 usart_tx_9bit_enable : 1;
    uint8 usart_tx_reserved : 5;
}usart_tx_cfg_t;


typedef struct{
    interrupt_priority_cfg usart_rx_int_priority;
	uint8 usart_rx_enable : 1;
	uint8 usart_rx_interrupt_enable : 1;
	uint8 usart_rx_9bit_enable : 1;
    uint8 usart_rx_reserved : 5;
}usart_rx_cfg_t;


typedef union{
	struct{
		uint8 usart_tx_reserved : 6;
		uint8 usart_ferr : 1;
		uint8 usart_oerr : 1;
	};
	uint8 status;
}usart_error_status_t;


typedef struct{
    uint32 baudrate;
    baudrate_gen_t baudrate_gen_gonfig;
    usart_tx_cfg_t usart_tx_cfg;
	usart_rx_cfg_t usart_rx_cfg;
	usart_error_status_t error_status;
	void (*EUSART_TxDefaultInterruptHandler)(void);
    void (*EUSART_RxDefaultInterruptHandler)(void);
    void (*EUSART_FramingErrorHandler)(void);
    void (*EUSART_OverrunErrorHandler)(void);
}usart_t;


STD_RETURN_TYPE EUSART_ASYNC_Init(const usart_t *_eusart);
STD_RETURN_TYPE EUSART_ASYNC_DeInit(const usart_t *_eusart);


STD_RETURN_TYPE EUSART_ASYNC_ReadByteBlocking(uint8 *_data);
STD_RETURN_TYPE EUSART_ASYNC_ReadByteNonBlocking(uint8 *_data);
STD_RETURN_TYPE EUSART_ASYNC_RX_Restart(void);


STD_RETURN_TYPE EUSART_ASYNC_WriteByteBlocking(uint8 _data);
STD_RETURN_TYPE EUSART_ASYNC_WriteStringBlocking(uint8 *_data, uint16 str_len);
STD_RETURN_TYPE EUSART_ASYNC_WriteByteNonBlocking(uint8 _data);
STD_RETURN_TYPE EUSART_ASYNC_WriteStringNonBlocking(uint8 *_data, uint16 str_len);

#endif	/* HAL_USART_H */
