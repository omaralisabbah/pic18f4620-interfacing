
#ifndef HAL_ADC_H
#define	HAL_ADC_H

#include "../mcal_std_types.h"
#include "../../mcal_layer/gpio/hal_gpio.h"
#include "../../mcal_layer/interrupt/mcal_internal_interrupt.h"
#include "hal_adc_cfg.h"


/**
 * @brief Analog-To-Digital Port Configuration Control
 * @note  When ADC_AN4_ANALOG_FUNCTIONALITY is configured, this means
 *        AN4,AN3,AN2,AN1,AN0 are Analog functionality.
 */

#define ADC_ALL_ANALOG_FUNCTIONALITY    0x00
#define ADC_ALL_DIGITAL_FUNCTIONALITY   0x0F

#define ADC_AN0_ANALOG_FUNCTIONALITY    0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY    0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY    0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY    0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY    0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY    0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY    0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY    0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY    0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY    0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY   0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY   0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY   0x02


#define ADC_RESULT_RIGHT    0x01U
#define ADC_RESULT_LEFT     0x00U

#define ADC_VOLTAGE_REFERENCE_ENABLED       0x01U
#define ADC_VOLTAGE_REFERENCE_DISABLED      0x00U

#define ADC_CONVERSION_COMPLETED  0x01U
#define ADC_CONVERSION_INPROGRESS 0x00U


// GO/DONE: A/D Conversion Status bit
#define ADC_CONVERSION_STATUS()  (ADCON0bits.GO_nDONE)

/*
 * GO/DONE: A/D Conversion Status bit
    When ADON = 1:
    1 = A/D conversion in progress
    0 = A/D Idle
*/
#define ADC_START_CONVERSION()  (ADCON0bits.GODONE = 1)


/*
    ADON: A/D On bit
    1 = A/D Converter module is enabled 
    0 = A/D Converter module is disabled
 */
#define ADC_CONVERTER_ENABLE()  (ADCON0bits.ADON = 1)
#define ADC_CONVERTER_DISABLE() (ADCON0bits.ADON = 0)


/*
 * Page: 224
 *  VCFG1: Voltage Reference Configuration bit (VREF- source)
    1 = VREF- (AN2)
    0 = VSS
    bit 4 VCFG0: Voltage Reference Configuration bit (VREF+ source)
    1 = VREF+ (AN3)
    0 = VDD 
*/
#define ADC_ENABLE_VOLTAGE_REFERENCE()  do{ADCON1bits.VCFG1 = 1;\
                                           ADCON1bits.VCFG0 = 1;\
                                        }while(0)
#define ADC_DISABLE_VOLTAGE_REFERENCE() do{ADCON1bits.VCFG1 = 0;\
                                           ADCON1bits.VCFG0 = 0;\
                                        }while(0)


/**
 * @brief  Analog-To-Digital Port Configuration Control
 * @note   Example : ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN4_ANALOG_FUNCTIONALITY);
		   When ADC_AN4_ANALOG_FUNCTIONALITY is configured, this means that
 *         AN4,AN3,AN2,AN1,AN0 are Analog functionality.
 * @ref Analog-To-Digital Port Configuration Control
 */
#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG) (ADCON1bits.PCFG = _CONFIG)


/*
    ADFM: A/D Result Format Select bit
    1 = Right justified 
    0 = Left justified
*/
#define ADC_RESULT_RIGHT_FORMAT()  (ADCON2bits.ADFM = 1)
#define ADC_RESULT_LEFT_FORMAT()   (ADCON2bits.ADFM = 0)


typedef enum{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12
}adc_channel_select_t; // Analog Channel Select Page: 223

/**
 * @brief  A/D Acquisition Time Select 
 * @note   Acquisition time (sampling time) is the time required for the (ADC) to 
 *         capture the input voltage during sampling.
 * @note   Acquisition time of a Successive Approximation Register (SAR) ADC is the amount of time 
 *         required to charge the holding capacitor (CHOLD) on the front end of an ADC
 */
typedef enum{
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD
}adc_acquisition_time_t; // ACQT2:ACQT0: A/D Acquisition Time Select bits


/** 
 * @brief  A/D Conversion Clock Select
 * @note   If the A/D FRC clock source is selected, a delay of one TCY (instruction cycle) 
 *         is added before the A/D clock starts.
 * @note   This allows the SLEEP instruction to be executed before starting a conversion.
 */
typedef enum{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64
}adc_conversion_clock_t; // ADCS2:ADCS0: A/D Conversion Clock Select bits


/**
 * ADC Configurations
 */
typedef struct{
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* ADC_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    adc_acquisition_time_t acquisition_time;
    adc_conversion_clock_t conversion_clock;
    adc_channel_select_t adc_channel;
    uint8 voltage_reference : 1;
    uint8 result_format : 1;
    uint8 ADC_Reserved : 6;
}adc_config_t;


// Result size of an A/D conversion
typedef uint16 adc_result_t; // Need to point to (10 Bit)


STD_RETURN_TYPE ADC_Init(const adc_config_t *_adc);
STD_RETURN_TYPE ADC_DeInit(const adc_config_t *_adc);
STD_RETURN_TYPE ADC_SelectChannel(const adc_config_t *_adc, adc_channel_select_t channel);

STD_RETURN_TYPE ADC_StartConversion(const adc_config_t *_adc);
STD_RETURN_TYPE ADC_IsConversionDone(const adc_config_t *_adc, uint8 *conversion_status);
STD_RETURN_TYPE ADC_GetConversionResult(const adc_config_t *_adc, adc_result_t *conversion_result);
STD_RETURN_TYPE ADC_GetConversion_Blocking(const adc_config_t *_adc, adc_channel_select_t channel, adc_result_t *conversion_result);
STD_RETURN_TYPE ADC_StartConversion_Interrupt(const adc_config_t *_adc, adc_channel_select_t channel);

#endif	/* HAL_ADC_H */
