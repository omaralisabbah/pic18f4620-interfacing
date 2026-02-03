
#include "main.h"


LCD_4BIT_T lcd_1 = {
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

adc_config_t adc_1 = {
    .ADC_InterruptHandler = NULL,
    .acquisition_time = ADC_12_TAD,
    .adc_channel = ADC_CHANNEL_AN0,
    .conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    .result_format = ADC_RESULT_RIGHT,
    .voltage_reference = ADC_VOLTAGE_REFERENCE_DISABLED
};

uint16 adc_res_1, adc_res_2, adc_res_3, adc_res_4;
uint8 adc_res_1_txt[7], adc_res_2_txt[7], adc_res_3_txt[7], adc_res_4_txt[7];


void main(void) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    APPLICATION_INITIALIZE();
    
    RET = LCD_4BIT_INITIALIZE(&lcd_1);
    RET = ADC_Init(&adc_1);
    
    RET = LCD_4BIT_SEND_STRING_POSITION(&lcd_1, 1, 7, "ADC Test");
    __delay_ms(2000);
    RET = LCD_4BIT_SEND_COMMAND(&lcd_1, _LCD_CLEAR);
    
    RET = LCD_4BIT_SEND_STRING_POSITION(&lcd_1, 1, 1, "Pot0: ");
    RET = LCD_4BIT_SEND_STRING_POSITION(&lcd_1, 2, 1, "Pot1: ");
    RET = LCD_4BIT_SEND_STRING_POSITION(&lcd_1, 3, 1, "Pot2: ");
    RET = LCD_4BIT_SEND_STRING_POSITION(&lcd_1, 4, 1, "Pot3: ");
    
    while(1) {
        RET = ADC_GetConversion_Blocking(&adc_1, ADC_CHANNEL_AN0, &adc_res_1);
        RET = ADC_GetConversion_Blocking(&adc_1, ADC_CHANNEL_AN1, &adc_res_2);
        RET = ADC_GetConversion_Blocking(&adc_1, ADC_CHANNEL_AN2, &adc_res_3);
        RET = ADC_GetConversion_Blocking(&adc_1, ADC_CHANNEL_AN3, &adc_res_4);
        
        RET = CONVERT_UINT16_TO_STRING(adc_res_1, adc_res_1_txt);
        RET = CONVERT_UINT16_TO_STRING(adc_res_2, adc_res_2_txt);
        RET = CONVERT_UINT16_TO_STRING(adc_res_3, adc_res_3_txt);
        RET = CONVERT_UINT16_TO_STRING(adc_res_4, adc_res_4_txt);
        
        RET = LCD_4BIT_SEND_STRING_POSITION(&lcd_1, 1, 7, adc_res_1_txt);
        RET = LCD_4BIT_SEND_STRING_POSITION(&lcd_1, 2, 7, adc_res_2_txt);
        RET = LCD_4BIT_SEND_STRING_POSITION(&lcd_1, 3, 7, adc_res_3_txt);
        RET = LCD_4BIT_SEND_STRING_POSITION(&lcd_1, 4, 7, adc_res_4_txt);
    }
    
    return;
}

void APPLICATION_INITIALIZE(void) {
    STD_RETURN_TYPE RET = E_NOT_OK;
}

STD_RETURN_TYPE CONVERT_UINT16_TO_STRING(uint8 value, uint8 *str) {
    STD_RETURN_TYPE RET = E_OK;
    uint8 Temp_String[6] = {0};
    uint8 counter = 0;
    if(NULL == str) {
        RET = E_NOT_OK;
    }
    else {
        memset(str, ' ', 5); // Number of digits + Null Termination
        str[5] = '\0';
        sprintf((char *)Temp_String, "%i", value);
        while(Temp_String[counter] != '\0') {
            str[counter] = Temp_String[counter];
            counter++;
        }
    }
    return RET;
}