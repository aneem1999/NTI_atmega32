/*
 * Timer_NormalMode.c
 *
 * Created: 2/26/2023 2:25:53 PM
 *  Author: ncm
 */ 


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

#include "../MCAL/TIMER0/timer0_interface.h"
#include <util/delay.h>

volatile u32 ovfs;

void tovfISR()
{
	ovfs++;
}
int mainTN(void)
{
	led_viInit();

	T0_voidInit();
	T0_voidSetCallbackOV(tovfISR);
	T0_voidEnableInteruptOV();
	T0_voidStart();
	GIE_ENABLE();

	u8 p;
	u64 ovf;
	T0_voidSetTimerReg(p);

	while (1)
	{
		if (ovfs == ovf)
		{
			led_viToggle(LED_RED);
			ovfs = 0;
		}
	}
}
