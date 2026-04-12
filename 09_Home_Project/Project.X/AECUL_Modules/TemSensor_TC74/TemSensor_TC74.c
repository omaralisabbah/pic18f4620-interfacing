
#include "TemSensor_TC74.h"

uint8_t TempSensor_TC74_Read_Temp(i2c_address_t TC74_Address){
    uint8_t TC74_TempValue = 0;
    TC74_TempValue = I2C_Read1ByteRegister(TC74_Address, 0x00);
    
    return TC74_TempValue;
}