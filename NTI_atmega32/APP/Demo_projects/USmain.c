/*
 * USmain.c
 *
 * Created: 3/17/2023 10:05:09 PM
 *  Author: ncm
 */ 

#if 0
#include "../MCAL/USART/uart_interface.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/LED/led.h"

#include "../MCAL/TIMER2/timer2_interface.h"
#include "../MCAL/TIMER0/timer0_interface.h"
#include "../HAL/Ultrasonic_HC_SR04/US_HC_SR04.h"

#include <string.h>

#define F_CPU 16000000U
#include <util/delay.h>

#include <stdlib.h>

#include "../SERVICES/Delay/TD_delay.h"



char Tstr[6];
int main()
{
	LCD_Init();
	led_viInit();
	f32 d = 0, d1 = 0;
	US_voidInit();

	while (1)
	{
		d =US_u8dRead_Distance_cm(US_CHANNEL_0);

		LCD_GoToXY(0, 0);
		LCD_WriteString("Distance 0 = ");
		dtostrf(d, 3, 3, Tstr);
		LCD_WriteString(Tstr);

		d1 = US_u8dRead_Distance_cm(US_CHANNEL_1);
		
		LCD_GoToXY(2, 0);
		LCD_WriteString("Distance 1 = ");
		dtostrf(d1, 3, 3, Tstr);
		LCD_WriteString(Tstr);
		_delay_ms(500);
	}
}
#endif
