
#ifndef ECU_LCD_H
#define	ECU_LCD_H

#define _XTAL_FREQ 4000000UL

#include "ecu_lcd_cfg.h"
#include "../../mcal_layer/gpio/hal_gpio.h"

#define _LCD_CLEAR                          0X01
#define _LCD_RETURN_HOME                    0x02
#define _LCD_ENTRY_MODE                     0X06

#define _LCD_CURSOR_OFF_DISPLAY_ON          0X0C
#define _LCD_CURSOR_OFF_DISPLAY_OFF         0x08

#define _LCD_CURSOR_ON_BLINK_ON             0x0F
#define _LCD_CURSOR_ON_BLINK_OFF            0x0E

#define _LCD_DISPLAY_SHIFT_RIGHT            0x1C
#define _LCD_DISPLAY_SHIFT_LEFT             0x18

#define _LCD_4BIT_MODE_2_LINE               0x28
#define _LCD_8BIT_MODE_2_LINE               0x38

#define _LCD_CGRAM_START                    0x40
#define _LCD_DDRAM_START                    0x80

#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4

typedef struct {
    PIN_CONFIG_T LCD_RS;
    PIN_CONFIG_T LCD_EN;
    PIN_CONFIG_T LCD_DATA[4];
}LCD_4BIT_T;

typedef struct {
    PIN_CONFIG_T LCD_RS;
    PIN_CONFIG_T LCD_EN;
    PIN_CONFIG_T LCD_DATA[8];
}LCD_8BIT_T;

STD_RETURN_TYPE LCD_4BIT_INITIALIZE(const LCD_4BIT_T *lcd);
STD_RETURN_TYPE LCD_4BIT_SEND_COMMAND(const LCD_4BIT_T *lcd, uint8 command);
STD_RETURN_TYPE LCD_4BIT_SEND_DATA(const LCD_4BIT_T *lcd, uint8 data);
STD_RETURN_TYPE LCD_4BIT_SEND_DATA_POSITION(const LCD_4BIT_T *lcd, uint8 row, uint8 column, uint8 data);
STD_RETURN_TYPE LCD_4BIT_SEND_STRING(const LCD_4BIT_T *lcd, uint8 *str);
STD_RETURN_TYPE LCD_4BIT_SEND_STRING_POSITION(const LCD_4BIT_T *lcd, uint8 row, uint8 column, uint8 *str);
STD_RETURN_TYPE LCD_4BIT_SEND_CUSTOME_CHAR(const LCD_4BIT_T *lcd, uint8 row, uint8 column, const uint8 _char[], uint8 mem_pos);

STD_RETURN_TYPE LCD_8BIT_INITIALIZE(const LCD_8BIT_T *lcd);
STD_RETURN_TYPE LCD_8BIT_SEND_COMMAND(const LCD_8BIT_T *lcd, uint8 command);
STD_RETURN_TYPE LCD_8BIT_SEND_DATA(const LCD_8BIT_T *lcd, uint8 data);
STD_RETURN_TYPE LCD_8BIT_SEND_DATA_POSITION(const LCD_8BIT_T *lcd, uint8 row, uint8 column, uint8 data);
STD_RETURN_TYPE LCD_8BIT_SEND_STRING(const LCD_8BIT_T *lcd, uint8 *str);
STD_RETURN_TYPE LCD_8BIT_SEND_STRING_POSITION(const LCD_8BIT_T *lcd, uint8 row, uint8 column, uint8 *str);
STD_RETURN_TYPE LCD_8BIT_SEND_CUSTOME_CHAR(const LCD_8BIT_T *lcd, uint8 row, uint8 column, const uint8 _char[], uint8 mem_pos);

STD_RETURN_TYPE CONVERT_BYTE_TO_STRING(uint8 value, uint8 *str);
STD_RETURN_TYPE CONVERT_SHORT_TO_STRING(uint8 value, uint8 *str);
STD_RETURN_TYPE CONVERT_INT_TO_STRING(uint8 value, uint8 *str);

#endif	/* ECU_LCD_H */

