
#include "main.h"

LED_T led1 = {.PORT_NAME = PORTC_INDEX, .PIN = PIN0, .LED_STATUS = GPIO_LOW};
LED_T led2 = {.PORT_NAME = PORTC_INDEX, .PIN = PIN1, .LED_STATUS = GPIO_LOW};
LED_T led3 = {.PORT_NAME = PORTC_INDEX, .PIN = PIN2, .LED_STATUS = GPIO_LOW};
LED_T led4 = {.PORT_NAME = PORTC_INDEX, .PIN = PIN3, .LED_STATUS = GPIO_LOW};

void RB4_HIGH_Int_APP_ISR(void){
    LED_TURN_ON(&led1);
    __delay_ms(500);
}

void RB4_LOW_Int_APP_ISR(void){
    LED_TURN_ON(&led2);
    __delay_ms(500);
}

void RB5_HIGH_Int_APP_ISR(void){
    LED_TURN_OFF(&led1);
}

void RB5_LOW_Int_APP_ISR(void){
    LED_TURN_OFF(&led2);
}

void RB6_HIGH_Int_APP_ISR(void){
    LED_TURN_ON(&led3);
}

void RB6_LOW_Int_APP_ISR(void){
    LED_TURN_ON(&led4);
}

void RB7_HIGH_Int_APP_ISR(void){
    LED_TURN_OFF(&led3);
}

void RB7_LOW_Int_APP_ISR(void){
    LED_TURN_OFF(&led4);
}
        
interrupt_RBx_t rb4_int_obj = {
  .EXT_Interrupt_Handler_High =  RB4_HIGH_Int_APP_ISR,
  .EXT_Interrupt_Handler_Low =  RB4_LOW_Int_APP_ISR,
  .priority = INTERRUPT_HIGH_PRIORITY,
  .mcu_pin.PORT = PORTB_INDEX,
  .mcu_pin.PIN = PIN4,
  .mcu_pin.DIRECTION = GPIO_DIRECTION_INPUT
};

interrupt_RBx_t rb5_int_obj = {
  .EXT_Interrupt_Handler_High =  RB5_HIGH_Int_APP_ISR,
  .EXT_Interrupt_Handler_Low =  RB5_LOW_Int_APP_ISR,
  .priority = INTERRUPT_HIGH_PRIORITY,
  .mcu_pin.PORT = PORTB_INDEX,
  .mcu_pin.PIN = PIN5,
  .mcu_pin.DIRECTION = GPIO_DIRECTION_INPUT
};

interrupt_RBx_t rb6_int_obj = {
  .EXT_Interrupt_Handler_High =  RB6_HIGH_Int_APP_ISR,
  .EXT_Interrupt_Handler_Low =  RB6_LOW_Int_APP_ISR,
  .priority = INTERRUPT_HIGH_PRIORITY,
  .mcu_pin.PORT = PORTB_INDEX,
  .mcu_pin.PIN = PIN6,
  .mcu_pin.DIRECTION = GPIO_DIRECTION_INPUT
};

interrupt_RBx_t rb7_int_obj = {
  .EXT_Interrupt_Handler_High =  RB7_HIGH_Int_APP_ISR,
  .EXT_Interrupt_Handler_Low =  RB7_LOW_Int_APP_ISR,
  .priority = INTERRUPT_HIGH_PRIORITY,
  .mcu_pin.PORT = PORTB_INDEX,
  .mcu_pin.PIN = PIN7,
  .mcu_pin.DIRECTION = GPIO_DIRECTION_INPUT
};
        
void main(void) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    APPLICATION_INITIALIZE();
    
    RET = LED_INTIALIZE(&led1);
    RET = LED_INTIALIZE(&led2);
    RET = LED_INTIALIZE(&led3);
    RET = LED_INTIALIZE(&led3);
    
    RET = Interrupt_RBx_Init(&rb4_int_obj);
    RET = Interrupt_RBx_Init(&rb5_int_obj);
    RET = Interrupt_RBx_Init(&rb6_int_obj);
    RET = Interrupt_RBx_Init(&rb7_int_obj);
    
    while(1) {
        LED_TURN_TOGGLE(&led4);
        __delay_ms(250);
    }
    
    return;
}

void APPLICATION_INITIALIZE(void) {
    STD_RETURN_TYPE RET = E_NOT_OK;
}