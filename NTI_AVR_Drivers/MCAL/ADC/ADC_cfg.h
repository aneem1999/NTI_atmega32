/***************************************************************
     Author             :    Ahmed Naeem
     Date 				:    24 feb 2023
     Version 			:    1.0V
     Description 		:    configuration interface
****************************************************************/

/***************************************************************
           Sense Mode Definition
****************************************************************/
typedef enum
{
    AVCC,
    AREF,
    INTERNAL = 4
} ADC_VoltageReference_t;

/****************************************************************/
/**            Adjustment Definition					   		*/
/****************************************************************/
typedef enum
{
    RIGHT_ADJUSTMENT,
    LEFT_ADJUSTMENT
} ADC_ValueAdjust_t;

/****************************************************************/
/**           Prescaler select				   		*/
/****************************************************************/
typedef enum
{
    DIVID_BY_2 = 1,
    DIVID_BY_4,
    DIVID_BY_8,
    DIVID_BY_16,
    DIVID_BY_32,
    DIVID_BY_64,
    DIVID_BY_128
} ADC_Prescaler_t;

/****************************************************************/
/**            ADC Mode Reference					   		*/
/****************************************************************/
typedef enum
{
    FREE_RUNNING_MODE,
    ANALOG_COMPARATOR,
    EXTERNAL_INTERRPUT_REQUEST_0,
    TIMER_COUNTER_0_COMPARE_MATCH,
    TIMER_COUNTER_0_OVERFLOW,
    TIMER_COUNTER_COMPARE_MATCH_B,
    TIMER_COUNTER_1_OVERFLOW,
    TIMER_COUNTER_1_CAPTURE_EVENT,
    NO_AUTO_TRIG
} ADC_AutoTriggerSource_t;

/****************************************************************
 *            ADC channel select
 ****************************************************************/
typedef enum
{
    ADC_Channel_0,
    ADC_Channel_1,
    ADC_Channel_2,
    ADC_Channel_3,
    ADC_Channel_4,
    ADC_Channel_5,
    ADC_Channel_6,
    ADC_Channel_7

} ADC_Channel_t;

/****************************************************************
 *            configuration struct
 ****************************************************************/
typedef struct ADC_Conf
{
    ADC_Channel_t channel;
    ADC_VoltageReference_t voltageReference;
    ADC_ValueAdjust_t adjustment;
    ADC_AutoTriggerSource_t AutoTriggerSource;
    ADC_Prescaler_t prescaler;

} ADC_Config_t;

/****************************************************************
 *           array of configurations struct
 ****************************************************************/
extern ADC_Config_t ADC_configurations[];