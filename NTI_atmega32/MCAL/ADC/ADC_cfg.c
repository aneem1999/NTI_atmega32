/***************************************************************
     @author             :    Ahmed Naeem
     @date 				 :    24 Feb 2023
     @version 			 :    1.0V
     @brief 		     :    Configure Sense Mode [cfg.c]
***************************************************************/

#include "ADC_int.h"
/***************************************************************
            ADC_chammel can be :
                                ADC_Channel_0,
                                ADC_Channel_1,
                                ADC_Channel_2,
                                ADC_Channel_3,
                                ADC_Channel_4,
                                ADC_Channel_5,
                                ADC_Channel_6,
                                 DC_Channel_7

*-*-*_*-*-*-*-*-*_*-*-*-*-*-*-*_*-*-*-*-*-*-*_*-*-*-*-*-*-*_*-*-*-*

           VOLTAGE_REFERENCE can be :
                                    AREF
                                    AVCC
                                    INTERNAL

*-*-*_*-*-*-*-*-*_*-*-*-*-*-*-*_*-*-*-*-*-*-*_*-*-*-*-*-*-*_*-*-*-*

            ADJUSTMENT can be :
                                    RIGHT_ADJUSTMENT
                                    LEFT_ADJUSTMENT

 NOTE	 : The preferred adjustment for a 8 bits Resolution
                is LEFT_ADJUSTMENT and for a 10 bits Resolution
                is RIGHT_ADJUSTMENT

*-*-*_*-*-*-*-*-*_*-*-*-*-*-*-*_*-*-*-*-*-*-*_*-*-*-*-*-*-*_*-*-*-*
            PRESCALER can be
                                    DIVID_BY_2
                                    DIVID_BY_4,
                                    DIVID_BY_8,
                                    DIVID_BY_16,
                                    DIVID_BY_32,
                                    DIVID_BY_64,
                                    DIVID_BY_128

*-*-*_*-*-*-*-*-*_*-*-*-*-*-*-*_*-*-*-*-*-*-*_*-*-*-*-*-*-*_*-*-*-*
           auto trigger Modes can be :
                                FREE_RUNNING_MODE,
                                ANALOG_COMPARATOR,
                                EXTERNAL_INTERRPUT_REQUEST_0,
                                TIMER_COUNTER_0_COMPARE_MATCH,
                                TIMER_COUNTER_0_OVERFLOW,
                                TIMER_COUNTER_COMPARE_MATCH_B,
                                TIMER_COUNTER_1_OVERFLOW,
                                TIMER_COUNTER_1_CAPTURE_EVENT,
                                NO_AUTO_TRIG
typedef struct ADC_Conf
{
    ADC_Channel_t channel;
    ADC_VoltageReference_t voltageReference;
    ADC_ValueAdjust_t adjustment;
    ADC_AutoTriggerSource_t AutoTriggerSource;
    ADC_Prescaler_t prescaler;

} ADC_Config_t;

****************************************************************/

ADC_Config_t ADC_configurations[] = {
    {ADC_Channel_0, AREF, RIGHT_ADJUSTMENT, FREE_RUNNING_MODE, DIVID_BY_128},
    {ADC_Channel_1, AREF, RIGHT_ADJUSTMENT, FREE_RUNNING_MODE, DIVID_BY_128},
	{ADC_Channel_2, AREF, RIGHT_ADJUSTMENT, FREE_RUNNING_MODE, DIVID_BY_128},
	{ADC_Channel_3, AREF, RIGHT_ADJUSTMENT, FREE_RUNNING_MODE, DIVID_BY_128}

};
