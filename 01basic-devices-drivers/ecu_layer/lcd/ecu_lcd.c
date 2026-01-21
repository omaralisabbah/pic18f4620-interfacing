
#include "ecu_lcd.h"

static STD_RETURN_TYPE LCD_SEND_4BITS(const LCD_4BIT_T *lcd, uint8 _data);
static STD_RETURN_TYPE LCD_4BITS_SEND_EN_SIGNAL(const LCD_4BIT_T *lcd);
static STD_RETURN_TYPE LCD_4BITS_SET_CURSOR(const LCD_4BIT_T *lcd, uint8 row, uint8 column);

static STD_RETURN_TYPE LCD_8BITS_SEND_EN_SIGNAL(const LCD_8BIT_T *lcd);
static STD_RETURN_TYPE LCD_8BITS_SET_CURSOR(const LCD_8BIT_T *lcd, uint8 row, uint8 column);

/**
 * 
 * @param lcd
 * @return 
 */
STD_RETURN_TYPE LCD_4BIT_INITIALIZE(const LCD_4BIT_T *lcd) {
    STD_RETURN_TYPE RET = E_OK;
    uint8 local_pin_counter = ZERO_INIT;
    if(NULL == lcd) {
        RET = E_NOT_OK;
    }
    else {
        RET = PIN_INITIALIZE(&(lcd->LCD_RS));
        RET = PIN_INITIALIZE(&(lcd->LCD_EN));
        for(local_pin_counter = ZERO_INIT; local_pin_counter < 4; local_pin_counter++) {
            RET = PIN_INITIALIZE(&(lcd->LCD_DATA[local_pin_counter]));
        }
        __delay_ms(20);
        RET = LCD_4BIT_SEND_COMMAND(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        RET = LCD_4BIT_SEND_COMMAND(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        RET = LCD_4BIT_SEND_COMMAND(lcd, _LCD_8BIT_MODE_2_LINE);
        RET = LCD_4BIT_SEND_COMMAND(lcd, _LCD_CLEAR);
        RET = LCD_4BIT_SEND_COMMAND(lcd, _LCD_RETURN_HOME);
        RET = LCD_4BIT_SEND_COMMAND(lcd, _LCD_ENTRY_MODE);
        RET = LCD_4BIT_SEND_COMMAND(lcd, _LCD_CURSOR_OFF_DISPLAY_ON);
        RET = LCD_4BIT_SEND_COMMAND(lcd, _LCD_4BIT_MODE_2_LINE);
    }
    return  RET;
}

/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
STD_RETURN_TYPE LCD_4BIT_SEND_COMMAND(const LCD_4BIT_T *lcd, uint8 command) {
    STD_RETURN_TYPE RET = E_OK;
    if(NULL == lcd) {
        RET = E_NOT_OK;
    }
    else {
        RET = GPIO_PIN_WRITE_LOGIC(&(lcd->LCD_RS), GPIO_LOW);
        RET = LCD_SEND_4BITS(&(lcd), (command >> 4));
        RET =LCD_4BITS_SEND_EN_SIGNAL(lcd);
        RET = LCD_SEND_4BITS(&(lcd), (command));
        RET =LCD_4BITS_SEND_EN_SIGNAL(lcd);
    }
    return  RET;
}

/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
STD_RETURN_TYPE LCD_4BIT_SEND_DATA(const LCD_4BIT_T *lcd, uint8 data) {
    STD_RETURN_TYPE RET = E_OK;
    if(NULL == lcd) {
        RET = E_NOT_OK;
    }
    else {
        RET = GPIO_PIN_WRITE_LOGIC(&(lcd->LCD_RS), GPIO_HIGH);
        RET = LCD_SEND_4BITS(&(lcd), (data >> 4));
        RET =LCD_4BITS_SEND_EN_SIGNAL(lcd);
        RET = LCD_SEND_4BITS(&(lcd), (data));
        RET =LCD_4BITS_SEND_EN_SIGNAL(lcd);
    }
    return  RET;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return 
 */
STD_RETURN_TYPE LCD_4BIT_SEND_DATA_POSITION(const LCD_4BIT_T *lcd, uint8 row, uint8 column, uint8 data) {
    STD_RETURN_TYPE RET = E_OK;
    if(NULL == lcd) {
        RET = E_NOT_OK;
    }
    else {
        RET = LCD_4BITS_SET_CURSOR(lcd, row, column);
        RET = LCD_4BIT_SEND_DATA(lcd, data);
    }
    return  RET;
}

/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
STD_RETURN_TYPE LCD_4BIT_SEND_STRING(const LCD_4BIT_T *lcd, uint8 *str) {
    STD_RETURN_TYPE RET = E_OK;
    if(NULL == lcd) {
        RET = E_NOT_OK;
    }
    else {
        while(*str) {            
            RET = LCD_4BIT_SEND_DATA(lcd, *str++);
        }
    }
    return  RET;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return 
 */
STD_RETURN_TYPE LCD_4BIT_SEND_STRING_POSITION(const LCD_4BIT_T *lcd, uint8 row, uint8 column, uint8 *str) {
    STD_RETURN_TYPE RET = E_OK;
    if(NULL == lcd) {
        RET = E_NOT_OK;
    }
    else {
        RET = LCD_4BITS_SET_CURSOR(lcd, row, column);
        while(*str) {            
            RET = LCD_4BIT_SEND_DATA(lcd, *str++);
        }
    }
    return  RET;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param _char
 * @param mem_pos
 * @return 
 */
STD_RETURN_TYPE LCD_4BIT_SEND_CUSTOME_CHAR(const LCD_4BIT_T *lcd, uint8 row, uint8 column, const uint8 _char[], uint8 mem_pos) {
    STD_RETURN_TYPE RET = E_OK;
    uint8 local_pin_counter = ZERO_INIT;
    if(NULL == lcd) {
        RET = E_NOT_OK;
    }
    else {
        RET = LCD_4BIT_SEND_COMMAND(lcd, (_LCD_CGRAM_START + (mem_pos * 8))); // 0x40 = 0100 0000, (8 = Byte)
        for(local_pin_counter = ZERO_INIT; local_pin_counter <= 7; ++local_pin_counter) {
            RET = LCD_4BIT_SEND_DATA(lcd, _char[local_pin_counter]);
        }
        RET = LCD_4BIT_SEND_DATA_POSITION(lcd, row, column, mem_pos);
    }
    return  RET;
}

/**
 * 
 * @param lcd
 * @return 
 */
STD_RETURN_TYPE LCD_8BIT_INITIALIZE(const LCD_8BIT_T *lcd) {
    STD_RETURN_TYPE RET = E_OK;
    uint8 local_pin_counter = ZERO_INIT;
    if(NULL == lcd) {
        RET = E_NOT_OK;
    }
    else {
        RET = PIN_INITIALIZE(&(lcd->LCD_RS));
        RET = PIN_INITIALIZE(&(lcd->LCD_EN));
        for(local_pin_counter = ZERO_INIT; local_pin_counter < 8; local_pin_counter++) {
            RET = PIN_INITIALIZE(&(lcd->LCD_DATA[local_pin_counter]));
        }
        __delay_ms(20);
        RET = LCD_8BIT_SEND_COMMAND(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        RET = LCD_8BIT_SEND_COMMAND(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        RET = LCD_8BIT_SEND_COMMAND(lcd, _LCD_8BIT_MODE_2_LINE);
        RET = LCD_8BIT_SEND_COMMAND(lcd, _LCD_CLEAR);
        RET = LCD_8BIT_SEND_COMMAND(lcd, _LCD_RETURN_HOME);
        RET = LCD_8BIT_SEND_COMMAND(lcd, _LCD_ENTRY_MODE);
        RET = LCD_8BIT_SEND_COMMAND(lcd, _LCD_CURSOR_OFF_DISPLAY_ON);
        RET = LCD_8BIT_SEND_COMMAND(lcd, _LCD_8BIT_MODE_2_LINE);
    }
    return  RET;
}

/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
STD_RETURN_TYPE LCD_8BIT_SEND_COMMAND(const LCD_8BIT_T *lcd, uint8 command) {
    STD_RETURN_TYPE RET = E_OK;
    uint8 local_pin_counter = ZERO_INIT;
    if(NULL == lcd) {
        RET = E_NOT_OK;
    }
    else {
        RET = GPIO_PIN_WRITE_LOGIC(&(lcd->LCD_RS), GPIO_LOW);
        for(local_pin_counter = ZERO_INIT; local_pin_counter < 8; local_pin_counter++) {
            RET = GPIO_PIN_WRITE_LOGIC(&(lcd->LCD_DATA[local_pin_counter]), (command >> local_pin_counter) & (uint8)0x01);
        }
        RET = LCD_8BITS_SEND_EN_SIGNAL(lcd);
    }
    return  RET;
}

/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
STD_RETURN_TYPE LCD_8BIT_SEND_DATA(const LCD_8BIT_T *lcd, uint8 data) {
    STD_RETURN_TYPE RET = E_OK;
    uint8 local_pin_counter = ZERO_INIT;
    if(NULL == lcd) {
        RET = E_NOT_OK;
    }
    else {
        RET = GPIO_PIN_WRITE_LOGIC(&(lcd->LCD_RS), GPIO_HIGH);
        for(local_pin_counter = ZERO_INIT; local_pin_counter < 8; local_pin_counter++) {
            RET = GPIO_PIN_WRITE_LOGIC(&(lcd->LCD_DATA[local_pin_counter]), (data >> local_pin_counter) & (uint8)0x01);
        }
        RET = LCD_8BITS_SEND_EN_SIGNAL(lcd);
    }
    return  RET;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return 
 */
STD_RETURN_TYPE LCD_8BIT_SEND_DATA_POSITION(const LCD_8BIT_T *lcd, uint8 row, uint8 column, uint8 data) {
    STD_RETURN_TYPE RET = E_OK;
    if(NULL == lcd) {
        RET = E_NOT_OK;
    }
    else {
        RET = LCD_8BITS_SET_CURSOR(lcd, row, column);
        RET = LCD_8BIT_SEND_DATA(lcd, data);
    }
    return  RET;
}

/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
STD_RETURN_TYPE LCD_8BIT_SEND_STRING(const LCD_8BIT_T *lcd, uint8 *str) {
    STD_RETURN_TYPE RET = E_OK;
    if(NULL == lcd) {
        RET = E_NOT_OK;
    }
    else {
        while(*str) {            
            RET = LCD_8BIT_SEND_DATA(lcd, *str++);
        }
    }
    return  RET;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return 
 */
STD_RETURN_TYPE LCD_8BIT_SEND_STRING_POSITION(const LCD_8BIT_T *lcd, uint8 row, uint8 column, uint8 *str) {
    STD_RETURN_TYPE RET = E_OK;
    if(NULL == lcd) {
        RET = E_NOT_OK;
    }
    else {
        RET = LCD_8BITS_SET_CURSOR(lcd, row, column);
        while(*str) {            
            RET = LCD_8BIT_SEND_DATA(lcd, *str++);
        }
    }
    return  RET;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param _char
 * @param mem_pos
 * @return 
 */
STD_RETURN_TYPE LCD_8BIT_SEND_CUSTOME_CHAR(const LCD_8BIT_T *lcd, uint8 row, uint8 column, const uint8 _char[], uint8 mem_pos) {
    STD_RETURN_TYPE RET = E_OK;
    uint8 local_pin_counter = ZERO_INIT;
    if(NULL == lcd) {
        RET = E_NOT_OK;
    }
    else {
        RET = LCD_8BIT_SEND_COMMAND(lcd, (_LCD_CGRAM_START + (mem_pos * 8))); // 0x40 = 0100 0000, (8 = Byte)
        for(local_pin_counter = ZERO_INIT; local_pin_counter <= 7; ++local_pin_counter) {
            RET = LCD_8BIT_SEND_DATA(lcd, _char[local_pin_counter]);
        }
        RET = LCD_8BIT_SEND_DATA_POSITION(lcd, row, column, mem_pos);
    }
    return  RET;
}

/**
 * 
 * @param value
 * @param str
 */
void CONVERT_BYTE_TO_STRING(uint8 value, uint8 *str){
    STD_RETURN_TYPE RET = E_OK;
    if(NULL == str) {
        RET = E_NOT_OK;
    }
    else {
        memset(str, '\0', 4); // Number of digits + Null Termination
        sprintf(str, "%i", value);
    }
}

/**
 * 
 * @param value
 * @param str
 */
void CONVERT_SHORT_TO_STRING(uint8 value, uint8 *str) {
    STD_RETURN_TYPE RET = E_OK;
    if(NULL == str) {
        RET = E_NOT_OK;
    }
    else {
        memset(str, '\0', 6); // Number of digits + Null Termination
        sprintf(str, "%i", value);
    }
}

/**
 * 
 * @param value
 * @param str
 */
void CONVERT_INT_TO_STRING(uint8 value, uint8 *str) {
    STD_RETURN_TYPE RET = E_OK;
    if(NULL == str) {
        RET = E_NOT_OK;
    }
    else {
        memset(str, '\0', 11); // Number of digits + Null Termination
        sprintf(str, "%i", value);
    }
}


/**
 * 
 * @param lcd
 * @param _data
 * @return 
 */
static STD_RETURN_TYPE LCD_SEND_4BITS(const LCD_4BIT_T *lcd, uint8 _data) {
    STD_RETURN_TYPE RET = E_OK;
    if(NULL == lcd) {
        RET = E_NOT_OK;
    }
    else {
        RET = GPIO_PIN_WRITE_LOGIC(&(lcd->LCD_DATA[0]), (_data >> 0) & (uint8)0x01);
        RET = GPIO_PIN_WRITE_LOGIC(&(lcd->LCD_DATA[1]), (_data >> 1) & (uint8)0x01);
        RET = GPIO_PIN_WRITE_LOGIC(&(lcd->LCD_DATA[2]), (_data >> 2) & (uint8)0x01);
        RET = GPIO_PIN_WRITE_LOGIC(&(lcd->LCD_DATA[3]), (_data >> 3) & (uint8)0x01);
    }
    return  RET;
}

/**
 * 
 * @param lcd
 * @return 
 */
static STD_RETURN_TYPE LCD_4BITS_SEND_EN_SIGNAL(const LCD_4BIT_T *lcd) {
    STD_RETURN_TYPE RET = E_OK;
    if(NULL == lcd) {
        RET = E_NOT_OK;
    }
    else {
        RET = GPIO_PIN_WRITE_LOGIC(&(lcd->LCD_EN), GPIO_HIGH);
        __delay_us(5);
        RET = GPIO_PIN_WRITE_LOGIC(&(lcd->LCD_EN), GPIO_LOW);
    }
    return  RET;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @return 
 */
static STD_RETURN_TYPE LCD_4BITS_SET_CURSOR(const LCD_4BIT_T *lcd, uint8 row, uint8 column) {
    STD_RETURN_TYPE RET = E_OK;
    column--;
    if(NULL == lcd) {
        RET = E_NOT_OK;
    }
    else {
        switch(row) {
            case ROW1 : RET = LCD_4BIT_SEND_COMMAND(lcd, (0x80 + column)); break;
            case ROW2 : RET = LCD_4BIT_SEND_COMMAND(lcd, (0xc0 + column)); break;
            case ROW3 : RET = LCD_4BIT_SEND_COMMAND(lcd, (0x94 + column)); break;
            case ROW4 : RET = LCD_4BIT_SEND_COMMAND(lcd, (0xD4 + column)); break;
            default   :;
        }
    }
    return  RET;
}

/**
 * 
 * @param lcd
 * @return 
 */
static STD_RETURN_TYPE LCD_8BITS_SEND_EN_SIGNAL(const LCD_8BIT_T *lcd) {
    STD_RETURN_TYPE RET = E_OK;
    if(NULL == lcd) {
        RET = E_NOT_OK;
    }
    else {
        RET = GPIO_PIN_WRITE_LOGIC(&(lcd->LCD_EN), GPIO_HIGH);
        __delay_us(5);
        RET = GPIO_PIN_WRITE_LOGIC(&(lcd->LCD_EN), GPIO_LOW);
    }
    return  RET;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @return 
 */
static STD_RETURN_TYPE LCD_8BITS_SET_CURSOR(const LCD_8BIT_T *lcd, uint8 row, uint8 column) {
    STD_RETURN_TYPE RET = E_OK;
    column--;
    if(NULL == lcd) {
        RET = E_NOT_OK;
    }
    else {
        switch(row) {
            case ROW1 : RET = LCD_8BIT_SEND_COMMAND(lcd, (0x80 + column)); break;
            case ROW2 : RET = LCD_8BIT_SEND_COMMAND(lcd, (0xc0 + column)); break;
            case ROW3 : RET = LCD_8BIT_SEND_COMMAND(lcd, (0x94 + column)); break;
            case ROW4 : RET = LCD_8BIT_SEND_COMMAND(lcd, (0xD4 + column)); break;
            default   :;
        }
    }
    return  RET;
}