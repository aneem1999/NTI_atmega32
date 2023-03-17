

/*
 * NTI_AVR_Drivers.c
 *
 * Created: 2/17/2023 11:50:41 AM
 * Author : ncm
 */

#define F_CPU 16000000U
#include "../HAL/LED/led.h"
#include "../HAL/LCD/LCD.h"
#include "../MCAL/ADC/ADC_int.h"
#include "../MCAL/EXTI/EXTI_int.h"
#include "../MCAL/DIO/dio.h"
#include "../HAL/Button/button.h"

#include "../LIB/register.h"

#include <stdlib.h>
#include "../LIB/std_types.h"

#include <util/delay.h>
#if 0
u16 ADCval1 = 0;
volatile u8 ADCFlag1 = 0;

void EXTI_Isr1()
{
    led_viToggle(LED_RED);
}
void ADC_ISR1()
{
    ADCFlag1 = 1;
    ADCval1 = ADC_u16ReadADC(&ADC_configurations[0]);

    led_viToggle(LED_BLUE);
}

int mainautotrigger(void)
{
    led_viInit();
    LCD_Init();
    button_viInit();

    EXTI_Init(EXTI_0, RISINING_EDGE);
    EXTI_voidSetCallbackFunction(EXTI_0, EXTI_Isr1);

    ADC_voidInit(&ADC_configurations[0]);
    ADC_voidEnable();
    ADC_voidInterrputEnable();
    ADC_voidAutoTrigger(&ADC_configurations[0]);

    ADC_voidSetCallbackFun(ADC_ISR1);
    GIE_ENABLE();

    char str[10];

    while (1)
    {
        if (ADCFlag1 == 1)
        {

            ADCFlag1 = 0;
            itoa(ADCval1, str, 10);
            LCD_WriteString(str, 0, 0);

            _delay_ms(1000);
        }
    }
}
#endif