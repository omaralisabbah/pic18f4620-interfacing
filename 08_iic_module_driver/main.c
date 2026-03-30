
#include "main.h"
#include <pic18f4620.h>

/*
    The MSSP module has three associated registers.
    These include a status register (SSPSTAT) and two
    control registers (SSPCON1 and SSPCON2). The use
    of these registers and their individual Configuration bits
    differ significantly depending on whether the MSSP
    module is operated in SPI or I2C mode.
    Additional details are provided under the individual
    sections. Page: 170
*/

mssp_i2c_t i2c_obj;
uint8 slave_ack;
volatile uint8 i2c_slave1_rec_counter;
static volatile uint8 i2c_slave1_rec_data;

void MMSP_I2C_DefaultInterruptHandler(void) {
    // Hold the clock Low (Clock Stretching)
    if((SSPSTATbits.R_nW == 0) && (SSPSTATbits.D_nA == 0)) { 
        uint8 dummy_buffer = SSPBUF;
        while(!SSPSTATbits.BF);
        i2c_slave1_rec_data = SSPBUF;
    } else if(SSPSTATbits.R_nW == 1) { 

    } else { /* Nothing */ }
    I2C_CLOCK_STRETCH_ENABLE();
    I2C_CLOCK_STRETCH_DISABLE();
}

#define SLAVE_1_Write 0x60 // Address = 0x30 + W Bit (0) => 0x60
#define SLAVE_1_Read  0x62 // Address = 0x30 + R Bit (1) => 0x62

void MSSP_I2C_Send_1_Byte(uint8 slave_address, uint8 _data){
    STD_RETURN_TYPE ret = E_NOT_OK;
    ret = MSSP_I2C_Master_Send_Start(&i2c_obj);
    ret = MSSP_I2C_Master_Write_Blocking(&i2c_obj, slave_address, &slave_ack);
    ret = MSSP_I2C_Master_Write_Blocking(&i2c_obj, _data, &slave_ack);
    ret = MSSP_I2C_Master_Send_Stop(&i2c_obj);
}


void MSSP_I2C_Read_1_Byte(uint8 slave_add, uint8 *_data){
    STD_RETURN_TYPE ret = E_NOT_OK;
    ret = MSSP_I2C_Master_Send_Start(&i2c_obj);
    ret = MSSP_I2C_Master_Write_Blocking(&i2c_obj, slave_add, &slave_ack);
    ret = MSSP_I2C_Master_Read_Blocking(&i2c_obj, I2C_MASTER_SEND_NACK, _data);
    ret = MSSP_I2C_Master_Send_Stop(&i2c_obj);
}


void main(void) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    APPLICATION_INITIALIZE();
    
    // i2c_obj.i2c_clock = 100000;
    i2c_obj.i2c_cfg.i2c_mode = I2C_MSSP_SLAVE_MODE;
    i2c_obj.i2c_cfg.i2c_slave_address = 0x62;
    i2c_obj.i2c_cfg.i2c_mode_cfg = I2C_SLAVE_MODE_7BIT_ADDRESS;
    i2c_obj.i2c_cfg.i2c_general_call = I2C_GENERAL_CALL_DISABLE;
    i2c_obj.i2c_cfg.i2c_SMBus_control = I2C_SMBus_DISABLE;
    i2c_obj.i2c_cfg.i2c_slew_rate = I2C_SLEW_RATE_DISABLE;
    i2c_obj.I2C_DefaultInterruptHandler = MMSP_I2C_DefaultInterruptHandler;
    i2c_obj.I2C_Report_Receive_Overflow = NULL;
    i2c_obj.I2C_Report_Write_Collision = NULL;

    RET = MSSP_I2C_Init(&i2c_obj);
    // RET = MSSP_I2C_Master_Send_Start(&i2c_obj); 

    while(1) {
        // MSSP_I2C_Send_1_Byte(SLAVE_1_Write, 'a');
        // __delay_ms(250); 
        // MSSP_I2C_Send_1_Byte(SLAVE_1_Read, 'b');
        // __delay_ms(250);
        // MSSP_I2C_Send_1_Byte(SLAVE_1_Write, 'c');
        // __delay_ms(250); 
        // MSSP_I2C_Send_1_Byte(SLAVE_1_Read, 'd');
        // __delay_ms(250);
        //    MSSP_I2C_Read_1_Byte(SLAVE_1_Read, &master_rec_data);
        //    __delay_ms(250);
        //    MSSP_I2C_Read_1_Byte(SLAVE_1_Read, &master_rec_data);
        //    __delay_ms(250);
    }
    
    return;
}

void APPLICATION_INITIALIZE(void) {
    STD_RETURN_TYPE RET = E_NOT_OK;
}
