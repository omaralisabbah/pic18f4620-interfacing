
#include "main.h"

timer3_t timer3_obj;
ccp_t ccp_obj;

volatile uint8 CCP1_Second_Copture_Flag = 0;
uint16 Second_Copture = 0;
volatile uint32 Timer3_OverFlow = 0;
uint32 Total_Period_MicroSecond = 0;
uint32 Freq = 0;

void CCP1_DefaultInterruptHandler(void) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    static uint8 CCP1_Interrupt_Flag = 0;
    
    CCP1_Interrupt_Flag++;
    CCP1_Second_Copture_Flag++;
    if(CCP1_Interrupt_Flag == 1) {
        RET = Timer3_Write_Value(&timer3_obj, 0);
    }
    else if(CCP1_Interrupt_Flag == 2) {
        Timer3_OverFlow = 0;
        CCP1_Interrupt_Flag = 0;
        RET = CCP1_Capture_Mode_Read_Value(&Second_Copture);
    }
}

void Timer3_DefaultInterruptHandler(void) {
    Timer3_OverFlow++;
}

void main(void) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    APPLICATION_INITIALIZE();
    
    ccp_obj.CCP1_InterruptHandler = CCP1_DefaultInterruptHandler;
    ccp_obj.ccp_inst = CCP1_INST;
    ccp_obj.ccp_mode = CCP_CAPTURE_MODE_SELECTED;
    ccp_obj.ccp_mode_variant = CCP_CAPTURE_MODE_1_RISING_EDGE;
    ccp_obj.ccp_capture_timer = CCP1_CCP2_TIMER3;
    ccp_obj.ccp_pin.PORT = PORTC_INDEX;
    ccp_obj.ccp_pin.PIN = PIN2;
    ccp_obj.ccp_pin.DIRECTION = GPIO_DIRECTION_INPUT;
    RET = CCP_Init(&ccp_obj);
    
    timer3_obj.TMR3_InterruptHandler = Timer3_DefaultInterruptHandler;
    timer3_obj.timer3_mode = TIMER3_TIMER_MODE;
    timer3_obj.priority = INTERRUPT_LOW_PRIORITY;
    timer3_obj.timer3_prescaler_value = TIMER3_PRESCALER_DIV_BY_1;
    timer3_obj.timer3_preload_value = 0;
    timer3_obj.timer3_reg_wr_mode = TIMER3_RW_REG_8Bit_MODE;
    RET = Timer3_Init(&timer3_obj);

    
    while(1) {
        if(CCP1_Second_Copture_Flag == 2) {
            Total_Period_MicroSecond = (Timer3_OverFlow * 65536) + Second_Copture;
            Freq = (uint32)(1 / (Total_Period_MicroSecond / 1000000.0));
            CCP1_Second_Copture_Flag = 0;
        }
    }
    
    return;
}

void APPLICATION_INITIALIZE(void) {
    STD_RETURN_TYPE RET = E_NOT_OK;
}
