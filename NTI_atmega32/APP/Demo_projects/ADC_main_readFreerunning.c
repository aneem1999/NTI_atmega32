
/*
 * CFile1.c
 *
 * Created: 2/22/2023 5:41:46 PM
 *  Author: ncm
 */

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

u16 ADCval = 0;
volatile u8 ADCFlag = 0;

void EXTI_Isr()
{
    led_viToggle(LED_RED);
}
void ADC_ISR()
{
    ADCFlag = 1;
    ADCval = ADC;

    led_viToggle(LED_BLUE);
}

int main4(void)
{

    led_viInit();
    LCD_Init();
    button_viInit();

    EXTI_Init(EXTI_0, RISINING_EDGE);
    EXTI_voidSetCallbackFunction(EXTI_0, EXTI_Isr);

    ADC_voidInit(&ADC_configurations[0]);
    ADC_voidEnable();
    ADC_voidInterrputEnable();

    ADC_voidSetCallbackFun(ADC_ISR);
    GIE_ENABLE();

    char str[10];
    ADC_voidStartConversion();

    while (1)
    {
        if (ADCFlag == 1)
        {

            ADCFlag = 0;
            itoa(ADCval, str, 10);
            LCD_WriteString(str);

            _delay_ms(1000);
            ADC_voidStartConversion();
        }
    }
}
