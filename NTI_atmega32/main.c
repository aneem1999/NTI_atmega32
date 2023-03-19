
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
#include "../HAL/KEYPAD/keypad.h"
#include "../HAL/Ultrasonic_HC_SR04/US_HC_SR04.h"
#include "../APP/Smart_Home/Enterene/Entrance_Control.h"
#include "../HAL/SERVO_MOTOR/servo.h"

#include "../HAL/RFID/RFID.h"

#if 0
char str[5];
int main()
{
	dio_vidConfigChannel(DIO_PORTA, DIO_PIN4, OUTPUT);
	dio_vidConfigChannel(DIO_PORTA, DIO_PIN5, OUTPUT);
	dio_vidConfigChannel(DIO_PORTA, DIO_PIN6, OUTPUT);

	SPI_Init();
	LCD_Init();
	mcrf522_init();
	u8 byte;
	u8 buffer[4];
	GIE_ENABLE();

	while (1)
	{
		byte = DetectCard();
		LCD_ClearDisplay();
		LCD_GoToXY(0, 0);
		if (byte == 1)
		{
			dio_vidWriteChannel(DIO_PORTA, DIO_PIN4, STD_HIGH);
			GetCardId(buffer);

			for (u8 i = 0; i < 4; i++)
			{
				itoa(buffer[i], str, 10);
				LCD_WriteString(str);
				LCD_WriteData(' ');
			}
		}
		_delay_ms(500);
	}
#endif

#if 0
	u8 k = 0;

	while (1)
	{
		char name[16];
		LCD_ClearDisplay();
		LCD_GoToXY(0, 0);

		k = Take_Compare_RFID(name);
		if (k != 0xff)
		{
			LCD_WriteString(NAME_Arr[k]);
		}
		else
		{
			LCD_WriteString("ERROR");
		}
		_delay_ms(500);
	}
}
#endif

#if 1

int main()
{
	Entrance_Init();

	while (1)
	{

		Entrance_Start();
	}
}

#endif

#if 0

int main()
{
	SERVO_voidInit();
	u8 a = 10;
	while (1)
	{

		SERVO_voidGotoAngle(a);
		a += 10;

		_delay_ms(1000);
	}
}

#endif
