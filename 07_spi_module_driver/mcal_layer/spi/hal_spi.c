
#include "hal_spi.h"

#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*SPI_InterruptHandler)(void) = NULL;
#endif

static void MSSP_SPI_Interrupt_Init(const SPI_Config *Config);
static void MSSP_SPI_Msster_Mode_GPIO_PIN_Configurations(const SPI_Config *Config);
static void MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(const SPI_Config *Config);
    
STD_RETURN_TYPE SPI_Init(const SPI_Config *Config) {
    STD_RETURN_TYPE RET = E_OK;
    
    if(NULL == Config) {
        RET = E_NOT_OK;
    } else {
        SPI_DISABLE_MODULE(); // Disable SPI Module
        SSPCON1bits.SSPM = Config->spi_mode; // MSSP SPI Mode Select

        // GPIO PIN Configurations
        if((Config->spi_mode == SPI_MASTER_FOSC_DIV4) || (Config->spi_mode == SPI_MASTER_FOSC_DIV16) ||
            (Config->spi_mode == SPI_MASTER_FOSC_DIV64) || (Config->spi_mode == SPI_MASTER_FOSC_TMR2)){
            MSSP_SPI_Msster_Mode_GPIO_PIN_Configurations(Config);
        } else if((Config->spi_mode == SPI_SLAVE_SS_ENABLE) || (Config->spi_mode == SPI_SLAVE_SS_DISABLE)) {
            MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(Config);
        }

        SSPCON1bits.CKP = Config->spi_config.ClockPolarity; // Clock Polarity Select
        SSPSTATbits.SMP = Config->spi_config.SampleSelect; // SPI Sample Select
        SSPSTATbits.CKE = Config->spi_config.ClockSelect; // SPI Clock Select
        MSSP_SPI_Interrupt_Init(Config); // MSSP SPI Interrupt Configurations
        SPI_ENABLE_MODULE(); // Enable SPI Module
    }
    
    return RET;
}

STD_RETURN_TYPE SPI_DeInit(const SPI_Config *Config){
    STD_RETURN_TYPE RET = E_NOT_OK;
    
    if(NULL == Config){
        RET = E_NOT_OK;
    } else {
        /* Disable SPI Module */
        SPI_DISABLE_MODULE();
/* Interrupt Configurations */        
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        MSSP_SPI_InterruptDisable();
#endif
    }
    
    return RET;
}

STD_RETURN_TYPE SPI_Send_Byte(const SPI_Config *Config, const uint8 _data) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    
    if(NULL == Config) {
        RET = E_NOT_OK;
    } else {
        SSPBUF = _data;
        while(!(PIR1bits.SSPIF)); // Waiting to transmit
        PIR1bits.SSPIF = 0;
    }
    
    return RET;
}

STD_RETURN_TYPE SPI_Read_Byte(const SPI_Config *Config, uint8 *_data) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    
    if((NULL == Config) || (NULL == _data)) {
        RET = E_NOT_OK;
    } else {
        while(SSPSTATbits.BF == 0); // Receive not complete, SSPBUF is empty
        *_data = SSPBUF;
    }
    
    return RET;
}

STD_RETURN_TYPE SPI_Send_Byte_NonBlocking(const SPI_Config *Config, const uint8 _data) {
    STD_RETURN_TYPE RET = E_NOT_OK;

    if (NULL == Config) {
        RET = E_NOT_OK;
    } else {
        SSPBUF = _data;

        if (SSPCON1bits.WCOL) {
            SSPCON1bits.WCOL = 0; 
            ret = E_NOT_OK;
        } else {    
            RET = E_OK;
        }
    }
    return RET;
}

STD_RETURN_TYPE SPI_Read_Byte_NonBlocking(const SPI_Config *Config, uint8 *_data) {
    STD_RETURN_TYPE RET = E_NOT_OK;

    if (NULL == Config || NULL == _data) {
        RET = E_NOT_OK;
    } else {
        // Check if the receive buffer is full (SSPSTAT bit 0)
        if (SSPSTATbits.BF == 1) {
            *_data = SSPBUF;
            RET = E_OK;
        } else {
            RET = E_NOT_OK; // Data not yet received; return E_NOT_OK to indicate "busy/empty"
        }
    }

    return RET;
}

void MSSP_SPI_ISR(void){
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    MSSP_SPI_InterruptFlagClear();
    if(SPI_InterruptHandler){
        SPI_InterruptHandler();
    }
#endif
}

static void MSSP_SPI_Interrupt_Init(const SPI_Config *Config) {
// Interrupt Configurations      
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    MSSP_SPI_InterruptEnable();
    MSSP_SPI_InterruptFlagClear();
    SPI_InterruptHandler = Config->MSSP_SPI_InterruptHandler;
/* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
    INTERRUPT_PriorityLevelsEnable();
    if(INTERRUPT_HIGH_PRIORITY == Config->priority){
        /* Enables all high-priority interrupts */
        INTERRUPT_GlobalInterruptHighEnable();
        MSSP_SPI_HighPrioritySet();
    }
    else if(INTERRUPT_LOW_PRIORITY == Config->priority){
        /* Enables all unmasked peripheral interrupts */
        INTERRUPT_GlobalInterruptLowEnable();
        MSSP_SPI_LowPrioritySet();
    }
    else{ /* Nothing */ }
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif      
#endif        
}


static void MSSP_SPI_Msster_Mode_GPIO_PIN_Configurations(const SPI_Config *Config) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    pin_config_t SPI_SDO = {.port = PORTC_INDEX, .pin = GPIO_PIN5, .direction = GPIO_DIRECTION_OUTPUT};
    pin_config_t SPI_SDI = {.port = PORTC_INDEX, .pin = GPIO_PIN4, .direction = GPIO_DIRECTION_INPUT};
    pin_config_t SPI_CLK = {.port = PORTC_INDEX, .pin = GPIO_PIN3, .direction = GPIO_DIRECTION_OUTPUT};
    
    RET = gpio_pin_direction_intialize(&SPI_SDO); 
    RET = gpio_pin_direction_intialize(&SPI_SDI);
    RET = gpio_pin_direction_intialize(&SPI_CLK);
}


static void MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(const SPI_Config *Config) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    pin_config_t SPI_SDO = {.port = PORTC_INDEX, .pin = GPIO_PIN5, .direction = GPIO_DIRECTION_OUTPUT};
    pin_config_t SPI_SDI = {.port = PORTC_INDEX, .pin = GPIO_PIN4, .direction = GPIO_DIRECTION_INPUT};
    pin_config_t SPI_CLK = {.port = PORTC_INDEX, .pin = GPIO_PIN3, .direction = GPIO_DIRECTION_INPUT};
    pin_config_t SPI_SS = {.port = PORTA_INDEX, .pin = GPIO_PIN5, .direction = GPIO_DIRECTION_INPUT};
    
    RET = gpio_pin_direction_intialize(&SPI_SDO); 
    RET = gpio_pin_direction_intialize(&SPI_SDI);
    RET = gpio_pin_direction_intialize(&SPI_CLK); 
    
    if(SPI_SLAVE_SS_ENABLE == Config->spi_mode) {
        RET = gpio_pin_direction_intialize(&SPI_SS);
    }
}