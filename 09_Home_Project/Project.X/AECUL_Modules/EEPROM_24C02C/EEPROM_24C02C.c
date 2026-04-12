
#include <pic18.h>

#include "EEPROM_24C02C.h"

void EEPROM_24C02C_Write_Byte(i2c_address_t EEPROM_Address, i2c_address_t Byte_Address, uint8_t Data){
    I2C_Write1ByteRegister(EEPROM_Address, Byte_Address, Data);
}

uint8_t EEPROM_24C02C_Read_Byte(i2c_address_t EEPROM_Address, i2c_address_t Byte_Address){
    uint8_t RecValue = 0;
    RecValue = I2C_Read1ByteRegister(EEPROM_Address, Byte_Address);
    
    return RecValue;
}