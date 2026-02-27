#include "hal_gpio.h"

/* reference to the data direction control register */
volatile uint8 *TRIS_REGISTERS[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE}; // Same Index like ports enumeration (PORTA_INDEX = 0,)
/* reference to the data latch register (read and write to data latch) */
volatile uint8 *LAT_REGISTERS[] = {&LATA, &LATB, &LATC, &LATD, &LATE};
/* reference to the port status register */
volatile uint8 *PORT_REGISTERS[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

/**
 * @brief Initialize the direction of a specific pin @ref DIRECTION_T
 * @param _PIN_CONFIG pointer to the configurations @ref PIN_CONFIG_T
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PIN_CONFIGURATIONS == CONFIG_ENABLE
STD_RETURN_TYPE GPIO_PIN_DIRECTION_INITIALIZE(const PIN_CONFIG_T *_PIN_CONFIG) {
    STD_RETURN_TYPE RET = E_OK;
    if((NULL == _PIN_CONFIG) || (_PIN_CONFIG->PIN > PORT_BIN_MAX_NUMBER-1)) {
        RET = E_NOT_OK;
    }
    else {
        switch(_PIN_CONFIG->DIRECTION) {
        case  GPIO_DIRECTION_OUTPUT :
            CLEAR_BIT(*TRIS_REGISTERS[_PIN_CONFIG->PORT], _PIN_CONFIG->PIN); // dereferencing the address
            break;
        case GPIO_DIRECTION_INPUT :
            SET_BIT(*TRIS_REGISTERS[_PIN_CONFIG->PORT], _PIN_CONFIG->PIN);
            break;
        default : RET = E_NOT_OK;
        }
    }
    return  RET;
}
#endif

/**
 * 
 * @param _PIN_CONFIG pointer to the configurations @ref PIN_CONFIG_T
 * @param DIREC_STATUS
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PIN_CONFIGURATIONS == CONFIG_ENABLE
STD_RETURN_TYPE GPIO_PIN_DIRECTION_STATUS(const PIN_CONFIG_T *_PIN_CONFIG, DIRECTION_T *DIREC_STATUS) {
    STD_RETURN_TYPE RET = E_OK;
    if((NULL == _PIN_CONFIG) || (NULL == DIREC_STATUS) || (_PIN_CONFIG->PIN > PORT_BIN_MAX_NUMBER-1)) {
        RET = E_NOT_OK;
    }
    else {
        *DIREC_STATUS = READ_BIT(*TRIS_REGISTERS[_PIN_CONFIG->PORT], _PIN_CONFIG->PIN);
    }
    return  RET;
}
#endif

/**
 * 
 * @param _PIN_CONFIG pointer to the configurations @ref PIN_CONFIG_T
 * @param LOGIC
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PIN_CONFIGURATIONS == CONFIG_ENABLE
STD_RETURN_TYPE GPIO_PIN_WRITE_LOGIC(const PIN_CONFIG_T *_PIN_CONFIG, LOGIC_T LOGIC) {
    STD_RETURN_TYPE RET = E_OK;
    if(NULL == _PIN_CONFIG || _PIN_CONFIG->PIN > PORT_BIN_MAX_NUMBER-1) {
        RET = E_NOT_OK;
    }
    else {
        switch(LOGIC) {
            case GPIO_LOW :
                CLEAR_BIT(*LAT_REGISTERS[_PIN_CONFIG->PORT], _PIN_CONFIG->PIN);
                break;
            case GPIO_HIGH :
                SET_BIT(*LAT_REGISTERS[_PIN_CONFIG->PORT], _PIN_CONFIG->PIN);
                break;
            default : RET = E_NOT_OK;
        }
    }
    return  RET;
}
#endif

/**
 * 
 * @param _PIN_CONFIG pointer to the configurations @ref PIN_CONFIG_T
 * @param LOGIC
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PIN_CONFIGURATIONS == CONFIG_ENABLE
STD_RETURN_TYPE GPIO_PIN_READ_LOGIC(const PIN_CONFIG_T *_PIN_CONFIG, LOGIC_T *LOGIC) {
    STD_RETURN_TYPE RET = E_OK;
    if(NULL == _PIN_CONFIG || NULL == LOGIC || _PIN_CONFIG->PIN > PORT_BIN_MAX_NUMBER-1) {
        RET = E_NOT_OK;
    }
    else {
        *LOGIC = READ_BIT(*PORT_REGISTERS[_PIN_CONFIG->PORT], _PIN_CONFIG->PIN);
    }   
    return  RET;
}
#endif

/**
 * 
 * @param _PIN_CONFIG pointer to the configurations @ref PIN_CONFIG_T
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PIN_CONFIGURATIONS == CONFIG_ENABLE
STD_RETURN_TYPE GPIO_PIN_TOGGLE_LOGIC(const PIN_CONFIG_T *_PIN_CONFIG) {
    STD_RETURN_TYPE RET = E_OK;
    if(NULL == _PIN_CONFIG || _PIN_CONFIG->PIN > PORT_BIN_MAX_NUMBER-1) {
        RET = E_NOT_OK;
    }
    else {
        TOGGLE_BIT(*LAT_REGISTERS[_PIN_CONFIG->PORT], _PIN_CONFIG->PIN);
    }
    return  RET;
}
#endif

/**
 * 
 * @param _PIN_CONFIG pointer to the configurations @ref PIN_CONFIG_T
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PIN_CONFIGURATIONS == CONFIG_ENABLE
STD_RETURN_TYPE PIN_INITIALIZE(const PIN_CONFIG_T *_PIN_CONFIG) {
    STD_RETURN_TYPE RET = E_OK;
    if(NULL == _PIN_CONFIG || _PIN_CONFIG->PIN > PORT_BIN_MAX_NUMBER-1) {
        RET = E_NOT_OK;
    }
    else {
        RET = GPIO_PIN_DIRECTION_INITIALIZE(_PIN_CONFIG);
        RET = GPIO_PIN_WRITE_LOGIC(_PIN_CONFIG, _PIN_CONFIG->LOGIC);
    }
    return  RET;
}
#endif



/**
 * 
 * @param PORT
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
STD_RETURN_TYPE GPIO_PORT_DIRECTION_INITIALIZE(PORT_INDEX_T PORT, uint8 DIREC) {
    STD_RETURN_TYPE RET = E_OK;
    if(PORT > PORT_MAX_NUMBER-1) {
        RET = E_NOT_OK;
    }
    else {
        *TRIS_REGISTERS[PORT] = DIREC;
    }
    return  RET;
}
#endif

/**
 * 
 * @param PORT
 * @param DIREC_STATUS
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
STD_RETURN_TYPE GPIO_PORT_GET_DIRECTION_STATUS(PORT_INDEX_T PORT, uint8 *DIREC_STATUS) {
    STD_RETURN_TYPE RET = E_OK;
    if((NULL == DIREC_STATUS) && (PORT > PORT_MAX_NUMBER-1)) {
        RET = E_NOT_OK;
    }
    else {
        *DIREC_STATUS = *TRIS_REGISTERS[PORT];
    }
    return  RET;
}
#endif

/**
 * 
 * @param PORT
 * @param LOGIC
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
STD_RETURN_TYPE GPIO_PORT_WRITE_LOGIC(PORT_INDEX_T PORT, uint8 LOGIC) {
    STD_RETURN_TYPE RET = E_OK;
    if(PORT > PORT_MAX_NUMBER-1) {
        RET = E_NOT_OK;
    }
    else {
        *LAT_REGISTERS[PORT] = LOGIC;
    }
    return  RET;
}
#endif

/**
 * 
 * @param PORT
 * @param LOGIC
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
STD_RETURN_TYPE GPIO_PORT_READ_LOGIC(PORT_INDEX_T PORT, uint8 *LOGIC) {
    STD_RETURN_TYPE RET = E_OK;
    if((NULL == LOGIC) && (PORT > PORT_MAX_NUMBER-1)) {
        RET = E_NOT_OK;
    }
    else {
        *LOGIC = *LAT_REGISTERS[PORT];
    }
    return  RET;
}
#endif

/**
 * 
 * @param PORT
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
STD_RETURN_TYPE GPIO_PORT_TOGGLE_LOGIC(PORT_INDEX_T PORT) {
    STD_RETURN_TYPE RET = E_OK;
    if(PORT > PORT_MAX_NUMBER-1) {
        RET = E_NOT_OK;
    }
    else {
        *LAT_REGISTERS[PORT] ^= PORTC_MASK;
    }
    return  RET;
}
#endif