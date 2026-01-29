
#include "hal_eeprom.h"

/*
 * The EEADRH:EEADR register pair is used to address
    the data EEPROM for read and write operations.
    EEADRH holds the two MSbits of the address; the
    upper 6 bits are ignored. The 10-bit range of the pair
    can address a memory range of 1024 bytes (00h to
    3FFh).  
*/
/*
 * Access to the data EEPROM is controlled by two
    registers: EECON1 and EECON2. These are the same
    registers which control access to the program memory
    and are used in a similar manner for the data
    EEPROM.
*/
/*
 * 
 * The EECON1 register (Register 6-1) is the control
    register for data and program memory access. Control
    bit EEPGD determines if the access will be to program
    or data EEPROM memory. When clear, operations will
    access the data EEPROM memory. When set, program
    memory is accessed.
 * 
    Control bit, CFGS, determines if the access will be to
    the Configuration registers or to program memory/data
    EEPROM memory. When set, subsequent operations
    access Configuration registers. When CFGS is clear,
    the EEPGD bit selects either Flash program or data
    EEPROM memory.
 * 
    The WREN bit, when set, will allow a write operation.
    On power-up, the WREN bit is clear. The WRERR bit is
    set in hardware when the WREN bit is set and cleared
    when the internal programming timer expires and the
    write operation is complete. 
*/


/**
 * @Summary Writes a data byte to Data EEPROM
 * @Description This routine writes a data byte to given Data EEPROM location
 * @Preconditions None
 * @param bAdd - Data EEPROM location to which data to be written
 * @param bData - Data to be written to Data EEPROM location
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 * @Example ret = Data_EEPROM_WriteByte(0x3ff, 0);
 */
STD_RETURN_TYPE Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData){
    STD_RETURN_TYPE RET = E_OK;
    
    // Read the Interrupt Status "Enabled or Disabled"
    uint8 Global_Interrupt_Status = INTCONbits.GIE;
    
    // Update the Address Registers
    EEADRH = (uint8)((bAdd >> 8) & 0x03);
    EEADR = (uint8)(bAdd & 0xFF);
            
    // Update the Data Register
    EEDATA = bData;
    
    // Select Access data EEPROM memory
    EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
    EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
    
    // Allows write cycles to Flash program/data EEPROM
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_FLASH_EEPROM;
    
    // Disable all interrupts "General Interrupt"
    INTERRUPT_GlobalInterruptDisable();
    
    // Write the required sequence : 0x55 -> 0xAA
    EECON2 = 0x55;
    EECON2 = 0xAA;
    
    // Initiates a data EEPROM erase/write cycle
    EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
    
    // Wait for write to complete
    while(EECON1bits.WR);
    
    // Inhibits write cycles to Flash program/data EEPROM
    EECON1bits.WREN = INHIBTS_WRITE_CYCLES_FLASH_EEPROM;
    
    // Restore the Interrupt Status "Enabled or Disabled"
    INTCONbits.GIE = Global_Interrupt_Status;
    
    return RET;
}

/**
 * @Summary Reads a data byte from Data EEPROM
 * @Description This routine reads a data byte from given Data EEPROM location
 * @Preconditions None
 * @param bAdd - Data EEPROM location from which data has to be read
 * @param bData - Data byte read from given Data EEPROM location
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 * @Example ret = Data_EEPROM_ReadByte(0x3ff, &eeprom_read_val);
 */
STD_RETURN_TYPE Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData){
    STD_RETURN_TYPE RET = E_NOT_OK;
    if(NULL == bData){
        RET = E_NOT_OK;
    }
    else{
        // Update the Address Registers
        EEADRH = (uint8)((bAdd >> 8) & 0x03);
        EEADR = (uint8)(bAdd & 0xFF);
        
        // Select Access data EEPROM memory
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
        EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
        
        // Initiates a data EEPROM read cycle
        EECON1bits.RD = INITIATE_DATA_EEPROM_READ;
        
        NOP(); // NOPs may be required for latency at high frequencies
        NOP(); // NOPs may be required for latency at high frequencies
        
        // Return data 
        *bData = EEDATA;
        RET = E_OK;
    }
    return RET;
}
