
#include "hal_usart.h"

#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void (*EUSART_TxInterruptHandler)(void) = NULL;
#endif
    
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void (*EUSART_RxInterruptHandler)(void) = NULL;
    static void (*EUSART_FramingErrorHandler)(void) = NULL;
    static void (*EUSART_OverrunErrorHandler)(void) = NULL;
#endif    

static void EUSART_Baud_Rate_Calculation(const usart_t *_eusart);
static void EUSART_ASYNC_TX_Init(const usart_t *_eusart);
static void EUSART_ASYNC_RX_Init(const usart_t *_eusart);


STD_RETURN_TYPE EUSART_ASYNC_Init(const usart_t *_eusart) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    if(NULL == _eusart) {
        RET = E_NOT_OK;
    } else {
        RCSTAbits.SPEN = EUSART_MODULE_DISABLE; // Disable EUSART Module
        TRISCbits.RC7 = 1; // RX: Input Configuration as needed
        TRISCbits.RC6 = 1; // TX: Input Configuration as needed
        EUSART_Baud_Rate_Calculation(_eusart);
        EUSART_ASYNC_TX_Init(_eusart);
        EUSART_ASYNC_RX_Init(_eusart);
        RCSTAbits.SPEN = EUSART_MODULE_ENABLE; // Enable EUSART Module
        RET = E_OK;
    }
    return RET;
}

STD_RETURN_TYPE EUSART_ASYNC_DeInit(const usart_t *_eusart) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    if(NULL == _eusart) {
        RET = E_NOT_OK;
    } else {
        RCSTAbits.SPEN = EUSART_MODULE_DISABLE; // Disable EUSART Module
        RET = E_OK;
    }
    return RET;
}

STD_RETURN_TYPE EUSART_ASYNC_ReadByteBlocking(uint8 *_data) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    while(!PIR1bits.RCIF);
    *_data = RCREG;
    return RET;
}

STD_RETURN_TYPE EUSART_ASYNC_ReadByteNonBlocking(uint8 *_data) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    if(1 == PIR1bits.RCIF) {
        *_data = RCREG;
        RET = E_OK;
    } else {
        RET = E_NOT_OK;
    }
    return RET;
}

STD_RETURN_TYPE EUSART_ASYNC_RX_Restart(void) {
    STD_RETURN_TYPE RET = E_OK;
    RCSTAbits.CREN = 0; // Disables receiver (Page: 203)
    RCSTAbits.CREN = 1; // Enables receiver
    return RET;
}

STD_RETURN_TYPE EUSART_ASYNC_WriteByteBlocking(uint8 _data) {
    STD_RETURN_TYPE RET = E_OK;
    while(!TXSTAbits.TRMT);
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    EUSART_TX_InterruptEnable();
#endif
    TXREG = _data;
    return RET;
}

STD_RETURN_TYPE EUSART_ASYNC_WriteStringBlocking(uint8 *_data, uint16 str_len) {
    STD_RETURN_TYPE RET = E_OK;
    uint16 char_counter = ZERO_INIT;
    for(char_counter=ZERO_INIT; char_counter < str_len; char_counter++) {
        RET = EUSART_ASYNC_WriteByteBlocking(_data[char_counter]);
    }
    return RET;
}

STD_RETURN_TYPE EUSART_ASYNC_WriteByteNonBlocking(uint8 _data){
    STD_RETURN_TYPE RET = E_NOT_OK;
    
    if(1 == PIR1bits.TXIF) {
        TXREG = _data;
        RET = E_OK;
    } else {
        RET = E_NOT_OK;
    }
    return RET;
}

STD_RETURN_TYPE EUSART_ASYNC_WriteStringNonBlocking(uint8 *_data, uint16 str_len){
    STD_RETURN_TYPE RET = E_NOT_OK;
    static uint16 current_pos = 0; // Remembers position across calls

    // Check if we still have bytes left to send
    if (current_pos < str_len) {
        if (1 == PIR1bits.TXIF) { // Check if the Transmit Interrupt Flag is set (Buffer Empty)
            TXREG = _data[current_pos];
            current_pos++;
            RET = E_OK;
        } else { // Buffer is busy; return NOT_OK so the caller tries again
            RET = E_NOT_OK;
        }
    }

    if (current_pos >= str_len) { // Reset the counter once the entire string is sent
        current_pos = 0; // Optionally return a specific status indicating completion
    }
    return RET;
}


static void EUSART_Baud_Rate_Calculation(const usart_t *_eusart) {
    float Baud_Rate_Temp = 0;
    switch(_eusart->baudrate_gen_gonfig) {
        case BAUDRATE_ASYN_8BIT_lOW_SPEED:
            // Table 18-1: 3-Bits Configurations
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 64) - 1; // 12
            break;
        case BAUDRATE_ASYN_8BIT_HIGH_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 16) - 1; // 51
            break;
        case BAUDRATE_ASYN_16BIT_lOW_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 16) - 1; // 51
            break;
        case BAUDRATE_ASYN_16BIT_HIGH_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1;
            break;
        case BAUDRATE_SYN_8BIT:
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1;
            break;
        case BAUDRATE_SYN_16BIT:
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1;
            break;
        default : /* Nothing */;
    }
    SPBRG = (uint8)((uint32)Baud_Rate_Temp); // First 8-Bits (LSB)
    SPBRGH = (uint8)(((uint32)Baud_Rate_Temp) >> 8); // Shifting 2-Bits to Right (MSB)
}


static void EUSART_ASYNC_TX_Init(const usart_t *_eusart) {
    if(EUSART_ASYNCHRONOUS_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_enable) {
        TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_ENABLE;
        EUSART_TxInterruptHandler = _eusart->EUSART_TxDefaultInterruptHandler;
        
        // EUSART Transmit Interrupt Configuration
        if(EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_interrupt_enable) {
            PIE1bits.TXIE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE;
            
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            EUSART_TX_InterruptEnable();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 
            INTERRUPT_PriorityLevelsEnable();
            if(INTERRUPT_HIGH_PRIORITY == _eusart->usart_tx_cfg.usart_tx_int_priority){
                INTERRUPT_GlobalInterruptHighEnable();
                EUSART_TX_HighPrioritySet();
            } else if(INTERRUPT_LOW_PRIORITY == _eusart->usart_tx_cfg.usart_tx_int_priority){
                INTERRUPT_GlobalInterruptLowEnable();
                EUSART_TX_LowPrioritySet();
            } else{ /* Nothing */ }
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        } else if(EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE == _eusart->usart_tx_cfg.usart_tx_interrupt_enable) {
            PIE1bits.TXIE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE;
        } else{ /* Nothing */ }

        // EUSART  9-Bit Transmit Configuration
        if(EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_9bit_enable) {
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE;
        } else if(EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE == _eusart->usart_tx_cfg.usart_tx_9bit_enable) {
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE;
        } else{ /* Nothing */ }
    } else { /* Nothing */ }
}


static void EUSART_ASYNC_RX_Init(const usart_t *_eusart) {
    if(EUSART_ASYNCHRONOUS_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_enable) {
        RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE;
        EUSART_RxInterruptHandler = _eusart->EUSART_RxDefaultInterruptHandler;
        EUSART_FramingErrorHandler = _eusart->EUSART_FramingErrorHandler;
        EUSART_OverrunErrorHandler = _eusart->EUSART_OverrunErrorHandler;
        
        // EUSART Receiver Interrupt Configuration
        if(EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_interrupt_enable) {
            PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE;
            
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            EUSART_RX_InterruptEnable();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 
            INTERRUPT_PriorityLevelsEnable();
            if(INTERRUPT_HIGH_PRIORITY == _eusart->usart_rx_cfg.usart_rx_int_priority) {
                INTERRUPT_GlobalInterruptHighEnable();
                EUSART_RX_HighPrioritySet();
            } else if(INTERRUPT_LOW_PRIORITY == _eusart->usart_rx_cfg.usart_rx_int_priority) {
                INTERRUPT_GlobalInterruptLowEnable();
                EUSART_RX_LowPrioritySet();
            } else{ /* Nothing */ }
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        } else if(EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE == _eusart->usart_rx_cfg.usart_rx_interrupt_enable) {
            PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE;
        } else{ /* Nothing */}

        // EUSART  9-Bit Receiver Configuration
        if(EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_9bit_enable) {
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE;
        } else if(EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE == _eusart->usart_rx_cfg.usart_rx_9bit_enable) {
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE;
        } else{ /* Nothing */ }
    } else { /* Nothing */ }
}


void EUSART_TX_ISR(void){
    EUSART_TX_InterruptDisable();
    if(EUSART_TxInterruptHandler) {
        EUSART_TxInterruptHandler();
    }else { /* Nothing */ }
}


void EUSART_RX_ISR(void){
    if(EUSART_RxInterruptHandler) {
        EUSART_RxInterruptHandler();
    } else { /* Nothing */ }
    
    if(EUSART_FramingErrorHandler) {
        EUSART_FramingErrorHandler();
    } else { /* Nothing */ }
    
    if(EUSART_OverrunErrorHandler) {
        EUSART_OverrunErrorHandler();
    } else { /* Nothing */ }
}
