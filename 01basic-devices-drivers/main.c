
#include "main.h"

LCD_4BIT_T lcd_one = {
    .LCD_RS.PORT = PORTC_INDEX,
    .LCD_RS.PIN = PIN0,
    .LCD_RS.DIRECTION = GPIO_DIRECTION_OUTPUT,
    .LCD_RS.LOGIC = GPIO_LOW,
    
    .LCD_EN.PORT = PORTC_INDEX,
    .LCD_EN.PIN = PIN1,
    .LCD_EN.DIRECTION = GPIO_DIRECTION_OUTPUT,
    .LCD_EN.LOGIC = GPIO_LOW,
    
    .LCD_DATA[0].PORT = PORTC_INDEX,
    .LCD_DATA[0].PIN = PIN2,
    .LCD_DATA[0].DIRECTION = GPIO_DIRECTION_OUTPUT,
    .LCD_DATA[0].LOGIC = GPIO_LOW,
    .LCD_DATA[1].PORT = PORTC_INDEX,
    .LCD_DATA[1].PIN = PIN3,
    .LCD_DATA[1].DIRECTION = GPIO_DIRECTION_OUTPUT,
    .LCD_DATA[1].LOGIC = GPIO_LOW,
    .LCD_DATA[2].PORT = PORTC_INDEX,
    .LCD_DATA[2].PIN = PIN4,
    .LCD_DATA[2].DIRECTION = GPIO_DIRECTION_OUTPUT,
    .LCD_DATA[2].LOGIC = GPIO_LOW,
    .LCD_DATA[3].PORT = PORTC_INDEX,
    .LCD_DATA[3].PIN = PIN5,
    .LCD_DATA[3].DIRECTION = GPIO_DIRECTION_OUTPUT,
    .LCD_DATA[3].LOGIC = GPIO_LOW
};
 
LCD_8BIT_T lcd_two = {
    .LCD_RS.PORT = PORTC_INDEX,
    .LCD_RS.PIN = PIN6,
    .LCD_RS.DIRECTION = GPIO_DIRECTION_OUTPUT,
    .LCD_RS.LOGIC = GPIO_LOW,
    
    .LCD_EN.PORT = PORTC_INDEX,
    .LCD_EN.PIN = PIN7,
    .LCD_EN.DIRECTION = GPIO_DIRECTION_OUTPUT,
    .LCD_EN.LOGIC = GPIO_LOW,
    
    .LCD_DATA[0].PORT = PORTD_INDEX,
    .LCD_DATA[0].PIN = PIN0,
    .LCD_DATA[0].DIRECTION = GPIO_DIRECTION_OUTPUT,
    .LCD_DATA[0].LOGIC = GPIO_LOW,
    .LCD_DATA[1].PORT = PORTD_INDEX,
    .LCD_DATA[1].PIN = PIN1,
    .LCD_DATA[1].DIRECTION = GPIO_DIRECTION_OUTPUT,
    .LCD_DATA[1].LOGIC = GPIO_LOW,
    .LCD_DATA[2].PORT = PORTD_INDEX,
    .LCD_DATA[2].PIN = PIN2,
    .LCD_DATA[2].DIRECTION = GPIO_DIRECTION_OUTPUT,
    .LCD_DATA[2].LOGIC = GPIO_LOW,
    .LCD_DATA[3].PORT = PORTD_INDEX,
    .LCD_DATA[3].PIN = PIN3,
    .LCD_DATA[3].DIRECTION = GPIO_DIRECTION_OUTPUT,
    .LCD_DATA[3].LOGIC = GPIO_LOW,
    .LCD_DATA[4].PORT = PORTD_INDEX,
    .LCD_DATA[4].PIN = PIN4,
    .LCD_DATA[4].DIRECTION = GPIO_DIRECTION_OUTPUT,
    .LCD_DATA[4].LOGIC = GPIO_LOW,
    .LCD_DATA[5].PORT = PORTD_INDEX,
    .LCD_DATA[5].PIN = PIN5,
    .LCD_DATA[5].DIRECTION = GPIO_DIRECTION_OUTPUT,
    .LCD_DATA[5].LOGIC = GPIO_LOW,
    .LCD_DATA[6].PORT = PORTD_INDEX,
    .LCD_DATA[6].PIN = PIN6,
    .LCD_DATA[6].DIRECTION = GPIO_DIRECTION_OUTPUT,
    .LCD_DATA[6].LOGIC = GPIO_LOW,
    .LCD_DATA[7].PORT = PORTD_INDEX,
    .LCD_DATA[7].PIN = PIN7,
    .LCD_DATA[7].DIRECTION = GPIO_DIRECTION_OUTPUT,
    .LCD_DATA[7].LOGIC = GPIO_LOW,
};


const uint8 battery_body[] = {0x0E, 0x0A, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x00};
const uint8 increment_1[]  = {0x0E, 0x0A, 0x11, 0x11, 0x11, 0x1F, 0x1F, 0x00};
const uint8 increment_2[]  = {0x0E, 0x0A, 0x11, 0x11, 0x1F, 0x1F, 0x1F, 0x00};
const uint8 increment_3[]  = {0x0E, 0x0A, 0x11, 0x1F, 0x1F, 0x1F, 0x1F, 0x00};
const uint8 increment_4[]  = {0x0E, 0x0A, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00};
const uint8 increment_5[]  = {0x0E, 0x0E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00};


void main(void) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    APPLICATION_INITIALIZE();
    while(1) {
        RET = LCD_8BIT_SEND_CUSTOME_CHAR(&lcd_two, 1, 20, battery_body, 0);
        __delay_ms(200);
        RET = LCD_8BIT_SEND_CUSTOME_CHAR(&lcd_two, 1, 20, increment_1, 0);
        __delay_ms(200);
        RET = LCD_8BIT_SEND_CUSTOME_CHAR(&lcd_two, 1, 20, increment_2, 0);
        __delay_ms(200);
        RET = LCD_8BIT_SEND_CUSTOME_CHAR(&lcd_two, 1, 20, increment_3, 0);
        __delay_ms(200);
        RET = LCD_8BIT_SEND_CUSTOME_CHAR(&lcd_two, 1, 20, increment_4, 0);
        __delay_ms(200);
        RET = LCD_8BIT_SEND_CUSTOME_CHAR(&lcd_two, 1, 20, increment_5, 0);
        __delay_ms(200);
    }
    
    return;
}

void APPLICATION_INITIALIZE(void) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    RET = LCD_4BIT_INITIALIZE(&(lcd_one));
    RET = LCD_8BIT_INITIALIZE(&(lcd_two));
}