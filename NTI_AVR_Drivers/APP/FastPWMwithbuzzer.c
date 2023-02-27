
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
#include "../HAL/KEYPAD/keyPad.h"

#include "../LIB/register.h"

#include "../MCAL/TIMER0/timer0_interface.h"
#include <util/delay.h>

volatile u32 ovfs;


int mainpWM1(void)
{
	led_viInit();
	KeyPad_init();

    T0_voidInit();
	T0_voidStart();
	T0_voidSetOC0Mode(TIMER0_OC0_CLR);

	u8 c = 0,duty =25;

	while (1)
	{
		if (GetKeyPressed(&c, Keypad_1) == KEY_PRESSED)
		{
			led_viToggle(LED_RED);
			duty =  (c -48 ) * 30;
			T0_voidSetOutputCompareReg(duty);
			_delay_ms(50);
		}
		
			T0_voidSetOutputCompareReg(0);
			
		
		
		
		
	}
}
