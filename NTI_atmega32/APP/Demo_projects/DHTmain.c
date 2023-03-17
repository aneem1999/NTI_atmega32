/*
 * NTI_atmega32.c
 *
 * Created: 3/3/2023 10:08:32 AM
 * Author : ncm
 */

#include "../MCAL/USART/uart_interface.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/LED/led.h"
#include "../HAL/DHT11/dht.h"
#include <stdlib.h>
#define F_CPU 16000000U
#include "util/delay.h"

#if 0
char data[5];
int main()
{
	u16 RH = 0, T = 0;
	LCD_Init();
	led_viInit();
	while (1)
	{
		if (DHT_enuReadData(&RH, &T) == ERROR_READ)
		{
			LCD_WriteString("ERROR ");
		}
		else
		{
#if 1

			LCD_GoToXY(0, 0); /* Enter column and row position */
			LCD_WriteString("Humidity =");
			LCD_GoToXY(1, 0);
			LCD_WriteString("Temp = ");
			itoa(RH, data, 10);
			LCD_GoToXY(0, 11);
			LCD_WriteString(data);
			LCD_WriteString(".");

			itoa(T, data, 10);
			LCD_GoToXY(1, 6);
			LCD_WriteString(data);
			LCD_WriteString("C ");

#endif
		}
		_delay_ms(1000);
	}
}

#endif
