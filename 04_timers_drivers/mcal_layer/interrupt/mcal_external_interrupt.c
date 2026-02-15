
#include "mcal_external_interrupt.h"

static STD_RETURN_TYPE Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static STD_RETURN_TYPE Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static STD_RETURN_TYPE Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static STD_RETURN_TYPE Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static STD_RETURN_TYPE Interrupt_INTx_McuPin_Init(const interrupt_INTx_t *int_obj);
static STD_RETURN_TYPE Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);

static STD_RETURN_TYPE Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
static STD_RETURN_TYPE Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static STD_RETURN_TYPE Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);
static STD_RETURN_TYPE Interrupt_RBx_McuPin_Init(const interrupt_RBx_t *int_obj);

static InterruptHandler INT0_InterruptHandler = NULL;
static InterruptHandler INT1_InterruptHandler = NULL;
static InterruptHandler INT2_InterruptHandler = NULL;

static InterruptHandler RB4_InterruptHandler_High = NULL;
static InterruptHandler RB4_InterruptHandler_Low = NULL;
static InterruptHandler RB5_InterruptHandler_High  = NULL;
static InterruptHandler RB5_InterruptHandler_Low  = NULL;
static InterruptHandler RB6_InterruptHandler_High  = NULL;
static InterruptHandler RB6_InterruptHandler_Low  = NULL;
static InterruptHandler RB7_InterruptHandler_High  = NULL;
static InterruptHandler RB7_InterruptHandler_Low  = NULL;

static STD_RETURN_TYPE INT0_SetInterruptHandler(void (* InterruptHandler)(void));
static STD_RETURN_TYPE INT1_SetInterruptHandler(void (* InterruptHandler)(void));
static STD_RETURN_TYPE INT2_SetInterruptHandler(void (* InterruptHandler)(void));
static STD_RETURN_TYPE Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);


void INT0_ISR(void) {
    // The INT0 external interrupt occurred (must be cleared in software)
    EXT_INT0_InterruptFlagClear();
    
    // Code
    
    // Call Back
    if(INT0_InterruptHandler) {
        INT0_InterruptHandler();
    }
}

void INT1_ISR(void) {
    // The INT1 external interrupt occurred (must be cleared in software)
    EXT_INT1_InterruptFlagClear();
    
    // Code
    
    // Call Back
    if(INT1_InterruptHandler) {
        INT1_InterruptHandler();
    }
}

void INT2_ISR(void) {
    // The INT2 external interrupt occurred (must be cleared in software)
    EXT_INT2_InterruptFlagClear();
    
    // Code
    
    // Call Back
    if(INT2_InterruptHandler) {
        INT2_InterruptHandler();
    }
}

void RB4_ISR(uint8 RB4_Source) {
    // The RBx external interrupt occurred (must be cleared in software)
    EXT_RBx_InterruptFlagClear();
    
    // Call Back
    if(STD_LOW == RB4_Source) {
        if(RB4_InterruptHandler_High) { RB4_InterruptHandler_High();}
        else {/* Nothing */}
    } else if(STD_HIGH == RB4_Source) {
        if(RB4_InterruptHandler_Low) { RB4_InterruptHandler_Low();}
        else {/* Nothing */}
    } else {
        /* Nothing */
    }
}

void RB5_ISR(uint8 RB5_Source){
    /* The RB4 external OnChange interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context */
    /* Application Callback function gets called every time this ISR executes */
    if(0 == RB5_Source){
        if(RB5_InterruptHandler_High){ RB5_InterruptHandler_High(); }
        else{ /* Nothing */ }
    }
    else if (1 == RB5_Source){
        if(RB5_InterruptHandler_Low){ RB5_InterruptHandler_Low(); }
        else{ /* Nothing */ }
    }
    else { /* Nothing */ }
}

void RB6_ISR(uint8 RB6_Source){
    /* The RB4 external OnChange interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context */
    /* Application Callback function gets called every time this ISR executes */
    if(0 == RB6_Source){
        if(RB6_InterruptHandler_High){ RB6_InterruptHandler_High(); }
        else{ /* Nothing */ }
    }
    else if (1 == RB6_Source){
        if(RB6_InterruptHandler_Low){ RB6_InterruptHandler_Low(); }
        else{ /* Nothing */ }
    }
    else { /* Nothing */ }   
}

void RB7_ISR(uint8 RB7_Source){
    /* The RB4 external OnChange interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context */
    /* Application Callback function gets called every time this ISR executes */
    if(0 == RB7_Source){
        if(RB7_InterruptHandler_High){ RB7_InterruptHandler_High(); }
        else{ /* Nothing */ }
    }
    else if (1 == RB7_Source){
        if(RB7_InterruptHandler_Low){ RB7_InterruptHandler_Low(); }
        else{ /* Nothing */ }
    }
    else { /* Nothing */ }   
}

/**
 * 
 * @param int_obj Pointer to the Interrupt Configuration object
 * @return Status of the function
 *          (E_OK): The function done successfully
 *          (E_NOT_OK): The function has issue to perform this action
 */
STD_RETURN_TYPE Inetrrupt_INTx_Init(const interrupt_INTx_t *int_obj) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    
    if(NULL == int_obj) {
        RET = E_NOT_OK;
    }
    else {
        // OR to ensures that all functions executed correctly
        // Disable The External Interrupt
        RET = Interrupt_INTx_Disable(int_obj);
        
        // Clearing The Interrupt Flag (External interrupt did not happened)
        RET |= Interrupt_INTx_Clear_Flag(int_obj);
        
        // Configure External Interrupt Edge
        RET |= Interrupt_INTx_Edge_Init(int_obj);
        
        // Configure External Interrupt I/O Pin
        RET |= Interrupt_INTx_McuPin_Init(int_obj);
        
        // Configure Default Interrupt Call Back
        RET |= Interrupt_INTx_SetInterruptHandler(int_obj);
        
        // Enable The External Interrupt
        RET |= Interrupt_INTx_Enable(int_obj);
    }
    return RET;
}

/**
 * 
 * @param int_obj Pointer to the Interrupt Configuration object
 * @return Status of the function
 *          (E_OK): The function done successfully
 *          (E_NOT_OK): The function has issue to perform this action
 */
STD_RETURN_TYPE Inetrrupt_INTx_DeInit(const interrupt_INTx_t *int_obj) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    
    if(NULL == int_obj) {
        RET = E_NOT_OK;
    }
    else {
        RET = Interrupt_INTx_Disable(int_obj);
    }
    return RET;
}

/**
 * 
 * @param int_obj
 * @return 
 */
STD_RETURN_TYPE Interrupt_RBx_Init(const interrupt_RBx_t *int_obj) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    
    if(NULL == int_obj) {
        RET = E_NOT_OK;
    }
    else {
        EXT_RBx_InterruptDisable();
        EXT_RBx_InterruptFlagClear();
        
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_LOW_PRIORITY == int_obj->priority) {
            INTERRUPT_GlobalInterruptLowEnable();
            EXT_RBx_Priority_Low();
        } else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority) {
            INTERRUPT_GlobalInterruptHighEnable();
            EXT_RBx_Priority_High();
        } else {
            /* Nothing */
        }
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        // Initialize PIN as Input
        RET = GPIO_PIN_DIRECTION_INITIALIZE(&(int_obj->mcu_pin));
        switch(int_obj->mcu_pin.PIN) {
            case PIN4 :
                RB4_InterruptHandler_High = int_obj->EXT_Interrupt_Handler_High;
                RB4_InterruptHandler_Low = int_obj->EXT_Interrupt_Handler_Low;
                break;
            case PIN5 :
                RB5_InterruptHandler_High = int_obj->EXT_Interrupt_Handler_High;
                RB5_InterruptHandler_Low = int_obj->EXT_Interrupt_Handler_Low;
                break;
            case PIN6 :
                RB6_InterruptHandler_High = int_obj->EXT_Interrupt_Handler_High;
                RB6_InterruptHandler_Low = int_obj->EXT_Interrupt_Handler_Low;
                break;
            case PIN7 :
                RB7_InterruptHandler_High = int_obj->EXT_Interrupt_Handler_High;
                RB7_InterruptHandler_Low = int_obj->EXT_Interrupt_Handler_Low;
                break;
            default   :
                RET = E_NOT_OK;
        }
        EXT_RBx_InterruptEnable();
    }
    return RET;
}

/**
 * 
 * @param int_obj
 * @return 
 */
STD_RETURN_TYPE Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    
    if(NULL == int_obj) {
        RET = E_NOT_OK;
    }
    else {
        RET = Interrupt_RBx_Disable(int_obj);
    }
    return RET;    
}


/**
 * 
 * @param int_obj
 * @return 
 */
static STD_RETURN_TYPE Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    
    if(NULL == int_obj) {
        RET = E_NOT_OK;
    }
    else {
        switch(int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0 :
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                /* By Default It's High Priority (page: 112)*/
                INTERRUPT_GlobalInterruptHighEnable();
                #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                #endif
                EXT_INT0_InterruptEnable(); RET = E_OK; break;
            case INTERRUPT_EXTERNAL_INT1 :
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelsEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority) {
                    INTERRUPT_GlobalInterruptLowEnable();
                } else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority) {
                    INTERRUPT_GlobalInterruptHighEnable();
                } else {
                    /* Nothing */
                }
                #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                #endif
                EXT_INT1_InterruptEnable(); RET = E_OK; break;
            case INTERRUPT_EXTERNAL_INT2 :
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelsEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority) {
                    INTERRUPT_GlobalInterruptLowEnable();
                } else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority) {
                    INTERRUPT_GlobalInterruptHighEnable();
                } else {
                    /* Nothing */
                }
                #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                #endif
                EXT_INT2_InterruptEnable(); RET = E_OK; break;
            default: RET = E_NOT_OK;
        }
    }
    return RET;    
}

/**
 * 
 * @param int_obj
 * @return 
 */
static STD_RETURN_TYPE Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    
    if(NULL == int_obj) {
        RET = E_NOT_OK;
    }
    else {
        switch(int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0 :
                EXT_INT0_InterruptDisable(); RET = E_OK; break;
            case INTERRUPT_EXTERNAL_INT1 :
                EXT_INT1_InterruptDisable(); RET = E_OK; break;
            case INTERRUPT_EXTERNAL_INT2 :
                EXT_INT2_InterruptDisable(); RET = E_OK; break;
            default: RET = E_NOT_OK;
        }
    }
    return RET;    
}

/**
 * 
 * @param int_obj
 * @return 
 */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
static STD_RETURN_TYPE Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    
    if(NULL == int_obj) {
        RET = E_NOT_OK;
    }
    else {
        switch(int_obj->source) {
            case INTERRUPT_EXTERNAL_INT1 :
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority) {
                    EXT_INT1_InterruptLowPrioritySet();
                } else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority) {
                    EXT_INT1_InterruptHighPrioritySet();
                } else {
                    /* Do Nothing */
                }
            case INTERRUPT_EXTERNAL_INT2 :
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority) {
                    EXT_INT2_InterruptLowPrioritySet();
                } else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                    EXT_INT2_InterruptHighPrioritySet();
                } else {
                    /* Do Nothing */
                }
            default: RET = E_NOT_OK;
        }
    }
    return RET;    
}
#endif

/**
 * 
 * @param int_obj
 * @return 
 */
static STD_RETURN_TYPE Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    
    if(NULL == int_obj) {
        RET = E_NOT_OK;
    }
    else {
        switch(int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0 :
                if(INTERRUPT_FALLING_EDGE == int_obj->edge) {
                    EXT_INT0_FallingEdgeSet();
                } else if(INTERRUPT_RISING_EDGE == int_obj->edge) {
                    EXT_INT0_RisingEdgeSet();
                } else {
                    /* Do Nothing*/
                }
            case INTERRUPT_EXTERNAL_INT1 :
                if(INTERRUPT_FALLING_EDGE == int_obj->edge) {
                    EXT_INT1_FallingEdgeSet();
                } else if(INTERRUPT_RISING_EDGE == int_obj->edge) {
                    EXT_INT1_RisingEdgeSet();
                } else {
                    /* Do Nothing*/
                }
            case INTERRUPT_EXTERNAL_INT2 :
                if(INTERRUPT_FALLING_EDGE == int_obj->edge) {
                    EXT_INT2_FallingEdgeSet();
                } else if(INTERRUPT_RISING_EDGE == int_obj->edge) {
                    EXT_INT2_RisingEdgeSet();
                } else {
                    /* Do Nothing*/
                }
            default: RET = E_NOT_OK;
        }
    }
    return RET;    
}

/**
 * 
 * @param int_obj
 * @return 
 */
static STD_RETURN_TYPE Interrupt_INTx_McuPin_Init(const interrupt_INTx_t *int_obj) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    
    if(NULL == int_obj) {
        RET = E_NOT_OK;
    }
    else {
        RET = GPIO_PIN_DIRECTION_INITIALIZE(&(int_obj->mcu_pin));
    }
    return RET;    
}

/**
 * 
 * @param int_obj
 * @return 
 */
static STD_RETURN_TYPE Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    
    if(NULL == int_obj) {
        RET = E_NOT_OK;
    }
    else {
        switch(int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0 :
                EXT_INT0_InterruptFlagClear(); RET = E_OK; break;
            case INTERRUPT_EXTERNAL_INT1 :
                EXT_INT1_InterruptFlagClear(); RET = E_OK; break;
            case INTERRUPT_EXTERNAL_INT2 :
                EXT_INT2_InterruptFlagClear(); RET = E_OK; break;
            default: RET = E_NOT_OK;
        }
    }
    return RET; 
}

/**
 * 
 * @param InterruptHandler
 * @return 
 */
static STD_RETURN_TYPE INT0_SetInterruptHandler(void (* InterruptHandler)(void)) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    
    if(NULL == InterruptHandler) {
        RET = E_NOT_OK;
    }
    else {
        INT0_InterruptHandler = InterruptHandler; RET = E_OK;
    }
    return RET; 
}

/**
 * 
 * @param InterruptHandler
 * @return 
 */
static STD_RETURN_TYPE INT1_SetInterruptHandler(void (* InterruptHandler)(void)) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    
    if(NULL == InterruptHandler) {
        RET = E_NOT_OK;
    }
    else {
        INT1_InterruptHandler = InterruptHandler; RET = E_OK;
    }
    return RET;
}

/**
 * 
 * @param InterruptHandler
 * @return 
 */
static STD_RETURN_TYPE INT2_SetInterruptHandler(void (* InterruptHandler)(void)) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    
    if(NULL == InterruptHandler) {
        RET = E_NOT_OK;
    }
    else {
        INT2_InterruptHandler = InterruptHandler; RET = E_OK;
    }
    return RET;
}

/**
 * 
 * @param InterruptHandler
 * @return 
 */
static STD_RETURN_TYPE Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj) {
    STD_RETURN_TYPE RET = E_NOT_OK;
    
    if(NULL == int_obj) {
        RET = E_NOT_OK;
    }
    else {
        switch(int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0 :
                RET = INT0_SetInterruptHandler(int_obj->EXT_Interrupt_Handler);
                RET = E_OK; break;
            case INTERRUPT_EXTERNAL_INT1 :
                RET = INT1_SetInterruptHandler(int_obj->EXT_Interrupt_Handler);
                RET = E_OK; break;
            case INTERRUPT_EXTERNAL_INT2 :
                RET = INT2_SetInterruptHandler(int_obj->EXT_Interrupt_Handler);
                RET = E_OK; break;
            default: RET = E_NOT_OK;
        }
    }
    return RET; 
}
