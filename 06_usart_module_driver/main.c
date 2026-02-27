
#include "main.h"

volatile uint8 rec_uart_data; // Volatile Important
LED_T led1 = {.PORT_NAME = PORTD_INDEX, .PIN = PIN0, .LED_STATUS = GPIO_LOW};

void EUSART_RxDefaultInterruptHandler (void){
    STD_RETURN_TYPE ret = E_NOT_OK;
    EUSART_ASYNC_ReadByteNonBlocking(&rec_uart_data);
    if('z' == rec_uart_data){
        LED_TURN_ON(&led1);
        ret = EUSART_ASYNC_WriteByteBlocking('y');
        __delay_ms(500);
    }
    if('x' == rec_uart_data){
        LED_TURN_OFF(&led1);
        ret = EUSART_ASYNC_WriteByteBlocking('w');
        __delay_ms(500);
    }
}

void usart_module_int_init(void){
    STD_RETURN_TYPE RET = E_NOT_OK;
    usart_t usart_obj;
    usart_obj.baudrate = 9600;
    usart_obj.baudrate_gen_gonfig = BAUDRATE_ASYN_8BIT_lOW_SPEED;   
    usart_obj.usart_tx_cfg.usart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE;
    usart_obj.usart_tx_cfg.usart_tx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE;
    usart_obj.usart_tx_cfg.usart_tx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE;
    usart_obj.usart_rx_cfg.usart_rx_enable = EUSART_ASYNCHRONOUS_RX_ENABLE;
    usart_obj.usart_rx_cfg.usart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE;
    usart_obj.usart_rx_cfg.usart_rx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE;
    
    usart_obj.EUSART_TxDefaultInterruptHandler = NULL;
    usart_obj.EUSART_RxDefaultInterruptHandler = EUSART_RxDefaultInterruptHandler; // Receiving Done
    usart_obj.EUSART_FramingErrorHandler = NULL;
    usart_obj.EUSART_OverrunErrorHandler = NULL;
    RET = EUSART_ASYNC_Init(&usart_obj);
}

void main(void) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    APPLICATION_INITIALIZE();
    
    usart_module_int_init();
    RET = LED_INITIALIZE(&led1);
    
//    RET = EUSART_ASYNC_WriteByteBlocking('w');

    while(1) {
        
    }
    
    return;
}

void APPLICATION_INITIALIZE(void) {
    STD_RETURN_TYPE RET = E_NOT_OK;
}
